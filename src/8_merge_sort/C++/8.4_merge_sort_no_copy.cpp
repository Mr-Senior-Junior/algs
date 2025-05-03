#include "collections_helper.h"
#include <iostream>
#include <vector>


// #define WITH_ITERATORS


static const int M = 9;




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


template <
	comparable_iter_value Iter1,
	comparable_iter_value Iter2,
	comparable_iter_value Iter3> requires 
							std::same_as<typename Iter1::value_type, typename Iter2::value_type> &&
							std::same_as<typename Iter1::value_type, typename Iter3::value_type>
void merge_no_copy(Iter1 src1Begin, Iter1 src1End,
				   Iter2 src2Begin, Iter2 src2End,
				   Iter3 dst)
{
	while (src1Begin != src1End && src2Begin != src2End) {
		*dst++ = *src1Begin < *src2Begin ? *src1Begin++ : *src2Begin++;
	}

	if (src1Begin == src1End) {
		while (src2Begin != src2End) {
			*dst++ = *src2Begin++;
		}
	}
	if (src2Begin == src2End) {
		while (src1Begin != src1End) {
			*dst++ = *src1Begin++;
		}
	}
}



template <
	comparable_iter_value Iter1,
	comparable_iter_value Iter2> requires
		std::same_as<typename Iter1::value_type, typename Iter2::value_type>
void merge_sort_no_copy_impl(Iter1 dstBegin, Iter1 dstEnd,
							 Iter2 srcBegin, Iter2 srcEnd)
{
	auto dis = std::distance(dstBegin, dstEnd);
	if (dis <= M) {
		insertion_sort(dstBegin, dstEnd);
		return;
	}

	auto dstMid = std::next(dstBegin, dis / 2);
	auto srcMid = std::next(srcBegin, dis / 2);
	merge_sort_no_copy_impl(srcBegin, srcMid, dstBegin, dstMid);
	merge_sort_no_copy_impl(srcMid, srcEnd, dstMid, dstEnd);
	merge_no_copy(srcBegin, srcMid, srcMid, srcEnd, dstBegin);
}



template <comparable_iter_value Iter>
void merge_sort_no_copy(Iter begin, Iter end)
{
	using value_type = std::decay_t<decltype(*begin)>;
	auto dis = std::distance(begin, end);
	std::vector<value_type> buf;
	buf.reserve(dis);
	std::copy(begin, end, std::back_inserter(buf));

	merge_sort_no_copy_impl(begin, end, buf.begin(), buf.end());
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


template <
	is_cmp_array Array1,
	is_cmp_array Array2,
	is_cmp_array Array3>
void basic_merge(Array1& dest, int l,
				 Array2& src1, int l1, int r1,
				 Array3& src2, int l2, int r2)
{
	int r = l + r1 - l1 + r2 - l2 + 1; 

	for (; l <= r; ++l) {
		if (l1 > r1) {
			dest[l] = src2[l2++];
			continue;
		}
		if (l2 > r2) {
			dest[l] = src1[l1++];
			continue;
		}

		dest[l] = (src1[l1] < src2[l2] ? src1[l1++] : src2[l2++]);
	}
}


template <
	is_cmp_array Array,
	is_cmp_array Buffer>
void merge_sort_no_copy_impl(Array& arr, Buffer& buf, int l, int r)
{
	if (r - l + 1 <= M) {
		insertion_sort_advance(arr, l, r);
		return;
	}

	int m = (r + l) / 2;
	merge_sort_no_copy_impl(buf, arr, l, m);
	merge_sort_no_copy_impl(buf, arr, m + 1, r);
	basic_merge(arr, l,  buf, l, m,  buf, m + 1, r);
}


template <is_cmp_array Array>
void merge_sort_no_copy(Array& arr, int l, int r)
{
	using Elem = std::decay_t<decltype(arr[l])>;
	Elem* buf = new Elem[r - l + 1];

	for (int i = l; i <= r; ++i) {
		buf[i] = arr[i];
	}

	merge_sort_no_copy_impl(arr, buf, l, r);
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
	std::cout << function_execution_time(merge_sort_no_copy<decltype(vec.begin())>, vec.begin(), vec.end()) << " ms" << std::endl;
#else
	std::cout << function_execution_time(merge_sort_no_copy<decltype(vec)>, vec, 0, SIZE - 1) << " ms" << std::endl;
#endif


	std::cout << std::ranges::is_sorted(vec) << std::endl;
	// print_collection(vec);


	return 0;
}
