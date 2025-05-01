#include "collections_helper.h"
#include <iostream>
#include <vector>



// #define WITH_ITERATORS




#ifdef WITH_ITERATORS

template <comparable_iter_value Iter>
void three_way_quick_sort(Iter begin, Iter end)
{
	auto dis = std::distance(begin, end);
	if (dis <= 1) {
		return;
	}


	using ValueType = std::decay_t<decltype(*begin)>;
	Iter supElemIt = std::prev(end);
	ValueType& supElemVal = *supElemIt;

	Iter left = begin;
	Iter right = supElemIt;

	Iter leftSupEq = left;
	Iter rightSupEq = std::prev(right);



	while (*left < supElemVal) { std::advance(left, 1); }
	while (true) {
		do { std::advance(right, -1); } while (supElemVal < *right && left != right);
		if (left >= right) {
			break;
		}
		std::iter_swap(left, right);
		if (*left == supElemVal) {
			std::iter_swap(leftSupEq, left);
			std::advance(leftSupEq, 1);
		}
		if (*right == supElemVal) {
			std::iter_swap(rightSupEq, right);
			std::advance(rightSupEq, -1);
		}

		do { std::advance(left, 1); } while (*left < supElemVal);
	}
	std::iter_swap(left, supElemIt);
	right = std::next(left);

	if (left != begin) {
		for (auto it = begin; it != leftSupEq; std::advance(it, 1)) {
			std::advance(left, -1);
			std::iter_swap(it, left);
		}
	}
	if (right != std::prev(end)) {
		for (auto it = std::prev(end, 2); it != rightSupEq; std::advance(it, -1), std::advance(right, 1)) {
			std::iter_swap(it, right);
		}
	}

	three_way_quick_sort(begin, left);
	three_way_quick_sort(right, end);
}

#else

template <is_cmp_array Array>
void three_way_quick_sort(Array& arr, int l, int r)
{
	if (r - l < 1) {
		return;
	}

	using Elem = std::decay_t<decltype(arr[l])>;
	int i = l - 1;
	int supEqleft = l;

	int j = r;
	int supEqRight = r - 1;

	Elem& supportElem = arr[r];
	while (true) {
		while (arr[++i] < supportElem);
		while (supportElem < arr[--j] && i < j);
		if (j <= i) {
			break;
		}
		std::swap(arr[i], arr[j]);

		if (arr[i] == supportElem) {
			std::swap(arr[supEqleft++], arr[i]);
		}
		if (arr[j] == supportElem) {
			std::swap(arr[j], arr[supEqRight--]);
		}
	}
	std::swap(arr[i], arr[r]);
	j = i;

	while (supEqleft > l) {
		std::swap(arr[--supEqleft], arr[--i]);
	}
	while (supEqRight < r - 1) {
		std::swap(arr[++j], arr[++supEqRight]);
	}


	three_way_quick_sort(arr, l, i - 1);
	three_way_quick_sort(arr, j + 1, r);
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
	std::cout << function_execution_time(three_way_quick_sort<decltype(vec.begin())>, vec.begin(), vec.end()) << " ms" << std::endl;
#else
	std::cout << function_execution_time(three_way_quick_sort<decltype(vec)>, vec, 0, SIZE - 1) << " ms" << std::endl;
#endif


	std::cout << std::ranges::is_sorted(vec) << std::endl;
	// print_collection(vec);


	return 0;
}

