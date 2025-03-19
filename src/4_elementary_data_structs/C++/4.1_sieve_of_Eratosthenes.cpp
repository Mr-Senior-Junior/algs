#include <iostream>
#include <iomanip>
#include <bitset>

static const int N = 1000000;

int main(int, char**)
{
// Инициализируется массив
	std::bitset<N> a = 0;
	a = ~a;

// Зануляются все индексы, кратные простым числам, начиная с 2
	int ind = 0;
	for (int i = 2; i < N; ++i) {
		if (a[i]) {
			ind = i * i;
			while (ind < N) {
				a[ind] = false;
				ind += i;
			}
		}
	}

// Индексы ячеек массива, значения которых равны 1 и будут являться простыми числами
	int counter = 0;
	for (int i = 2; i < N; ++i) {
		if (a[i]) {
			++counter;
			std::cout << std::setw(5) << i;
			if (counter == 20) {
				counter = 0;
				std::cout << std::endl;
			}
		}
	}

	return 0;
}
