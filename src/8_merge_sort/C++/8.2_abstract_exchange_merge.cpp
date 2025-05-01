#include "collections_helper.h"
#include <iostream>
#include <vector>






template <comparable_iter_value Iter>
void abstract_exchange_merge(Iter begin, Iter mid, Iter end)
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








static const int SIZE1 = 10;
static const int SIZE2 = 20;





int main(int, char**)
{
	std::vector<int> vec1, vec2, result;
	vec1.reserve(SIZE1);
	vec2.reserve(SIZE2);
	result.reserve(SIZE1 + SIZE2);

	random_init(std::back_inserter(vec1), SIZE1);
	random_init(std::back_inserter(vec2), SIZE2);


	std::ranges::sort(vec1);
	std::ranges::sort(vec2);


	result.insert(result.end(),
				  std::make_move_iterator(vec1.begin()),
				  std::make_move_iterator(vec1.end()));
	result.insert(result.end(),
				  std::make_move_iterator(vec2.begin()),
				  std::make_move_iterator(vec2.end()));

	abstract_exchange_merge(result.begin(),
							std::next(result.begin(), vec1.size()),
							result.end());

	print_collection(result);

	return 0;
}

