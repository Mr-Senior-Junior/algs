#include <iostream>
#include <algorithm>
#include <vector>



namespace fibonacci {

int BAD_fibonacci(int num)
{
	if (num < 2) {
		return std::clamp(num, 0, 1);
	}

	return BAD_fibonacci(num - 1) + BAD_fibonacci(num - 2);
}


int GOOD_fibonacci(int num)
{
	if (num < 3) {
		return std::clamp(num, 0, 1);
	}

	int prev = 1, current = 2;
	while (num-- > 3) {
		current += prev;
		prev = current - prev;
	}

	return current;
}

// top-down dynamic programming (memoization)
struct MEMO_fibonacci {
	int fib[50];

	MEMO_fibonacci() {
		for (int i = 0; i < 50; ++i) {
			fib[i] = 0;
		}
	}

	int evaluate(int num) {
		if (fib[num]) {
			return fib[num];
		}

		if (num < 3) {
			return std::clamp(num, 0, 1);
		}

		return fib[num] = evaluate(num - 1) + evaluate(num - 2);
	}
};

}



namespace bag {


const int itemsCount = 5;

struct Item {
	char title;
	int size;
	int price;
};

Item items[itemsCount] = {
	Item{'A', 3, 4},
	Item{'B', 4, 5},
	Item{'C', 7, 10},
	Item{'D', 8, 11},
	Item{'E', 9, 13}
};


int BAD_knap(int size)
{
	int max = 0, space = 0;
	for (auto &item : items) {
		space = size - item.size;
		if (space >= 0) {
			max = std::max(max, BAD_knap(space) + item.price);
		}
	}
	return max;
}


struct GOOD_knap {
	int knownMaxPriceForSize[1000];

	GOOD_knap() {
		for (int i = 0; i < 1000; ++i) {
			knownMaxPriceForSize[i] = 0;
		}
	}

	int evaluate(int size) {
		if (knownMaxPriceForSize[size]) {
			return knownMaxPriceForSize[size];
		}

		int max = 0, space = 0;
		for (auto& item : items) {
			space = size - item.size;
			if (space >= 0) {
				max = std::max(max, evaluate(space) + item.price);
			}
		}
		return knownMaxPriceForSize[size] = max;
	}
};

int GOOD_knap2(int size)
{
	int rows = itemsCount; // items
	int cols = size + 1; // sizes

	std::vector<std::vector<int>> dp(rows, std::vector(cols, 0));

	int upVal = 0, currentVal = 0;
	for (int row = 0; row < rows; ++row) {
		Item& item = items[row];
		for (int col = 0; col < cols; ++col) {
			upVal = dp[std::clamp(row - 1, 0, 4)][col];
			if (col < item.size) {
				dp[row][col] = upVal;
				continue;
			}

			currentVal = dp[row][col - item.size] + item.price;
			dp[row][col] = std::max(upVal, currentVal);
		}
	}

	return dp[rows - 1][cols - 1];
}



}



int main(int, char**)
{
// fibonacci tests
#if 0
	std::cout << fibonacci::BAD_fibonacci(40) << std::endl;
	std::cout << fibonacci::GOOD_fibonacci(40) << std::endl;
	std::cout << fibonacci::MEMO_fibonacci().evaluate(40) << std::endl;
#endif


// bag tests
#if 1
	std::cout << bag::GOOD_knap().evaluate(781) << std::endl;
	std::cout << bag::GOOD_knap2(5000) << std::endl;
	std::cout << bag::BAD_knap(63) << std::endl;
#endif

	return 0;
}
