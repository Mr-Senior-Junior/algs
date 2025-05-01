#include "collections_helper.h"
#include <iostream>
#include <vector>



static const int M = 9;


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




static const int SIZE = 200000;



int main(int, char**)
{
	std::vector<int> vec;
	vec.reserve(SIZE);

	random_init(std::back_inserter(vec), SIZE);


	//print_collection(vec);

	std::cout << function_execution_time(merge_sort_no_copy<decltype(vec.begin())>, vec.begin(), vec.end()) << " ms" << std::endl;

	//print_collection(vec);


	return 0;
}
