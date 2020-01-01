#include <numeric>
#include <iostream>
#include <vector>
#include <string>

template <typename Iterator>
class IteratorRange
{
public:
    IteratorRange(Iterator begin, Iterator end);

    Iterator begin();
    Iterator begin() const;
    Iterator end();
    Iterator end() const;
    std::size_t size() const;

private:
    Iterator first_;
    Iterator last_;
};

template <typename Iterator>
class Paginator 
{
public:
    Paginator(Iterator begin, Iterator end, std::size_t page_size);

    std::size_t size() const;
    auto begin();
    auto end();

private:
    Iterator first_;
    Iterator last_;
    size_t page_size_;
    std::vector<IteratorRange<Iterator>> pages_;
};

template <typename C>
auto Paginate(C& c, std::size_t page_size)
{
    return Paginator(c.begin(), c.end(), page_size);
}

template <typename Iterator>
IteratorRange<Iterator>::IteratorRange(Iterator begin, Iterator end) :
    first_(begin),
    last_(end)
{}

template <typename Iterator>
Iterator IteratorRange<Iterator>::begin()
{
    return first_;
}

template <typename Iterator>
Iterator IteratorRange<Iterator>::begin() const
{
    return first_;
}

template <typename Iterator>
Iterator IteratorRange<Iterator>::end()
{
    return last_;
}

template <typename Iterator>
Iterator IteratorRange<Iterator>::end() const
{
    return last_;
}

template <typename Iterator>
std::size_t IteratorRange<Iterator>::size() const
{
    return (last_ - first_);
}

template <typename Iterator>
Paginator<Iterator>::Paginator(Iterator begin, Iterator end, std::size_t page_size) :
    first_(begin),
    last_(end),
    page_size_(page_size)
{
    if (first_ == last_)
    {
        return;
    }

    Iterator it = first_;
    while (true)
    {
        if (last_ - it <= page_size_)
        {
            pages_.push_back(IteratorRange<Iterator>(it, last_));
            break;
        }
        else
        {
            pages_.push_back(IteratorRange<Iterator>(it, it + page_size_));
            it = it + page_size_;
        }
    }
}

template <typename Iterator>
std::size_t Paginator<Iterator>::size() const
{
    return pages_.size();
}

template <typename Iterator>
auto Paginator<Iterator>::begin()
{
    return pages_.begin();
}

template <typename Iterator>
auto Paginator<Iterator>::end()
{
    return pages_.end();
}