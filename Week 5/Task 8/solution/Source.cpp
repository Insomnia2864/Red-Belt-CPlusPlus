#include "test_runner.h"
#include <vector>
#include <cstdint>
#include <future>
#include <numeric>

std::int64_t Summing(const std::vector<std::vector<int>>& vec, std::size_t begin, std::size_t end)
{
    std::int64_t res = 0;
    for (std::size_t i = begin; i < end; i++)
    {
        res += static_cast<std::int64_t>(std::accumulate(vec[i].begin(), vec[i].end(), static_cast<std::int64_t>(0)));
    }

    return res;
}

std::int64_t CalculateMatrixSum(const std::vector<std::vector<int>>& matrix) 
{
    std::int64_t result = 0;

    std::vector<std::future<std::int64_t>> vec;
    
    for (size_t i = 0; ; i++)
    {
        vec.push_back(
            std::async([&matrix, i]
                {
                    return Summing(matrix, 2000u * i, std::min(2000u * (i + 1), matrix.size()));
                })
        );

        if (std::min(2000u * (i + 1), matrix.size()) == matrix.size())
        {
            break;
        }
    }
    for (auto& i : vec)
    {
        result += i.get();
    }

    return result;    
}





// testing
void TestCalculateMatrixSum() 
{
    const std::vector<std::vector<int>> matrix = 
    {
      {1, 2, 3, 4},
      {5, 6, 7, 8},
      {9, 10, 11, 12},
      {13, 14, 15, 16}
    };

    ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() 
{
    TestRunner tr;
    RUN_TEST(tr, TestCalculateMatrixSum);

    return 0;
}