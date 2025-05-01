#include <iostream>




void print_bin_number_recursion(size_t power, std::string str = std::string{})
{
// (2^power)-1 iterations

	if (!power && !str.empty()) {
		std::cout << str << "\n";
		return;
	}

	print_bin_number_recursion(power - 1, str + "0");
	print_bin_number_recursion(power - 1, str + "1");
}





int main(int, char**)
{
	print_bin_number_recursion(6);

	return 0;
}

