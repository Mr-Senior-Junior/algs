#pragma once
#include "collections_helper.h"
#include <concepts>




// Heap (пирамидальное дерево) - массив, в котором элементы храняться по уровням
// Для каждого узла справедливо, что родитель не меньше своих потомков
//          1
//      2       3
//    4   5   6   7
// цифры - это индексы массива. НУЛЕВОЙ ЭЛЕМЕНТ НЕ ИСПОЛЬЗУЕТСЯ!




// Функция fixUp восстанавливает "пирамидальность" в массиве снизу вверх
// Это актуально при вставке нового элемента или повышении приоритета
template <is_cmp_array Array>
void fixUp(Array arr, int k)
{
	while (k > 1 && arr[k / 2] < arr[k]) {
		std::swap(arr[k], arr[k / 2]);
		k /= 2;
	}
}



// Функция fixDown восстанавливает "пирамидальность" в массиве сверху вниз
// Это актуально при извлечении наибольшего элемента или понижении приоритета
template <is_cmp_array Array>
void fixDown(Array arr, int k, int N)
{
	while (2 * k <= N) {
		int j = 2 * k;
		if (j < N && arr[j] < arr[j + 1]) {
			++j;
		}
		if (!(arr[k] < arr[j])) {
			break;
		}
		std::swap(arr[k], arr[j]);
		k = j;
	}
}
