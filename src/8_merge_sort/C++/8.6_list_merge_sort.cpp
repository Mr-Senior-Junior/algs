#include "collections_helper.h"
#include <iostream>
#include <vector>
#include <ranges>
#include <queue>





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






template <std::default_initializable Node> 
	requires
		requires(Node n) {
			n.val;
			n.next;
			{n.next++} -> std::same_as<Node*>;
		}
Node* merge(Node* l1, Node* l2)
{
	Node dummy;
	dummy.val = 0;
	dummy.next = nullptr;
	Node* current = &dummy;

	while (l1 && l2) {
		if (l1->val < l2->val) {
			current = current->next = l1;
			l1 = l1->next;
		} else {
			current = current->next = l2;
			l2 = l2->next;
		}
	}

	current->next = (l1 ? l1 : l2);
	return dummy.next;
}



template <std::default_initializable Node> 
	requires
		requires(Node n) {
			n.val;
			n.next;
			{n.next++} -> std::same_as<Node*>;
		}
Node* merge_sort(Node* list)
{
	if (!list || !list->next) {
		return list;
	}

	Node* slow = list;
	Node* fast = list->next;

	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}

	Node* leftList = list;
	Node* rightList = slow->next;
	slow->next = nullptr;

	return merge(merge_sort(leftList), merge_sort(rightList));
}


template <std::default_initializable Node> 
	requires
		requires(Node n) {
			n.val;
			n.next;
			{n.next++} -> std::same_as<Node*>;
		}
Node* down_up_merge_sort(Node* list)
{
	if (!list || !list->next) {
		return list;
	}

	std::queue<Node*> q;

	for (auto tmp = list; list->next; list = tmp) {
		tmp = list->next;
		list->next = nullptr;
		q.push(list);
	}

	Node* a = nullptr;
	Node* b = nullptr;
	while (!q.empty()) {
		q.push(list);
		a = q.front();
		q.pop();
		b = q.front();
		q.pop();
		list = merge(a, b);
	}

	return list;
}




static const int SIZE = 20;



int main(int, char**)
{
	using Type = Node<int>;
	Type* list = nullptr;
	for (auto i : std::ranges::views::iota(0, SIZE)) {
		(void)i;
		list = new Type(get_random_int(), list);
	}

	print_collection(list->begin(), list->end());

	// Type* result = merge_sort(list);
	Type* result = down_up_merge_sort(list);

	print_collection(result->begin(), result->end());


	Type* tmp = nullptr;
	while (list) {
		tmp = list;
		list = list->next;
		delete tmp;
	}

	return 0;
}
