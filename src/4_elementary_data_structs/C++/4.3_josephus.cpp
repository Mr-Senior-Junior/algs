#include <iostream>


// Из N элементов итеративно удаляют M-й элемент
static const int N = 9;
static const int M = 5;



template <typename T>
struct Node {
	Node (T val, Node* next) : val(val), next(next) {}

	T val;
	Node* next;
};

void list_solution()
{
	using IntNode = Node<int>;
	IntNode* head = new IntNode(1, nullptr);
	head->next = head;

	IntNode* currentNode = head;
	for (int i = 2; i <= N; ++i) {
		currentNode = (currentNode->next = new IntNode(i, head));
	}

	while (currentNode != currentNode->next) {
		for (int i = 1; i < M; ++i) {
			currentNode = currentNode->next;
		}
		IntNode* tmp = currentNode->next;
		currentNode->next = currentNode->next->next;
		delete tmp;
	}

	std::cout << currentNode->val << std::endl;
	delete currentNode;
}


void array_solution()
{
	int array[N];
	int i = 0;
	for (i = 0; i < N - 1; ++i) {
		array[i] = i + 1;
	}
	array[i] = 0;


	while (i != array[i]) {
		for (int j = 1; j < M; ++j) {
			i = array[i];
		}
		array[i] = array[array[i]]; 
	}

	std::cout << array[i] + 1 << std::endl;
}


int main(int, char**)
{
	list_solution();
	array_solution();

	return 0;
}
