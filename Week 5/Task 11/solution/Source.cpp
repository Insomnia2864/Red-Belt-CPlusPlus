#include "test_runner.h"
#include "profile.h"

#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <random>
#include <future>

template <typename T>
T Indexing(T a) 
{
    return a < 0 ? -a : a;
}

template<typename K, typename V>
class Storage
{
public:
    Storage() = default;

    std::map<K, V> storage;
    std::mutex m;
};

template <typename K, typename V>
class ConcurrentMap
{
public:
    static_assert(std::is_integral_v<K>, "ConcurrentMap supports only integer keys");

    struct Access
    {
    public:
        Access(V& value, std::mutex& mtx) :
            ref_to_value(value),
            m_ref(mtx)
        {}

        ~Access()
        {
            m_ref.unlock();
        }

        V& ref_to_value;
    private:
        std::mutex& m_ref;
    };

    explicit ConcurrentMap(std::size_t bucket_count) :
        maps(std::vector<Storage<K, V>>(bucket_count))
    {}

    Access operator[](const K& key)
    {
        std::size_t key_adv = Indexing(key) % maps.size();

        maps[key_adv].m.lock();
        return Access(maps[key_adv].storage[key], maps[key_adv].m);
    }

    std::map<K, V> BuildOrdinaryMap()
    {
        std::map<K, V> result;

        for (auto& i : maps)
        {
            i.m.lock();
            for (auto& j : i.storage)
            {
                result[j.first] = j.second;
            }
            i.m.unlock();
        }

        return result;
    }

private:
    std::vector<Storage<K, V>> maps;
};




//testing

void RunConcurrentUpdates(ConcurrentMap<int, int>& cm, std::size_t thread_count, int key_count)
{
    auto kernel = [&cm, key_count](int seed)
    {
        std::vector<int> updates(key_count);
        std::iota(updates.begin(), updates.end(), -key_count / 2);
        std::shuffle(updates.begin(), updates.end(), std::default_random_engine(seed));

        for (int i = 0; i < 2; ++i)
        {
            for (auto key : updates)
            {
                cm[key].ref_to_value++;
            }
        }
    };

    std::vector<std::future<void>> futures;
    for (size_t i = 0; i < thread_count; ++i)
    {
        futures.push_back(std::async(kernel, i));
    }
}

void TestConcurrentUpdate()
{
    const std::size_t thread_count = 3;
    const std::size_t key_count = 50000;

    ConcurrentMap<int, int> cm(thread_count);
    RunConcurrentUpdates(cm, thread_count, key_count);

    const auto result = cm.BuildOrdinaryMap();
    ASSERT_EQUAL(result.size(), key_count);

    for (auto& [k, v] : result)
    {
        AssertEqual(v, 6, "Key = " + std::to_string(k));
    }
}

void TestReadAndWrite()
{
    ConcurrentMap<size_t, std::string> cm(5);

    auto updater = [&cm]
    {
        for (size_t i = 0; i < 50000; ++i)
        {
            cm[i].ref_to_value += 'a';
        }
    };
    auto reader = [&cm]
    {
        std::vector<std::string> result(50000);
        for (size_t i = 0; i < result.size(); ++i)
        {
            result[i] = cm[i].ref_to_value;
        }
        return result;
    };

    auto u1 = std::async(updater);
    auto r1 = std::async(reader);
    auto u2 = std::async(updater);
    auto r2 = std::async(reader);

    u1.get();
    u2.get();

    for (auto f : { &r1, &r2 })
    {
        auto result = f->get();
        ASSERT(std::all_of(result.begin(), result.end(), [](const std::string& s)
            {
                return s.empty() || s == "a" || s == "aa";
            }));
    }
}

void TestSpeedup()
{
    {
        ConcurrentMap<int, int> single_lock(1);

        LOG_DURATION("Single lock");
        RunConcurrentUpdates(single_lock, 4, 50000);
    }
    {
        ConcurrentMap<int, int> many_locks(100);

        LOG_DURATION("100 locks");
        RunConcurrentUpdates(many_locks, 4, 50000);
    }
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestConcurrentUpdate);
    RUN_TEST(tr, TestReadAndWrite);
    RUN_TEST(tr, TestSpeedup);
}