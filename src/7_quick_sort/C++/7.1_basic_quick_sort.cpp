#include "collections_helper.h"
#include <iostream>
#include <vector>


// #define WITH_ITERATORS



#ifdef WITH_ITERATORS

template <comparable_iter_value Iter>
void basic_quic_sort(Iter begin, Iter end)
{
	if (std::distance(begin, end) <= 1) {
		return;
	}

	// partition. take last element as supported and go through collection with 2 iterators: left and right
	using ValueType = std::decay_t<decltype(*begin)>;
	Iter supElemIt = std::prev(end);
	ValueType& supElem = *supElemIt; 

	Iter leftIt = begin;
	Iter rightIt = supElemIt;

	while (*leftIt < supElem) { std::advance(leftIt, 1); }
	while (true) {
		do { std::advance(rightIt, -1); } while (supElem < *rightIt && leftIt != rightIt);
		if (leftIt >= rightIt) {
			break;
		}
		std::iter_swap(leftIt, rightIt);
		do { std::advance(leftIt, 1); } while (*leftIt < supElem);
	}
	std::swap(leftIt, supElemIt);


	basic_quic_sort(begin, leftIt);
	basic_quic_sort(std::next(leftIt), end);
}

#else

template <is_cmp_array Array>
void basic_quic_sort(Array& arr, int l, int r)
{
	if (r - l < 1) {
		return;
	}

	using Elem = std::decay_t<decltype(arr[l])>;

	int i = l - 1;
	int j = r;
	Elem& supportElem = arr[r];

	while (true) {
		while (arr[++i] < supportElem);
		while (supportElem < arr[--j] && j > i);
		if (i >= j) {
			break;
		}
		std::swap(arr[i], arr[j]);
	}
	std::swap(arr[i], arr[r]);

	basic_quic_sort(arr, l, i - 1);
	basic_quic_sort(arr, i + 1, r);
}

#endif





static const int SIZE = 1000000;



int main(int, char**)
{
	std::vector<int> vec;
	vec.reserve(SIZE);
	random_init(std::back_inserter(vec), SIZE);


	std::cout << std::ranges::is_sorted(vec) << std::endl;
	// print_collection(vec);

#ifdef WITH_ITERATORS
	std::cout << function_execution_time(basic_quic_sort<decltype(vec.begin())>, vec.begin(), vec.end()) << " ms" << std::endl;
#else
	std::cout << function_execution_time(basic_quic_sort<decltype(vec)>, vec, 0, SIZE - 1) << " ms" << std::endl;
#endif
	
	std::cout << std::ranges::is_sorted(vec) << std::endl;
	// print_collection(vec);


	return 0;
}




