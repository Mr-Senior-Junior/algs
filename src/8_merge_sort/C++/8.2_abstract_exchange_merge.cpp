#include "collections_helper.h"
#include <iostream>
#include <vector>


// #define WITH_ITERATORS




#ifdef WITH_ITERATORS

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

#else

template <is_cmp_array Array>
void abstract_exchange_merge(Array& arr, int l, int m, int r)
{
	using Elem = std::decay_t<decltype(arr[l])>;
	Elem* buf = new Elem[r - l + 1];


	for (int i = l; i <= m; ++i) {
		buf[i] = arr[i];
	}

	for (int i = 0; i < r - m; ++i) {
		buf[m + i + 1] = arr[r - i];
	}

	for (int k = l, left = l, right = r; k <= r; ++k) {
		arr[k] = (buf[left] < buf[right] ? buf[left++] : buf[right--]);
	}

	delete[] buf;
}

#endif







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

#ifdef WITH_ITERATORS
	abstract_exchange_merge(result.begin(), std::next(result.begin(), SIZE1), result.end());
#else
	abstract_exchange_merge(result, 0, SIZE1 - 1, SIZE1 + SIZE2 - 1);
#endif

	print_collection(result);

	return 0;
}

