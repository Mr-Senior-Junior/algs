#include "collections_helper.h"
#include <iostream>
#include <vector>



// #define WITH_ITERATORS



static const int M = 10;




#ifdef WITH_ITERATORS

template <comparable_iter_value Iter>
void insertion_sort_advance(Iter begin, Iter end)
{
	auto dis = std::distance(begin, end);
	if (dis <= 1) {
		return;
	}

	Iter prevIt;
	for (auto it = std::prev(end); it != begin; it = std::move(prevIt)) {
		prevIt = std::move(std::prev(it));
		if (*it < *prevIt) {
			std::iter_swap(it, prevIt);
		}
	}


	using ValType = std::decay_t<decltype(*begin)>;
	for (auto it = std::next(begin, 2); it != end; std::advance(it, 1)) {
		prevIt = std::move(std::prev(it));
		ValType currentCheckVal = std::move(*it);
		while (currentCheckVal < *prevIt) {
			*std::next(prevIt) = std::move(*prevIt);
			std::advance(prevIt, -1);
		}
		*std::next(prevIt) = std::move(currentCheckVal);
	}
}


template <comparable_iter_value Iter>
void median_quic_sort(Iter begin, Iter end)
{
	auto dis = std::distance(begin, end);
	if (dis <= M) {
		return;
	}


	{
		auto left = begin;
		auto right = std::prev(end);
		auto mid = std::prev(right);
		std::iter_swap(std::next(begin, dis / 2), mid);
		if (*mid < *left) std::iter_swap(mid, left);
		if (*right < *left) std::iter_swap(right, left);
		if (*right < *mid) std::iter_swap(right, mid);
	}


	using ValueType = std::decay_t<decltype(*begin)>;
	Iter supElemIt = std::prev(end, 2);
	ValueType& supElemVal = *supElemIt; 

	Iter leftIt = std::next(begin);
	Iter rightIt = supElemIt;

	while (*leftIt < supElemVal) { std::advance(leftIt, 1); }
	while (true) {
		do { std::advance(rightIt, -1); } while (supElemVal < *rightIt && leftIt != rightIt);
		if (leftIt >= rightIt) {
			break;
		}
		std::iter_swap(leftIt, rightIt);
		do { std::advance(leftIt, 1); } while (*leftIt < supElemVal);
	}
	std::iter_swap(leftIt, supElemIt);


	median_quic_sort(begin, leftIt);
	median_quic_sort(std::next(leftIt), end);
}


template <comparable_iter_value Iter>
void median_hybrid_sort(Iter begin, Iter end)
{
	median_quic_sort(begin, end);
	insertion_sort_advance(begin, end);
}

#else


template <is_cmp_array Array>
void insertion_sort_advance(Array& arr, int l, int r)
{
	if (r - l < 1) {
		return;
	}

	for (int i = r; i > l; --i) {
		if (arr[i] < arr[i - 1]) {
			std::swap(arr[i], arr[i - 1]);
		}
	}

	using Elem = std::decay_t<decltype(arr[l])>;
	int j = 0;
	for (int i = l + 2; i <= r; ++i) {
		j = i;
		Elem buffer = std::move(arr[i]);
		while (buffer < arr[j - 1]) {
			arr[j] = std::move(arr[j - 1]);
			--j;
		}
		arr[j] = std::move(buffer);
	}
}


template <is_cmp_array Array>
void median_quic_sort(Array& arr, int l, int r)
{
	if (r - l < M) {
		return;
	}


	
	std::swap(arr[(r + l) / 2], arr[r - 1]);
	if (arr[r - 1] < arr[l]) {
		std::swap(arr[r - 1], arr[l]);
	}
	if (arr[r] < arr[l]) {
		std::swap(arr[r], arr[l]);
	}
	if (arr[r] < arr[r - 1]) {
		std::swap(arr[r], arr[r - 1]);
	}
	
	
	using Elem = std::decay_t<decltype(arr[l])>;
	Elem& supportElem = arr[r - 1];
	int i = l;
	int j = r - 1;

	while (true) {
		while (arr[++i] < supportElem);
		while (supportElem < arr[--j] && j > i);
		if (i >= j) {
			break;
		}
		std::swap(arr[i], arr[j]);
	}
	std::swap(arr[i], arr[r - 1]);

	median_quic_sort(arr, l, i - 1);
	median_quic_sort(arr, i + 1, r);
}


template <is_cmp_array Array>
void median_hybrid_sort(Array& arr, int l, int r)
{
	median_quic_sort(arr, l, r);
	insertion_sort_advance(arr, l, r);
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
	std::cout << function_execution_time(median_hybrid_sort<decltype(vec.begin())>, vec.begin(), vec.end()) << " ms" << std::endl;
#else
	std::cout << function_execution_time(median_hybrid_sort<decltype(vec)>, vec, 0, SIZE - 1) << " ms" << std::endl;
#endif


	std::cout << std::ranges::is_sorted(vec) << std::endl;
	// print_collection(vec);



	return 0;
}
