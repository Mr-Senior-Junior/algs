#include "collections_helper.h"
#include <iostream>
#include <vector>
#include <stack>


// #define WITH_ITERATORS



static const int M = 10;




#ifdef WITH_ITERATORS


template <comparable_iter_value Iter>
void insertion_sort(Iter begin, Iter end)
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
void median(Iter begin, Iter end)
{
	auto left = begin;
	auto right = std::prev(end);
	auto mid = std::prev(right);
	std::iter_swap(std::next(begin, std::distance(begin, end) / 2), mid);
	if (*mid < *left) std::iter_swap(mid, left);
	if (*right < *left) std::iter_swap(right, left);
	if (*right < *mid) std::iter_swap(right, mid);
}



template <comparable_iter_value Iter>
void stack_quic_sort(Iter begin, Iter end)
{
	auto dis = std::distance(begin, end);
	if (dis <= M) {
		return;
	}

	using Node = std::pair<Iter, Iter>;
	std::vector<Node> buffer;
	buffer.reserve(static_cast<int>(std::log2(dis) + 1));
	std::stack<Node, std::vector<Node>> stack(buffer);


	using ValueType = std::decay_t<decltype(*begin)>;
	Iter supElemIt, left, right;

	while (true) {
		median(begin, end);
		supElemIt = std::prev(end, 2);
		left = std::next(begin);
		right = supElemIt;
		ValueType& supElemVal = *supElemIt;
		while (*left < supElemVal) { std::advance(left, 1); }
		while (true) {
			do { std::advance(right, -1); } while (supElemVal < *right && left != right);
			if (left >= right) {
				break;
			}
			std::iter_swap(left, right);
			do { std::advance(left, 1); } while (*left < supElemVal);
		}
		std::iter_swap(left, supElemIt);

		auto leftSize = std::distance(begin, left);
		auto rightSize = std::distance(std::next(left), end);
		if (leftSize > M && rightSize > M) {
			if (leftSize < rightSize) {
				stack.push({std::next(left), end});
				end = left;
			} else {
				stack.push({begin, left});
				begin = std::next(left);
			}
		} else if (leftSize > M && rightSize <= M) {
			end = left;
		} else if (leftSize <= M && rightSize > M) {
			begin = std::next(left);
		} else if (!stack.empty()) {
			std::tie(begin, end) = stack.top();
			stack.pop();
		} else {
			break;
		}
	};
}


template <comparable_iter_value Iter>
void median_stack_quick_sort(Iter begin, Iter end)
{
	stack_quic_sort(begin, end);
	insertion_sort(begin, end);
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
void median(Array& arr, int l, int r)
{
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
}


template <is_cmp_array Array>
void median_stack_quic_sort(Array& arr, int l, int r)
{
	if (r - l < M) {
		return;
	}

	std::stack<std::pair<int, int>> stack;

	using Elem = std::decay_t<decltype(arr[l])>;
	int i = 0, j = 0;
	while (true) {
		median(arr, l, r);
		i = l;
		j = r - 1;
		Elem& supportElem = arr[r - 1];
		while (true) {
			while (arr[++i] < supportElem);
			while (supportElem < arr[--j] && j > i);
			if (i >= j) {
				break;
			}
			std::swap(arr[i], arr[j]);
		}
		std::swap(arr[i], arr[r - 1]);

		int leftSize = i - l;
		int rightSize = r - i;
		if (leftSize > M && rightSize > M) {
			if (leftSize < rightSize) {
				stack.push({i + 1, r});
				r = i - 1;
			} else {
				stack.push({l, i - 1});
				l = i + 1;
			}
		} else if (leftSize > M && rightSize <= M) {
			r = i - 1;
		} else if (leftSize <= M && rightSize > M) {
			l = i + 1;
		} else if (!stack.empty()) {
			std::tie(l, r) = stack.top();
			stack.pop();
		} else {
			break;
		}
	}
}


template <is_cmp_array Array>
void median_stack_hybrid_sort(Array& arr, int l, int r)
{
	median_stack_quic_sort(arr, l, r);
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
	std::cout << function_execution_time(median_stack_quick_sort<decltype(vec.begin())>, vec.begin(), vec.end()) << " ms" << std::endl;
	std::cout << function_execution_time(median_stack_quick_sort<decltype(vec.begin())>, vec.begin(), vec.end()) << " ms" << std::endl;
#else
	std::cout << function_execution_time(median_stack_hybrid_sort<decltype(vec)>, vec, 0, SIZE - 1) << " ms" << std::endl;
#endif


	std::cout << std::ranges::is_sorted(vec) << std::endl;
	// print_collection(vec);



	return 0;
}
