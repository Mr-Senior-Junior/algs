#include "collections_helper.h"
#include <iostream>
#include <chrono>



// #define WITH_ITERATORS


#ifdef WITH_ITERATORS


// basic implementation
template <comparable_iter_value Iter>
void insertion_sort_basic(Iter begin, Iter end)
{
	auto dis = std::distance(begin, end);
	if (dis <= 1) {
		return;
	}

	Iter prevIt;
	for (auto it = std::next(begin); it != end; std::advance(it, 1)) {
		for (auto curr = it; curr != begin; std::advance(curr, -1)) {
			prevIt = std::move(std::prev(curr));
			if (*curr >= *prevIt) {
				break;
			}
			std::iter_swap(curr, prevIt);
		}
	}
}


// Advance implementation
template <comparable_iter_value Iter>
void insertion_sort_advance(Iter begin, Iter end)
{
	// move min element at first pos. It's like signal key for following code
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


#else

// basic implementation
template <is_cmp_array Array>
void insertion_sort_basic(Array& arr, int l, int r)
{
	for (int i = l + 1; i <= r; ++i) {
		for (int j = i - 1; j >= l; --j) {
			if (!(arr[j + 1] < arr[j])) {
				break;
			}
			std::swap(arr[j + 1], arr[j]);
		}
	}
}


// Advance implementation
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



#endif





static const int SIZE = 50000;



int main(int, char**)
{
	std::vector<int> vec;
	vec.reserve(SIZE);
	random_init(std::back_inserter(vec), SIZE);


#ifdef WITH_ITERATORS

#if 0 // basic implementation
	std::cout << function_execution_time(insertion_sort_basic<decltype(vec.begin())>, vec.begin(), vec.end()) << " ms" << std::endl;
#endif
#if 0 // advance implementation
	std::cout << function_execution_time(insertion_sort_advance<decltype(vec.begin())>, vec.begin(), vec.end()) << " ms" << std::endl;
#endif


#else


#if 0 // basic implementation
	std::cout << function_execution_time(insertion_sort_basic<decltype(vec)>, vec, 0, SIZE - 1) << " ms" << std::endl;
#endif
#if 1 // advance implementation
	std::cout << function_execution_time(insertion_sort_advance<decltype(vec)>, vec, 0, SIZE - 1) << " ms" << std::endl;
	#endif

#endif

	return 0;
}

