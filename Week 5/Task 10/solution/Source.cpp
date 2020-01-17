#include "test_runner.h"

#include <numeric>
#include <vector>
#include <string>
#include <future>
#include <mutex>
#include <queue>
#include <thread>

template <typename T>
class Synchronized {
public:
    explicit Synchronized(T initial = T()) :
        value(initial)
    {}

    struct Access 
    {
        T& ref_to_value;
        std::mutex& m_ref;

        ~Access()
        {
            m_ref.unlock();
        }
    };

    Access GetAccess()
    {   
        m.lock();
        return { value, m };
    }
private:
    T value;
    std::mutex m;
};





//testing
void TestConcurrentUpdate() 
{
    Synchronized<std::string> common_string;

    const size_t add_count = 50000;
    auto updater = [&common_string, add_count]
    {
        for (size_t i = 0; i < add_count; ++i) 
        {
            auto access = common_string.GetAccess();
            access.ref_to_value += 'a';
        }
    };

    auto f1 = std::async(updater);
    auto f2 = std::async(updater);

    f1.get();
    f2.get();

    ASSERT_EQUAL(common_string.GetAccess().ref_to_value.size(), 2 * add_count);
}

std::vector<int> Consume(Synchronized<std::deque<int>>& common_queue) 
{
    std::vector<int> got;

    for (;;) 
    {
        std::deque<int> q;

        {
            auto access = common_queue.GetAccess();
            q = move(access.ref_to_value);
        }

        for (int item : q) 
        {
            if (item > 0) 
            {
                got.push_back(item);
            }
            else 
            {
                return got;
            }
        }
    }
}

void TestProducerConsumer()
{
    Synchronized<std::deque<int>> common_queue;

    auto consumer = async(Consume, std::ref(common_queue));

    const size_t item_count = 100000;
    for (size_t i = 1; i <= item_count; ++i)
    {
        common_queue.GetAccess().ref_to_value.push_back(i);
    }
    common_queue.GetAccess().ref_to_value.push_back(-1);

    std::vector<int> expected(item_count);
    std::iota(expected.begin(), expected.end(), 1);
    ASSERT_EQUAL(consumer.get(), expected);
}

int main() 
{
    TestRunner tr;
    RUN_TEST(tr, TestConcurrentUpdate);
    RUN_TEST(tr, TestProducerConsumer);

    return 0;
}