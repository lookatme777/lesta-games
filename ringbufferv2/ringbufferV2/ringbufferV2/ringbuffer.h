#pragma once
#include "listptr.h"
#include <algorithm>
#include <stdexcept>

template<typename T>
class ringbuffer
{
public:

    using Iterator = typename SingleLinkedList<T>::Iterator;
    using ConstIterator = typename SingleLinkedList<T>::ConstIterator;

    explicit ringbuffer(size_t capacity) : size_(0), capacity_(capacity), list_()
    {
    }

    ~ringbuffer() = default;

    bool isEmpty() const noexcept
    {
        return size_ == 0;
    }

    bool isFull() const noexcept
    {
        return size_ == capacity_;
    }

    void push_back(const T& value)
    {
        if (isFull())
        {
            pop_front();
        }
        list_.PushBack(value);
        if (!isFull())
        {
            ++size_;
        }
    }

    void push_front(const T& value)
    {
        if (isFull())
        {
            pop_back();
        }
        list_.PushFront(value);
        if (!isFull())
        {
            ++size_;
        }
    }

    void pop_front()
    {
        if (isEmpty())
        {
            throw std::underflow_error("Буфер пустой");
        }
        list_.PopFront();
        --size_;
    }

    void pop_back()
    {
        if (isEmpty())
        {
            throw std::underflow_error("Буфер пустой.");
        }
        list_.PopBack();
        --size_;
    }

    void resize(size_t new_size)
    {
        if (new_size == 0)
        {
            return;
        }

        SingleLinkedList<T> new_list;
        size_t elements_to_copy = std::min(new_size, size_);

        auto it = list_.begin();
        for (size_t i = 0; i < elements_to_copy; ++i, ++it)
        {
            new_list.PushBack(*it);
        }

        list_.swap(new_list);
        size_ = elements_to_copy;
        capacity_ = new_size;
    }

    void swap(ringbuffer& other) noexcept
    {
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_);
        list_.swap(other.list_);
    }

    size_t getsize() const noexcept
    {
        return size_;
    }

    size_t getcapacity() const noexcept
    {
        return capacity_;
    }

    Iterator begin() noexcept
    {
        return list_.begin();
    }

    ConstIterator begin() const noexcept
    {
        return list_.cbegin();
    }

    Iterator end() noexcept
    {
        return list_.end();
    }

    ConstIterator end() const noexcept
    {
        return list_.cend();
    }

private:
    size_t capacity_;
    size_t size_;
    SingleLinkedList<T> list_;
};