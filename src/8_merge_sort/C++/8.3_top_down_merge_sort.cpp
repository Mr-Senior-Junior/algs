#include "collections_helper.h"
#include <iostream>
#include <vector>



// #define WITH_ITERATORS



#ifdef WITH_ITERATORS


template <comparable_iter_value Iter>
void abstract_exchange_merge(Iter begin, Iter mid, Iter end)
{
	auto dis = std::distance(begin, end);
	if (dis <= 1) {
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
void top_down_merge_sort(Iter begin, Iter end)
{
	auto dis = std::distance(begin, end);
	if (dis <= 1) {
		return;
	}

	auto mid = std::next(begin, dis / 2);
	top_down_merge_sort(begin, mid);
	top_down_merge_sort(mid, end);
	abstract_exchange_merge(begin, mid, end);
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


template <
	is_cmp_array Array,
	is_cmp_array Buffer>
void top_down_merge_sort_impl(Array& arr, int l, int r, Buffer& buf)
{
	if (r <= l) {
		return;
	}

	int mid = (r + l) / 2;
	top_down_merge_sort_impl(arr, l, mid, buf);
	top_down_merge_sort_impl(arr, mid + 1, r, buf);
	abstract_exchange_merge(arr, l, mid, r, buf);
}

template <is_cmp_array Array>
void top_down_merge_sort(Array& arr, int l, int r)
{
	if (r <= l) {
		return;
	}

	using Elem = std::decay_t<decltype(arr[l])>;
	Elem* buf = new Elem[r - l + 1];
	top_down_merge_sort_impl(arr, l, r, buf);
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
	std::cout << function_execution_time(top_down_merge_sort<decltype(vec.begin())>, vec.begin(), vec.end()) << " ms" << std::endl;
#else
	std::cout << function_execution_time(top_down_merge_sort<decltype(vec)>, vec, 0, SIZE - 1) << " ms" << std::endl;
#endif

	std::cout << std::ranges::is_sorted(vec) << std::endl;
	// print_collection(vec);


	return 0;
}

