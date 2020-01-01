#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class Deque
{
public:
	Deque() = default;

	bool Empty() const;

	std::size_t Size() const;

	T& operator[](std::size_t index);
	const T& operator[](std::size_t index) const;

	const T& At(std::size_t index) const;
	T& At(std::size_t index);

	T& Front();
	const T& Front() const;

	T&Back();
	const T& Back() const;

	void PushFront(const T& elem);

	void PushBack(const T& elem);

private:
	std::vector<T> begin_;
	std::vector<T> end_;
};

int main()
{
	Deque<int> dq;

	std::cout << dq.Empty();

	try 
	{
		std::cout << dq[0] << dq[1] << dq[2] << std::endl;
	}
	catch (std::out_of_range& e)
	{
		std::cerr << e.what();
	}

	return 0;
}

template <typename T>
bool Deque<T>::Empty() const
{
	return begin_.empty() && end_.empty();
}

template <typename T>
std::size_t Deque<T>::Size() const
{
	return begin_.size() + end_.size();
}

template <typename T>
T& Deque<T>::operator[](std::size_t index)
{
	if (index >= this->Size())
	{
		throw std::out_of_range("index > size");
	}

	if (index < begin_.size())
	{
		return begin_[begin_.size() - index - 1];
	}

	return end_[index - begin_.size()];
}

template <typename T>
const T& Deque<T>::operator[](std::size_t index) const
{
	if (index >= this->Size())
	{
		throw std::out_of_range("index > size");
	}

	if (index < begin_.size())
	{
		return begin_[begin_.size() - index - 1];
	}

	return end_[index - begin_.size()];
}

template <typename T>
const T& Deque<T>::At(std::size_t index) const
{
	if (index >= this->Size())
	{
		throw std::out_of_range("index > size");
	}

	if (index < begin_.size())
	{
		return begin_[begin_.size() - index - 1];
	}

	return end_[index - begin_.size()];
}

template <typename T>
T& Deque<T>::At(std::size_t index)
{
	if (index >= this->Size())
	{
		throw std::out_of_range("index > size");
	}

	if (index < begin_.size())
	{
		return begin_[begin_.size() - index - 1];
	}

	return end_[index - begin_.size()];
}


template <typename T>
T& Deque<T>::Front()
{
	if (!begin_.empty())
	{
		return begin_.back();
	}
	return end_.front();
}


template <typename T>
const T& Deque<T>::Front() const
{
	if (!begin_.empty())
	{
		return begin_.back();
	}
	return end_.front();
}

template <typename T>
T& Deque<T>::Back()
{
	if (!end_.empty())
	{
		return end_.back();
	}
	return begin_.front();
}

template <typename T>
const T& Deque<T>::Back() const
{
	if (!end_.empty())
	{
		return end_.back();
	}
	return begin_.front();
}

template <typename T>
void Deque<T>::PushFront(const T& elem)
{
	begin_.push_back(elem);
}

template <typename T>
void Deque<T>::PushBack(const T& elem)
{
	end_.push_back(elem);
}