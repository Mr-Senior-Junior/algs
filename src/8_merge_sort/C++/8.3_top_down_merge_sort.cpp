#include "collections_helper.h"
#include <iostream>
#include <vector>



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





static const int SIZE = 200000;



int main(int, char**)
{
	std::vector<int> vec;
	vec.reserve(SIZE);
	random_init(std::back_inserter(vec), SIZE);
	

	// print_collection(vec);

	std::cout << function_execution_time(top_down_merge_sort<decltype(vec.begin())>, vec.begin(), vec.end()) << " ms" << std::endl;

	// print_collection(vec);


	return 0;
}

