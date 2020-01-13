#pragma once

#include <cstdlib>
#include <algorithm>

template <typename T>
class SimpleVector
{
public:
    SimpleVector();
    explicit SimpleVector(size_t size);
    SimpleVector(const SimpleVector& other);
    ~SimpleVector();

    T& operator[](size_t index);
    void operator=(const SimpleVector& other);

    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;

    size_t Size() const;
    size_t Capacity() const;
    void PushBack(const T& value);

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
SimpleVector<T>::SimpleVector(const SimpleVector<T>& other) :
    elements_(new T[other.capacity_]),
    capacity_(other.capacity_),
    size_(other.size_)
{
    std::copy(other.begin(), other.end(), elements_);
}

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
void SimpleVector<T>::operator=(const SimpleVector<T>& other)
{
    if (this->capacity_ >= other.size_)
    {
        std::copy(other.begin(), other.end(), elements_);
        size_ = other.size_;
    }
    else
    {
        if (this->elements_ != nullptr)
        {
            delete[] this->elements_;
        }
        this->elements_ = new T[other.capacity_];
        this->size_ = other.size_;
        this->capacity_ = other.capacity_;
        std::copy(other.begin(), other.end(), elements_);
    }
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
const T* SimpleVector<T>::begin() const
{
    return elements_;
}

template <typename T>
const T* SimpleVector<T>::end() const
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
void SimpleVector<T>::PushBack(const T& value)
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
            tmp[i] = elements_[i];
        }
        tmp[size_++] = value;
        delete[] elements_;
        elements_ = tmp;
        return;
    }

    elements_[size_++] = value;

}