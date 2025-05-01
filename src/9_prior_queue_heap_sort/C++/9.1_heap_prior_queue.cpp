#include "collections_helper.h"
#include "heap_functions.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>



// очередь с приоритетом на базе пирамидального дерева (heap)
template <typename Item, typename Alloc = std::allocator<Item>>
class PriorityQueue
{
	using allocator_traits = std::allocator_traits<Alloc>;
public:
	PriorityQueue() : m_arr(nullptr), m_size(0), m_capacity(0) {}
	PriorityQueue(int cap) : m_size(0), m_capacity(cap) {
		m_arr = allocator_traits::allocate(m_alloc, cap + 1); // нулевой элемент не используется
	}

	~PriorityQueue() {
		for (int i = 1; i <= m_size; ++i) {
			allocator_traits::destroy(m_alloc, m_arr + i);
		}
		allocator_traits::deallocate(m_alloc, m_arr, m_capacity + 1);
	}


	bool empty() const noexcept {
		return m_size == 0;
	}
	void insert(const Item& item) {
		if (m_size == m_capacity) {
			allocateAndCopy(static_cast<int>((m_capacity ? m_capacity : 2) * 1.6));
		}

		m_size += 1;
		allocator_traits::construct(m_alloc, m_arr + m_size, item);
		fixUp(m_arr, m_size);
	}
	Item getMax() {
		if (!m_size) {
			throw std::runtime_error("There is not elements in priority queue!");
		}

		std::swap(m_arr[1], m_arr[m_size]);
		fixDown(m_arr, 1, m_size - 1);
		return m_arr[m_size--];
	}


private:
	void allocateAndCopy(int newCap) {
		Item* newArr = allocator_traits::allocate(m_alloc, newCap + 1);
		for (int i = 1; i <= m_size; ++i) {
			newArr[i] = std::move(m_arr[i]);
		}
		allocator_traits::deallocate(m_alloc, m_arr, m_capacity + 1);
		m_arr = newArr;
		m_capacity = newCap;
	}


private:
	Alloc m_alloc;
	Item* m_arr;
	int m_size;
	int m_capacity;
};




int main(int, char**)
{
	PriorityQueue<int> pq;
	for (int i = 0; i < 10; ++i) {
		pq.insert(get_random_int());
	}

	for (int i = 0; i < 10; ++i) {
		std::cout << pq.getMax() << " ";
	}
	std::cout << "\n";

	return 0;
}