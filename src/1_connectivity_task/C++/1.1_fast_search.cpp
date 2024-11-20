// #include <iostream>
// #include <iomanip>
// #include <cmath>


// constexpr unsigned int SIZE = 10;


// void printArray(unsigned int* arr)
// {
// 	unsigned int align = static_cast<unsigned int>(std::floor(std::log10(static_cast<double>(SIZE - 1))) + 1);

// 	for (int i = 0; i < SIZE - 1; ++i) {
// 		std::cout << std::setw(align) << arr[i] << " ";
// 	}
// 	std::cout << std::setw(align) << arr[SIZE - 1] << std::endl;
// }


// int main(int argc, char** argv)
// {
// 	unsigned int p, q, tmp, id[SIZE];

// 	for (unsigned int i = 0; i < SIZE; ++i) {
// 		id[i] = i;
// 	}

// 	while (std::cin >> p >> q) {
// 		std::cout << p << " - " << q << "\t";
// 		tmp = id[p];
// 		if (id[q] == tmp) {
// 			printArray(id);
// 			continue;
// 		}

// 		for (unsigned int i = 0; i < SIZE; ++i) {
// 			if (id[i] == tmp) {
// 				id[i] = id[q];
// 			}
// 		}

// 		printArray(id);
// 	}

// 	return 0;
// }



#include <iostream>

// Количество уникальных объектов (чисел)
const int N = 100;

int main(int, char**)
{
	// Объявление переменных
	int i, t, p, q, array[N];

	// Инициализация массива с начальными значениями от 0 до N-1
	for (i = 0; i < N; ++i) array[i] = i;

	// Основной цикл ввода данных (пар чисел) до достижения EOF (конца файла)
	while (std::cin >> p >> q) {

		// Запоминаем значение p-й ячейки
		t = array[p];

		// Проверка, связаны ли объекты (опреация ПОИСК)
		if (t == array[q]) continue;

		// Опреация ОБЪЕДИНЕНИЕ
		for (i = 0; i < N; ++i) {
			if (array[i] == t) {
				array[i] = array[q];
			}
		}

		// Вывод пары чисел
		std::cout << " " << p << " " << q << std::endl;
	}
}
