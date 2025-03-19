#include <iostream>
#include <random>


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



void insertSort()
{
	using IntNode = Node<int>;

	std::random_device dev;
	std::mt19937 gen(dev());
	std::uniform_int_distribution dist(1, 100);

	IntNode* head = nullptr;
	IntNode** inserter = &head;
	for (int i = 0; i < N; ++i) {
		*inserter = new IntNode(dist(gen), nullptr);
		inserter = &(*inserter)->next;
	}
	printList(head);


	IntNode* tmp = nullptr;
	IntNode* i = nullptr;
	IntNode newPrevHead = IntNode(0, nullptr);
	while (head) {
		tmp = head->next;
		for (i = &newPrevHead; i->next; i = i->next) {
			if (i->next && i->next->val >= head->val) {
				break;
			}
		}
		head->next = i->next;
		i->next = head;

		head = tmp;
	}
	head = newPrevHead.next;
	printList(head);


	while (head) {
		tmp = head;
		head = head->next;
		delete tmp;
	}
}



int main(int, char**)
{
	insertSort();

	return 0;
}
