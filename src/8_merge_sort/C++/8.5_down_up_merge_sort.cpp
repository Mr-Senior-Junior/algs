#include "collections_helper.h"
#include <iostream>
#include <vector>





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





static const int SIZE = 200000;



int main(int, char**)
{
	std::vector<int> vec;
	vec.reserve(SIZE);

	random_init(std::back_inserter(vec), SIZE);


	// print_collection(vec);

	std::cout << function_execution_time(down_up_merge_sort<decltype(vec.begin())>, vec.begin(), vec.end()) << " ms" << std::endl;

	// print_collection(vec);


	return 0;
}