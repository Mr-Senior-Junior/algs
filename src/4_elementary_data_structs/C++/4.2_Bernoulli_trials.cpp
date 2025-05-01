#include <iostream>
#include <stdlib.h>


int heads()
{
	return rand() < RAND_MAX / 2;
}



// M экспериментов по N подбрасываний
static const int M = 6000;
static const int N = 40;



int main(int, char**)
{
// Инициализация seed для алгоритма случайного числа
	srand(static_cast<unsigned int>(time(NULL)));

	int i = 0, j = 0, count = 0;
	int results[N + 1];
	for (j = 0; j <= N; ++j) {
		results[j] = 0;
	}


// Основная часть программы - подсчет успешных бросков
	for (i = 0; i < M; ++i, ++results[count]) {
		for (count = 0, j = 0; j <= N; ++j) {
			if (heads()) {
				++count;
			}
		}
	}

// Вывод результата на экран
	for (j = 0; j <= N; ++j) {
		if (!results[j]) {
			std::cout << ".";
		}
		for (i = 0; i < results[j]; i += 10) {
			std::cout << "*";
		}
		std::cout << "\n";
	}

	return 0;
}
