#pragma once

#include <stdexcept>
#include <array>

template <typename T, std::size_t N>
class StackVector 
{
public:
    explicit StackVector(std::size_t a_size = 0) :
        size_(a_size),
        capacity_(N)
    {
        if (size_>capacity_)
        {
            throw std::invalid_argument("a_size > capacity");
        }
    }

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;

    std::size_t Size() const;
    std::size_t Capacity() const;

    void PushBack(const T& value);
    T PopBack();

private:
    std::size_t size_;
    std::size_t capacity_;
    std::array<T, N> arr;
};

template <typename T, std::size_t N>
T& StackVector<T,N>::operator[](std::size_t index)
{
    return arr[index];
}

template <typename T, std::size_t N>
const T& StackVector<T, N>::operator[](std::size_t index) const
{
    return arr[index];
}

template <typename T, std::size_t N>
T* StackVector<T, N>::begin()
{
    return &arr[0];
}

template <typename T, std::size_t N>
T* StackVector<T, N>::end()
{
    return &arr[size_];
}

template <typename T, std::size_t N>
const T* StackVector<T, N>::begin() const
{
    return &arr[0];
}

template <typename T, std::size_t N>
const T* StackVector<T, N>::end() const
{
    return &arr[size_];
}

template <typename T, std::size_t N>
std::size_t StackVector<T, N>::Size() const
{
    return size_;
}

template <typename T, std::size_t N>
std::size_t StackVector<T, N>::Capacity() const
{
    return capacity_;
}

template <typename T, std::size_t N>
void StackVector<T, N>::PushBack(const T& value)
{
    if (size_ == capacity_)
    {
        throw std::overflow_error("overflow");
    }

    arr[size_++] = value;
}

template <typename T, std::size_t N>
T StackVector<T, N>::PopBack()
{
    if (size_ == 0)
    {
        throw std::underflow_error("underflow");
    }

    return arr[--size_];
}