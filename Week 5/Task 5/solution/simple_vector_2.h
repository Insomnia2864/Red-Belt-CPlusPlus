//#pragma once

#include <cstdlib>
#include <algorithm>
#include <utility>

template <typename T>
class SimpleVector
{
public:
    SimpleVector();
    explicit SimpleVector(size_t size);
    ~SimpleVector();

    T& operator[](size_t index);

    T* begin();
    T* end();

    size_t Size() const;
    size_t Capacity() const;
    void PushBack(T value);

private:
    std::size_t capacity_;
    std::size_t size_;
    T* elements_;
};

template <typename T>
SimpleVector<T>::SimpleVector() :
    capacity_(0),
    size_(0),
    elements_(nullptr)
{}

template <typename T>
SimpleVector<T>::SimpleVector(size_t size) :
    capacity_(size),
    size_(size),
    elements_(new T[capacity_])
{}

template <typename T>
SimpleVector<T>::~SimpleVector()
{
    delete[] elements_;
}

template <typename T>
T& SimpleVector<T>::operator[](size_t index)
{
    return elements_[index];
}


template <typename T>
T* SimpleVector<T>::begin()
{
    return elements_;
}

template <typename T>
T* SimpleVector<T>::end()
{
    return elements_ + size_;
}

template <typename T>
size_t SimpleVector<T>::Size() const
{
    return size_;
}

template <typename T>
size_t SimpleVector<T>::Capacity() const
{
    return capacity_;
}

template <typename T>
void SimpleVector<T>::PushBack(T value)
{
    if (capacity_ == size_)
    {
        T* tmp;
        if (capacity_ == 0)
        {
            capacity_ = 1;
            tmp = new T[capacity_];
        }
        else
        {
            capacity_ *= 2;
            tmp = new T[capacity_];
        }

        for (size_t i = 0; i < size_; i++)
        {
            tmp[i] = std::move(elements_[i]);
        }
        tmp[size_++] = std::move(value);
        if (elements_ != nullptr)
        {
            delete[] elements_;
        }
        elements_ = tmp;
        return;
    }

    elements_[size_++] = std::move(value);

}