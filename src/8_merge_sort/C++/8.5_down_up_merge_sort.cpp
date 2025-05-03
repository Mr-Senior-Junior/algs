#include "collections_helper.h"
#include <iostream>
#include <vector>



// #define WITH_ITERATORS



#ifdef WITH_ITERATORS


template <comparable_iter_value Iter>
void merge(Iter begin, Iter mid, Iter end)
{
	auto dis = std::distance(begin, end);
	if (dis <= 1 || mid == end) {
		return;
	}
	if (begin == mid) {
		std::reverse(begin, end);
		return;
	}


	using value_type = std::decay_t<decltype(*begin)>;;
	std::vector<value_type> buf;
	buf.reserve(dis);

	buf.insert(buf.end(),
			   std::make_move_iterator(begin),
			   std::make_move_iterator(mid));
	buf.insert(buf.end(),
			   std::make_move_iterator(std::make_reverse_iterator(end)),
			   std::make_move_iterator(std::make_reverse_iterator(mid)));


	auto left = buf.begin();
	auto right = buf.rbegin();
	while (begin != end) {
		*begin++ = std::move(*left < *right ? *left++ : *right++);
	}
}


template <comparable_iter_value Iter>
void down_up_merge_sort(Iter begin, Iter end)
{
	using distance_type = decltype(std::distance(begin, end));

	distance_type dis = std::distance(begin, end);
	distance_type offset = 0;

	for (distance_type i = 1; i < dis; i += i) {
		for (distance_type j = 0; j < dis - i; j += i + i) {
			offset = std::min(dis - j, i + i);
			merge(std::next(begin, j),
				  std::next(begin, j + i),
				  std::next(begin, j + offset));
		}
	}
}


#else


template <
	is_cmp_array Array,
	is_cmp_array Buffer>
void abstract_exchange_merge(Array& arr, int l, int m, int r, Buffer& buf)
{
	for (int i = l; i <= m; ++i) {
		buf[i] = arr[i];
	}

	for (int i = 0; i < r - m; ++i) {
		buf[m + i + 1] = arr[r - i];
	}

	for (int k = l, left = l, right = r; k <= r; ++k) {
		arr[k] = (buf[left] < buf[right] ? buf[left++] : buf[right--]);
	}
}


template <is_cmp_array Array>
void down_up_merge_sort(Array& arr, int l, int r)
{
	using Elem = std::decay_t<decltype(arr[l])>;
	Elem* buf = new Elem[r - l + 1];

	int size = r - l + 1;
	for (int i = 1; i < size; i += i) {
		for (int j = 0; j < size - i; j += i + i) {
			abstract_exchange_merge(arr, j,
									j + i - 1,
									std::min(j + i + i - 1, r),
									buf);
		}
	}

	delete[] buf;
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
	std::cout << function_execution_time(down_up_merge_sort<decltype(vec.begin())>, vec.begin(), vec.end()) << " ms" << std::endl;
#else
	std::cout << function_execution_time(down_up_merge_sort<decltype(vec)>, vec, 0, SIZE - 1) << " ms" << std::endl;
#endif


	std::cout << std::ranges::is_sorted(vec) << std::endl;
	// print_collection(vec);


	return 0;
}