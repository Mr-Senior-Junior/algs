#include <iostream>




void printBinNumberRecursion(size_t power, std::string str = std::string{})
{
// (2^power)-1 iterations

	if (!power && !str.empty()) {
		std::cout << str << "\n";
		return;
	}

	printBinNumberRecursion(power - 1, str + "0");
	printBinNumberRecursion(power - 1, str + "1");
}





int main(int, char**)
{
	printBinNumberRecursion(6);

	return 0;
}

