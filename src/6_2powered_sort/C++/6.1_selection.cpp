#include "collections_helper.h"
#include <vector>
#include <chrono>


// #define WITH_ITERATORS



#ifdef WITH_ITERATORS

template <comparable_iter_value Iter>
void selection_sort(Iter begin, Iter end)
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

#else

template <is_cmp_array Array>
void selection_sort(Array& arr, int l, int r)
{
	int minInd = 0;
	for (int i = l; i < r; ++i) {
		minInd = i;
		for (int j = i + 1; j <= r; ++j) {
			if (arr[j] < arr[minInd]) {
				minInd = j;
			}
		}
		std::swap(arr[i], arr[minInd]);
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
	std::cout << function_execution_time(selection_sort<decltype(vec.begin())>, vec.begin(), vec.end()) << " ms" << std::endl;
#else
	std::cout << function_execution_time(selection_sort<decltype(vec)>, vec, 0, SIZE - 1) << " ms" << std::endl;
#endif

	return 0;
}