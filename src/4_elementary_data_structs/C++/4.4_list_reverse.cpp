#include <iostream>


static const int N = 10;
// Количество элементов в списке


template <typename T>
struct Node
{
	Node(T val, Node* next) : val(val), next(next) {}

	T val;
	Node* next;
};


template <typename T>
concept IsOutEnable = requires (T val)
{
	std::cout << val;
};


template <IsOutEnable T>
void printList(Node<T>* head)
{
	std::cout << "[";
	while (head) {
		std::cout << head->val;
		head = head->next;
		if (head) {
			std::cout << ", ";
		}
	}
	std::cout << "]\n";
}



void reverse()
{
	using IntNode = Node<int>;
	IntNode* head = nullptr;
	IntNode** inserter = &head;

	for (int i = 0; i < N; ++i) {
		*inserter = new IntNode(i, nullptr);
		inserter = &(*inserter)->next;
	}
	printList(head);


	IntNode* prev = nullptr;
	while (head) {
		std::swap(head->next, prev);
		std::swap(prev, head);
	}
	head = prev;
	printList(head);


	IntNode* tmp = nullptr;
	while (head) {
		tmp = head;
		head = head->next;
		delete tmp;
	}
}




int main(int, char**)
{
	reverse();

	return 0;
}