#include "collections_helper.h"
#include <iostream>
#include <ranges>



template <std::default_initializable T>
struct Node
{
	struct iterator
	{
		using iterator_category = std::forward_iterator_tag;
		using value_type = T;
		using difference_type = decltype(T() - T());
		using pointer = T*;
		using reference = T&;

		explicit iterator(Node<T>* node = nullptr) : node(node) {}
		iterator& operator++() { node = node->next; return *this; }
        iterator operator++(int) { iterator retval = *this; ++(*this); return retval; }
		auto operator<=>(const iterator& other_it) const = default;
		reference operator*() { return node->val; }

	private:
		Node<T>* node;
	};



	Node() : val(T()), next(nullptr) {}
	Node(T&& val) : val(std::forward<T>(val)), next(nullptr) {}
	Node(T&& val, Node* next) : val(std::forward<T>(val)), next(next) {}

	iterator begin() { return iterator(this); }
	iterator end() { return iterator(nullptr); }

	T val;
	Node* next;
};



template <typename T>
void list_selection_sort(Node<T>*& head)
{
	Node<T> dummy = Node<T>(T(), head);
	
	Node<T>* sortedList = nullptr;
	Node<T>* max = dummy.next;
	Node<T>* prevMax = &dummy;
	while (max) {
		for (auto node = max; node->next; node = node->next) {
			if (max->val < node->next->val) {
				max = node->next;
				prevMax = node;
			}
		}
		prevMax->next = max->next;
		max->next = sortedList;
		sortedList = max;

		max = dummy.next;
		prevMax = &dummy;
	}

	head = sortedList;
}


template <typename T>
void list_insertion_sort(Node<T>*& head)
{
	Node<T> dummySorted = Node<T>(T(), nullptr);
	Node<T>* node = nullptr;
	while (head) {
		node = &dummySorted;

		while (node->next && node->next->val < head->val) {
			node = node->next;
		}
		std::swap(head->next, node->next);
		std::swap(node->next, head);
	}

	head = dummySorted.next;
}

template <typename T>
void list_bubble_sort(Node<T>*& head)
{
	Node<T> dummy = Node<T>(T(), head);

	int size = 0;
	Node<T>* tmp = head;
	while (tmp) {
		size++;
		tmp = tmp->next;
	}

	Node<T>* prev = nullptr, * current = nullptr;
	int cnt = 0;
	for (int i = 0; i < size; ++i) {
		cnt = size - i - 1;
		prev = &dummy;
		current = dummy.next;
		while (cnt) {
			if (prev->next->val > current->next->val) {
				prev->next = current->next;
				current->next = current->next->next;
				prev->next->next = current;
				prev = prev->next;
			} else {
				prev = current;
				current = current->next;
			}

			--cnt;
		}
	}

	head = dummy.next;
}




const int SIZE = 20;



int main(int, char**)
{

	Node<int>* list = nullptr;
	for (auto i : std::ranges::views::iota(0, SIZE)) {
		(void)i;
		list = new Node<int>(get_random_int(), list);
	}



#if 0
	print_collection(list->begin(), list->end());
	list_selection_sort(list);
	print_collection(list->begin(), list->end());
#endif

#if 0
	print_collection(list->begin(), list->end());
	list_insertion_sort(list);
	print_collection(list->begin(), list->end());
#endif

#if 1
	print_collection(list->begin(), list->end());
	list_bubble_sort(list);
	print_collection(list->begin(), list->end());
#endif



	Node<int>* tmp = nullptr;
	while (list) {
		tmp = list;
		list = list->next;
		delete tmp;
	}

	return 0;
}