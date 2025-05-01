#include "collections_helper.h"
#include <iostream>
#include <chrono>



// #define WITH_ITERATORS



#ifdef WITH_ITERATORS

template <comparable_iter_value Iter>
void bubble_sort(Iter begin, Iter end)
{
	Iter preEndIt = std::prev(end);
	Iter tmp;
	size_t cmpСount = 0;
	for (auto it = begin; it != preEndIt; std::advance(it, 1)) {
		for (auto curr = preEndIt; curr != it; std::advance(curr, -1)) {
			tmp = std::move(std::prev(curr));
			if (*curr < *tmp) {
				std::swap(*curr, *tmp);
				++cmpСount;
			}
		}

		if (!cmpСount) {
			break;
		}
		cmpСount = 0;
	}
}

#else

template <is_cmp_array Array>
void bubble_sort(Array& arr, int l, int r)
{
	int cmpСnt = 0;
	for (int i = l; i < r; ++i) {
		cmpСnt = 0;
		for (int j = r; j > i; --j) {
			if (arr[j] < arr[j - 1]) {
				std::swap(arr[j], arr[j - 1]);
				++cmpСnt;
			}
		}
		if (!cmpСnt) {
			break;
		}
	}
}

#endif




const int SIZE = 50000;



int main(int, char**)
{
	std::vector<int> vec;
	vec.reserve(SIZE);
	random_init(std::back_inserter(vec), SIZE);


#ifdef WITH_ITERATORS
	std::cout << function_execution_time(bubble_sort<decltype(vec.begin())>, vec.begin(), vec.end()) << " ms" << std::endl;
#else
	std::cout << function_execution_time(bubble_sort<decltype(vec)>, vec, 0, SIZE - 1) << " ms" << std::endl;
#endif


	return 0;
}