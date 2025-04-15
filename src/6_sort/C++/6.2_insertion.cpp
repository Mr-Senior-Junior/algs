#include "collections_helper.h"
#include <iostream>
#include <chrono>



// Simple implementation without optimizations
template <comparable_iter_value Iter>
void insertionSort_v1(Iter begin, Iter end)
{
	Iter prevIt;
	for (auto it = std::next(begin); it != end; std::advance(it, 1)) {
		for (auto curr = it; curr != begin; std::advance(curr, -1)) {
			prevIt = std::move(std::prev(curr));
			if (*curr < *prevIt) {
				std::iter_swap(curr, prevIt);
			}
		}
	}
}


// Implementation with inner `for` check
template <comparable_iter_value Iter>
void insertionSort_v2(Iter begin, Iter end)
{
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


// Perfect implementation
template <comparable_iter_value Iter>
void insertionSort_v3(Iter begin, Iter end)
{
	// move min element at first pos. It's like signal key for following code
	Iter prevIt;
	for (auto it = std::prev(end); it != begin; std::advance(it, -1)) {
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




const int SIZE = 5000;



int main(int, char**)
{
	std::vector<int> vec;
	vec.reserve(SIZE);
	randomInit(std::back_inserter(vec), SIZE);


#if 0
	std::cout << function_execution_time(insertionSort_v1<decltype(vec.begin())>, vec.begin(), vec.end()) << " ms" << std::endl;
#endif

#if 0
	std::cout << function_execution_time(insertionSort_v2<decltype(vec.begin())>, vec.begin(), vec.end()) << " ms" << std::endl;
#endif

#if 1
	std::cout << function_execution_time(insertionSort_v3<decltype(vec.begin())>, vec.begin(), vec.end()) << " ms" << std::endl;
#endif

	return 0;
}

