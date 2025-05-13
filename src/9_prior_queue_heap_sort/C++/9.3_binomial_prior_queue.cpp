#include "collections_helper.h"
#include <iostream>
#include <stdexcept>
#include <limits>


static const int ARRAY_SIZE = 64;




// очередь с приоритетом на базе биномиального дерева
template <typename Item>
class PriorityQueue
{
	struct Node {
		Node(Node* left, Node* right, const Item& val) :
			left(left),
			right(right),
			val(val) {}

		Node(const Item& val) :
			left(nullptr),
			right(nullptr),
			val(val) {}

		Node* left;
		Node* right;
		Item val;
	};

public:
	PriorityQueue() {
		for (int i = 0; i < ARRAY_SIZE; ++i) {
			m_treeArray[i] = nullptr;
		}
		m_elemSize = 0;
	}

	~PriorityQueue() {
		for (int i = 0; i < ARRAY_SIZE; ++i) {
			deleteTree(m_treeArray[i]);
		}
	}

	bool empty() const {
		return !m_elemSize;
	}

	void insert(const Item& value) {
		if (m_elemSize == std::numeric_limits<unsigned long long>::max()) {
			throw std::out_of_range("A lot of elements!");
		}

		Node* insertNode = new Node(value);
		for (int i = 0; i < ARRAY_SIZE; ++i) {
			if (m_treeArray[i]) {
				insertNode = pair(m_treeArray[i], insertNode);
				m_treeArray[i] = nullptr;
				continue;
			}
			m_treeArray[i] = insertNode;
			break;
		}
		++m_elemSize;
	}

	Item getMax() {
		if (!m_elemSize) {
			throw std::out_of_range("There is not any elements in queue");
		}
		int index = -1;
		while (!m_treeArray[++index]);
		int maxIndex = index++;
		for (; index < ARRAY_SIZE; ++index) {
			if (!m_treeArray[index]) {
				continue;
			}

			if (m_treeArray[index]->val > m_treeArray[maxIndex]->val) {
				maxIndex = index;
			}
		}

		Node* maxNode = m_treeArray[maxIndex];
		m_treeArray[maxIndex] = nullptr;
		if (maxIndex != 0) {
			Node* tmpArr[ARRAY_SIZE];
			for (int i = 0; i < ARRAY_SIZE; ++i) {
				tmpArr[i] = nullptr;
			}
			Node* tmpNode = maxNode->left;
			for (int i = maxIndex - 1; i >= 0; --i) {
				tmpArr[i] = tmpNode;
				tmpNode = tmpNode->right;
				tmpArr[i]->right = nullptr;
			}
			merge(m_treeArray, tmpArr);
		}

		Item result = std::move(maxNode->val);
		delete maxNode;
		--m_elemSize;
		return result;
	}

	template <typename Type> requires std::same_as<Item, Type>
	void merge(PriorityQueue<Type>& pq) {
		if (std::numeric_limits<unsigned long long>::max() - m_elemSize < pq.m_elemSize) {
			throw std::out_of_range("A lot of elements!");
		}
		merge(m_treeArray, pq.m_treeArray);
		m_elemSize += pq.m_elemSize;
		pq.m_elemSize = 0;
		for (int i = 0; i < ARRAY_SIZE; ++i) {
			pq.m_treeArray[i] = nullptr;
		}
	}


private:
	void deleteTree(Node* node) {
		if (!node) {
			return;
		}

		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}

	Node* pair(Node* first, Node* second) {
		if (first->val > second->val) {
			second->right = first->left;
			first->left = second;
			return first;
		}

		first->right = second->left;
		second->left = first;
		return second;
	}

	void merge(Node** a, Node** b) {
		auto test = [](bool c, bool b, bool a) { return static_cast<int>(c) * 4 +
														static_cast<int>(b) * 2 +
														static_cast<int>(a) * 1; };

		Node* c = nullptr;
		for (int i = 0; i < ARRAY_SIZE; ++i) {
			switch (test(c, b[i], a[i])) {
				case 2:
					a[i] = b[i];
					break;
				case 3:
					c = pair(a[i], b[i]);
					a[i] = nullptr;
					break;
				case 4:
					a[i] = c;
					c = nullptr;
					break;
				case 5:
					c = pair(c, a[i]);
					a[i] = nullptr;
					break;
				case 6:
				case 7:
					c = pair(c, b[i]);
					break;
			}
		}
	}



private:
	Node* m_treeArray[ARRAY_SIZE];
	unsigned long long m_elemSize;
};









int main(int, char**)
{
	PriorityQueue<int> pq1;
	pq1.insert(23);
	pq1.insert(1);
	pq1.insert(54);
	pq1.insert(100);
	pq1.insert(2345);
	pq1.insert(3);
	pq1.insert(78);
	pq1.insert(9);
	pq1.insert(123);
	pq1.insert(393);


	PriorityQueue<int> pq2;
	pq2.insert(222);
	pq2.insert(333);
	pq2.insert(444);
	pq2.insert(555);


	std::cout << pq1.getMax() << std::endl;
	std::cout << pq2.getMax() << std::endl;

	pq1.merge(pq2);

	while (!pq1.empty()) {
		std::cout << pq1.getMax() << " ";
	}
	std::cout << std::endl;


	return 0;
}
