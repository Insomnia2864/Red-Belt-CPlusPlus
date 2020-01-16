#include <cstdint>
#include <iterator>
#include <numeric>
#include <list>


#include "test_runner.h"

template <typename Collection, typename RandomIt>
RandomIt NextStep(Collection& collection, RandomIt it, std::uint32_t steps)
{
    while (steps-- != 0)
    {
        it = std::next(it);
        if (it == collection.end())
        {
            it = collection.begin();
        }
    }

    return it;
}

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, std::uint32_t step_size) 
{
    std::list<typename RandomIt::value_type> lst;
    for (auto it = first; it != last; ++it) 
    {
        lst.push_back(std::move(*it));
    }

    auto it = lst.begin();

    while (!lst.empty())
    {
        if (lst.size() == 1)
        {
            *first = std::move(*lst.begin());
            break;
        }

        *(first++) = std::move(*it);

        auto next_it = NextStep(lst, it, 1);
        lst.erase(it);


        it = NextStep(lst, next_it, step_size - 1);
    }
}


std::vector<int> MakeTestVector()
{
    std::vector<int> numbers(10);
    std::iota(numbers.begin(), numbers.end(), 0);
    return numbers;
}

void TestIntVector() 
{
    const std::vector<int> numbers = MakeTestVector();
    {
        std::vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(numbers_copy.begin(), numbers_copy.end(), 1);
        ASSERT_EQUAL(numbers_copy, numbers);
    }
    {
        std::vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(numbers_copy.begin(), numbers_copy.end(), 3);
        ASSERT_EQUAL(numbers_copy, std::vector<int>({ 0, 3, 6, 9, 4, 8, 5, 2, 7, 1 }));
    }
}


struct NoncopyableInt 
{
    int value;

    NoncopyableInt(const NoncopyableInt&) = delete;
    NoncopyableInt& operator=(const NoncopyableInt&) = delete;

    NoncopyableInt(NoncopyableInt&&) = default;
    NoncopyableInt& operator=(NoncopyableInt&&) = default;
};

bool operator==(const NoncopyableInt& lhs, const NoncopyableInt& rhs) 
{
    return lhs.value == rhs.value;
}

std::ostream& operator<<(std::ostream& os, const NoncopyableInt& v) 
{
    return os << v.value;
}

void TestAvoidsCopying() 
{
    std::vector<NoncopyableInt> numbers;
    numbers.push_back({ 1 });
    numbers.push_back({ 2 });
    numbers.push_back({ 3 });
    numbers.push_back({ 4 });
    numbers.push_back({ 5 });

    MakeJosephusPermutation(numbers.begin(), numbers.end(), 2);

    std::vector<NoncopyableInt> expected;
    expected.push_back({ 1 });
    expected.push_back({ 3 });
    expected.push_back({ 5 });
    expected.push_back({ 4 });
    expected.push_back({ 2 });

    ASSERT_EQUAL(numbers, expected);
}

int main() 
{
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    RUN_TEST(tr, TestAvoidsCopying);
    return 0;
}