#include <iostream>

// Количество уникальных объектов (чисел)
const int N = 100;

int main(int, char**)
{
	// Объявление переменных
	unsigned int i, j, p, q, array[N], sizes[N];

	// Инициализация массивов
	for (i = 0; i < N; ++i) {
		array[i] = i;
		sizes[i] = 1;
	}

	// Основной цикл ввода данных (пар чисел) до достижения EOF (конца файла)
	while (std::cin >> p >> q) {

		// Проверка, связаны ли объекты (опреация ПОИСК)
		for (i = p; i != array[i]; i = array[i]);
		for (j = q; j != array[j]; j = array[j]);
		if (i == j) continue;


		// Опреация ОБЪЕДИНЕНИЕ (корень МЕНЬШЕГО дерева ссылаем на корень БОЛЬШЕГО дерева, затем увеличиваем размер БОЛЬШЕГО дерева)
		if (sizes[i] < sizes[j]) {
			array[i] = j;
			sizes[j] += sizes[i];
		} else {
			array[j] = i;
			sizes[i] += sizes[j];
		}


		// Вывод пары чисел
		std::cout << " " << p << " " << q << std::endl;
	}
}

