#include "collections_helper.h"
#include "heap_functions.h"
#include <iostream>



template <is_cmp_array Array>
void heap_sort(Array arr, int size)
{
	for (int i = size / 2; i > 0; --i) {
		fixDown(arr, i, size);
	}

	while (size > 1) {
		std::swap(arr[1], arr[size]);
		fixDown(arr, 1, --size);
	}
}



static const int SIZE = 200000;



int main(int, char**)
{
	using Item = int;

	// Инициализация массива размера SIZE
	Item* arr = new Item[SIZE + 1];
	for (int i = 1; i <= SIZE; ++i) {
		arr[i] = get_random_int();
	}

	// print_collection(arr + 1, arr + SIZE + 1);

	std::cout << function_execution_time(heap_sort<decltype(arr)>, arr, SIZE) << " ms\n";

	// print_collection(arr + 1, arr + SIZE + 1);


	return 0;
}