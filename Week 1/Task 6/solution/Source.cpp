#include "test_runner.h"

template <typename T>
class Table
{
public:
    Table() = default;
    Table(std::size_t rows, std::size_t cols);

    void Resize(std::size_t rows, std::size_t cols);

    std::pair<std::size_t, std::size_t> Size() const;

    std::vector<T>& operator[](size_t index);
    std::vector<T>& operator[](size_t index) const;
private:
    std::size_t rows_, cols_;
    std::vector<std::vector<T>>  elems_;
};



void TestTable() {
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestTable);
    return 0;
}

template <typename T>
Table<T>::Table(std::size_t rows, std::size_t cols) :
    rows_(rows),
    cols_(cols)
{
    elems_.resize(rows_);
    for (auto& i : elems_)
    {
        i.resize(cols_);
    }
}

template <typename T>
void Table<T>::Resize(std::size_t rows, std::size_t cols)
{
    rows_ = rows;
    cols_ = cols;

    elems_.resize(rows_);
    for (auto& i : elems_)
    {
        i.resize(cols_);
    }
}
template <typename T>
std::pair<std::size_t, std::size_t> Table<T>::Size() const
{
    return std::make_pair(rows_, cols_);
}

template <typename T>
std::vector<T>& Table<T>::operator[](size_t index)
{
    return elems_[index];
}

template <typename T>
std::vector<T>& Table<T>::operator[](size_t index) const
{
    return elems_[index];
}