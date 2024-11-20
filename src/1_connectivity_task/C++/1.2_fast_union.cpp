#include <iostream>

// Количество уникальных объектов (чисел)
const int N = 100;

int main(int, char**)
{
	// Объявление переменных
	unsigned int i, j, p, q, array[N];

	// Инициализация массива с начальными значениями от 0 до N-1
	for (i = 0; i < N; ++i) array[i] = i;

	// Основной цикл ввода данных (пар чисел) до достижения EOF (конца файла)
	while (std::cin >> p >> q) {

		// Проверка, связаны ли объекты (опреация ПОИСК)
		for (i = p; i != array[i]; i = array[i]);
		for (j = q; j != array[j]; j = array[j]);
		if (i == j) continue;

		// Опреация ОБЪЕДИНЕНИЕ
		array[i] = j;

		// Вывод пары чисел
		std::cout << " " << p << " " << q << std::endl;
	}
}

