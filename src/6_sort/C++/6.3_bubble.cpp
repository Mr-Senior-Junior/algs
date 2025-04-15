#include "collections_helper.h"
#include <iostream>
#include <chrono>




template <comparable_iter_value Iter>
void bubbleSort(Iter begin, Iter end)
{
	Iter preEndIt = std::prev(end);
	Iter tmp;
	size_t cmp_count = 0;
	for (auto it = begin; it != preEndIt; std::advance(it, 1)) {
		for (auto curr = preEndIt; curr != it; std::advance(curr, -1)) {
			tmp = std::move(std::prev(curr));
			if (*curr < *tmp) {
				std::swap(*curr, *tmp);
				++cmp_count;
			}
		}

		if (!cmp_count) {
			break;
		}
		cmp_count = 0;
	}
}




const int SIZE = 5000;



int main(int, char**)
{
	std::vector<int> vec;
	vec.reserve(SIZE);
	randomInit(std::back_inserter(vec), SIZE);

	std::cout << function_execution_time(bubbleSort<decltype(vec.begin())>, vec.begin(), vec.end()) << " ms" << std::endl;

	return 0;
}