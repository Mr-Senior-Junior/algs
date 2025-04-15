#include "collections_helper.h"
#include <vector>
#include <chrono>



template <comparable_iter_value Iter>
void selectionSort(Iter begin, Iter end)
{
	auto preEnd = std::prev(end);
	auto min = begin;
	for (auto it = begin; it != preEnd; std::advance(it, 1)) {
		min = it;
		for (auto current = std::next(it); current != end; std::advance(current, 1)) {
			if (*current < *min) {
				min = current;
			}
		}
		std::swap(*min, *it);
	}
}




const int SIZE = 5000;



int main(int, char**)
{
	std::vector<int> vec;
	vec.reserve(SIZE);
	randomInit(std::back_inserter(vec), SIZE);

	std::cout << function_execution_time(selectionSort<decltype(vec.begin())>, vec.begin(), vec.end()) << " ms" << std::endl;

	return 0;
}