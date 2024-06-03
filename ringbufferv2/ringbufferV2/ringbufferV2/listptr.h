#pragma once
#include <algorithm>

template <typename Type>
class SingleLinkedList
{
	// Узел списка
	struct Node
	{
		Node() = default;
		Node(const Type& value, Node* next): value_(value), next_node_(next){}

		Node* next_node_;
		Type value_;
	};

	template <typename ValueType>
	class BasicIterator
	{
	public:
		// Тип указателя на итерируемое значение
		using pointer = ValueType*;

		// Тип ссылки на итерируемое значение
		using reference = ValueType&;

		friend class SingleLinkedList<ValueType>;
		explicit BasicIterator(Node* node) : node_(node) {}


		[[nodiscard]] reference operator*() const noexcept {
			return node_->value_;
		}

		[[nodiscard]] pointer operator->() const noexcept {
			return &node_->value_;
		}

		BasicIterator& operator++() noexcept {
			node_ = node_->next_node_;
			return *this;
		}

		[[nodiscard]] bool operator==(const BasicIterator& other) const noexcept {
			return node_ == other.node_;
		}

		[[nodiscard]] bool operator!=(const BasicIterator& other) const noexcept {
			return node_ != other.node_;
		}
	private:
		Node* node_ = nullptr;
	};

public:

	// Итератор, допускающий изменение элементов списка
	using Iterator = BasicIterator<Type>;
	// Константный итератор, предоставляющий доступ для чтения к элементам списка
	using ConstIterator = BasicIterator<const Type>;

	[[nodiscard]] Iterator begin() noexcept {
		return Iterator{ head_.next_node_ };
	}

	[[nodiscard]] Iterator end() noexcept {
		return Iterator{ nullptr };
	}

	[[nodiscard]] ConstIterator cbegin() const noexcept {
		return ConstIterator{ head_.next_node_ };
	}

	[[nodiscard]] ConstIterator cend() const noexcept {
		return ConstIterator{ nullptr };
	}

	SingleLinkedList() : head_(), size_(0) {};

	// Запрет на копирование
	SingleLinkedList& operator=(const SingleLinkedList) = delete;
	
	~SingleLinkedList() { Clear(); };

	Type* Get()
	{
		return &head_;
	}

	void swap(SingleLinkedList& other) noexcept
	{
		std::swap(head_.next_node_, other.head_.next_node_);
		std::swap(size_, other.size_);
	}

	// Возвращает ссылку на элемент списка с индексом index
	Type& operator[](size_t index) noexcept {
		Node* current_node = head_.next_node_;

		for (size_t i = 0; i < index; ++i)
		{
			current_node = current_node->next_node_;
		}
		return current_node->value_;
	}

	// Возвращает константную ссылку на элемент списка с индексом index
	const Type& operator[](size_t index) const noexcept {
		Node* current_node = head_->next_node_;

		for (size_t i = 0; i < index; ++i)
		{
			current_node = current_node->next_node_;
		}
		return current_node->value_;
	}

	[[nodiscard]] bool IsEmpty() const noexcept {
		return (size_ == 0) ? true : false;
	}

	void PushFront(const Type& value) {
		head_.next_node_ = new Node(value, head_.next_node_);
		++size_;
	}

	void PopFront() noexcept {
		if (!IsEmpty())
		{	
			// Новая вспомогательная node
			Node* current_node = head_.next_node_;
			head_.next_node_ = head_.next_node_->next_node_;
			delete current_node;
			--size_;
		}
	}

	void PushBack(const Type& value)
	{
		// Новая nodа
		Node* new_node_ = new Node(value, nullptr);

		// Если список пуст
		if (IsEmpty())
		{
			head_.next_node_ = new_node_;
		}
		else
		{
			Node* current_node = head_.next_node_;
			while (current_node->next_node_ != nullptr)
			{
				current_node = current_node->next_node_;
			}
			current_node->next_node_ = new_node_;
		}
		++size_;
	}

	void PopBack() noexcept
	{
		if (IsEmpty())
		{
			return;
		}
		else if (size_ == 1)
		{
			delete head_.next_node_;
			head_.next_node_ = nullptr;
		}
		else
		{
			// Предпоследняя нода
			Node* prev = head_.next_node_;

			// Ноду которую надо удалить
			Node* delete_node = head_.next_node_;

			while (delete_node->next_node_ != nullptr)
			{
				// Последний узел, в котором есть значение.
				prev = delete_node;
				delete_node = delete_node->next_node_;
			}
			delete delete_node;

			prev->next_node_ = nullptr;
			--size_;
		}
	}

	void Clear() noexcept {
		PopFront();
	}

private:
	size_t size_ = 0;
	Node head_ = nullptr;
};