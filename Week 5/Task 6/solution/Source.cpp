#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "test_runner.h"

/*
 *  split into 3 parts
 */

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    size_t one_to_third = (range_end - range_begin) / 3;
    if ((range_end - range_begin) < 2)
    {
        return;
    }

    std::vector<typename RandomIt::value_type> vec(std::make_move_iterator(range_begin), std::make_move_iterator(range_end));

    RandomIt first_p = vec.begin() + (vec.end() - vec.begin()) / 3;
    RandomIt second_p = vec.begin() + (vec.end() - vec.begin()) * 2 / 3;

    MergeSort(vec.begin(), first_p);
    MergeSort(first_p, second_p);
    MergeSort(second_p, vec.end());

    std::vector<typename RandomIt::value_type> tmp_res;

    std::merge(std::make_move_iterator(vec.begin()), std::make_move_iterator(first_p),
        std::make_move_iterator(first_p), std::make_move_iterator(second_p),
        std::back_inserter(tmp_res));

    std::merge(std::make_move_iterator(tmp_res.begin()), std::make_move_iterator(tmp_res.end()),
        std::make_move_iterator(second_p), std::make_move_iterator(vec.end()),
        range_begin);
}

void TestIntVector()
{
    std::vector<int> numbers = { 6, 1, 3, 9, 1, 9, 8, 12, 1 };
    MergeSort(std::begin(numbers), std::end(numbers));
    ASSERT(std::is_sorted(std::begin(numbers), std::end(numbers)));
}

int main() 
{
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    return 0;
}