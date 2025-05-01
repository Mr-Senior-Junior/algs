#include "collections_helper.h"
#include <iostream>




// Сортировка методом распределяющего подсчета
// Когда есть N целочисленных элементов, значения которых лежат в диапазоне от 0 до M - 1 -> [0, M - 1]



void key_indexed_counting_sort(int* array, int l, int r, int M)
{
	++M; // 2 ячейки (первая и последняя) являются служебными
	int* ind = new int[M]{};
	int* arrayСopy = new int[r - l + 1];

	for (int i = l; i <= r; ++i) { ++ind[array[i] + 1]; } // инкремент следующего счетчита (логика такая, что например в ind[1] будет хранится количество элементов, равных 0)
	for (int i = 1; i < M; ++i) { ind[i] += ind[i - 1]; } // поэтапное суммирование (логика такая, что например в ind[2] будет хранится количество элементов, МЕНЬШЕ 2)
	for (int i = l; i <= r; ++i) { arrayСopy[ind[array[i]]++] = array[i]; } // значение ind[i] задает смещение элемента, т.е. мы вставляем его в нужное место
	for (int i = l; i <= r; ++i) { array[i] = arrayСopy[i]; }

	delete[] ind;
	delete[] arrayСopy;
}



static const int SIZE = 30;
static const int M = 10;


int main(int, char**)
{
	int* vec = new int[SIZE];
	for (int i = 0; i < SIZE; ++i) {
		vec[i] = get_random_int() % M;
	}

	print_collection(vec, vec + SIZE);

	key_indexed_counting_sort(vec, 0, SIZE - 1, M);

	print_collection(vec, vec + SIZE);

	return 0;
}






