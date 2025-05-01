#include "collections_helper.h"
#include <iostream>
#include <chrono>



// #define WITH_ITERATORS



#ifdef WITH_ITERATORS

template <comparable_iter_value Iter>
void shell_sort(Iter begin, Iter end)
{
	int diff = static_cast<int>(std::distance(begin, end)) - 1; // => (right array index) - (left array index)
	int h = 1;
	while (h < diff / 9) {
		h *= 3;
		++h;
	}


	using ValType = std::decay_t<decltype(*begin)>;
	Iter curr, tmp;

	for (; h > 0; h /= 3) {
		for (auto it = std::next(begin, h); it != end; std::advance(it, 1)) {
			ValType currentCheckVal = std::move(*it);
			curr = it;
			while (	static_cast<int>(std::distance(begin, curr)) >= h &&
					*(tmp = std::prev(curr, h)) < currentCheckVal) {
				*curr = std::move(*tmp);
				curr = std::move(tmp);
			}
			*it = std::move(*curr);
		}
	}
}

#else

template <is_cmp_array Array>
void shell_sort(Array& arr, int l, int r)
{
	int h = 1;
	while (h < (r - l) / 9) {
		h = h * 3 + 1;
	}

	using Elem = std::decay_t<decltype(arr[l])>;
	int j = 0;
	for (; h > 0; h /= 3) {
		for (int i = l + h; i <= r; ++i) {
			Elem buffer = std::move(arr[i]);
			j = i;
			while (j >= l + h && buffer < arr[j - h]) {
				arr[j] = std::move(arr[j - h]);
				j -= h;
			}
			arr[j] = std::move(buffer);
		}
	}
}

#endif




const int SIZE = 200000;



int main(int, char**)
{
	std::vector<int> vec;
	vec.reserve(SIZE);
	random_init(std::back_inserter(vec), SIZE);

#ifdef WITH_ITERATORS
	std::cout << function_execution_time(shell_sort<decltype(vec.begin())>, vec.begin(), vec.end()) << " ms" << std::endl;
#else
	std::cout << function_execution_time(shell_sort<decltype(vec)>, vec, 0, SIZE - 1) << " ms" << std::endl;
#endif

	return 0;
}