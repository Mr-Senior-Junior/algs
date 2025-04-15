#include "collections_helper.h"
#include <iostream>
#include <chrono>




template <comparable_iter_value Iter>
void shellSort(Iter begin, Iter end)
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




const int SIZE = 5000;



int main(int, char**)
{
	std::vector<int> vec;
	vec.reserve(SIZE);
	randomInit(std::back_inserter(vec), SIZE);

	std::cout << function_execution_time(shellSort<decltype(vec.begin())>, vec.begin(), vec.end()) << " ms" << std::endl;

	return 0;
}