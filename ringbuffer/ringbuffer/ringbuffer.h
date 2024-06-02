#pragma once

#include "arrayptr.h"
#include <algorithm>
#include <stdexcept>
#include <utility>

template <typename T>
class ringbuffer
{
public:

	using Iterator = T*;
	using ConstIterator = const T*;

	ringbuffer() noexcept = default;

	explicit ringbuffer(size_t capacity) : value_(capacity), size_(0), capacity_(capacity)
	{
		for (size_t i = 0; i < size_; ++i) {
			value_[i] = 0;
		}
	}

	~ringbuffer() = default;

	ringbuffer& operator=(const ringbuffer& rhs) {
		if (&rhs == this)
		{
			return *this;
		}
		ringbuffer tmp(rhs);
		swap(tmp);
		return *this;
	}

	ringbuffer(const ringbuffer& other): capacity_(other.capacity_), size_(other.size_), value_(other.value_)
	{
		std::copy(other.begin(), other.end(), begin());
	}

	bool isEmpty() const noexcept
	{
		return size_ == 0;
	}

	void push_back(const T& value)
	{
		if (size_ == capacity_) {
			// Если буфер заполнен, удаляем первый элемент
			for (size_t i = 0; i < size_ - 1; ++i) {
				value_[i] = value_[i + 1];
			}
			value_[size_ - 1] = value;
			return;
		}

		// Добавляем новый элемент в конец
		value_[size_] = value;

		// Увеличиваем размер
		++size_;
	}

	void push_front(const T& value)
	{
		if (size_ == capacity_) {
			// Если буфер заполнен, удаляем последний элемент
			for (size_t i = size_ - 1; i > 0; --i) {
				value_[i] = value_[i - 1];
			}
			value_[0] = value;
			return;
		}

		// Сдвигаем все элементы вправо
		for (size_t i = size_; i > 0; --i) {
			value_[i] = value_[i - 1];
		}

		value_[0] = value;

		++size_;
	}

	void pop_back()
	{
		if (size_ == 0) {
			throw std::underflow_error("Удалены все элементы");
		}
		--size_;
	}

	void pop_front()
	{
		if (size_ == 0) {
			throw std::underflow_error("Удалены все элементы");
		}

		// Сдвигаем все элементы на один влево
		for (size_t i = 0; i < size_ - 1; ++i) {
			value_[i] = value_[i + 1];
		}

		// Уменьшаем размер буфера
		--size_;
	}

	void resize(size_t new_size) {
		if (new_size == size_) {
			return;
		}

		ArrayPtr<T> new_buffer(new_size);

		size_t elements_to_copy = std::min(size_, new_size);
		for (size_t i = 0; i < elements_to_copy; ++i) {
			new_buffer[i] = value_[i];
		}

		if (new_size > size_) {
			for (size_t i = elements_to_copy; i < new_size; ++i) {
				new_buffer[i] = T{};
			}
		}

		value_.swap(new_buffer);
		size_ = new_size;
		capacity_ = new_size;
	}

	void swap(ringbuffer& other) noexcept {
		std::swap(size_, other.size_);
		std::swap(capacity_, other.capacity_);
		value_.swap(other.value_);
	}

	T& operator[](size_t index) noexcept {
		assert(index < size_);
		return value_[index];
	}

	const T& operator[](size_t index) const noexcept {
		assert(index < size_);
		return value_[index];
	}

	size_t getsize()
	{
		return size_;
	}

	size_t getcapacity()
	{
		return capacity_;
	}

	Iterator begin() noexcept
	{
		return value_.Get();
	}

	ConstIterator begin() const noexcept
	{
		return value_.Get();
	}

	Iterator end() noexcept
	{
		return value_.Get() + size_;
	}

	ConstIterator end() const noexcept
	{
		return value_.Get() + size_;
	}

private:
	size_t capacity_ = 0;
	size_t size_ = 0;
	ArrayPtr<T> value_{};
};