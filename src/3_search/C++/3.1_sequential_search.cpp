#include <compare>
#include <iterator>
#include <iostream>
#include <vector>
#include <list>
#include <concepts>



template <std::input_or_output_iterator Iter, std::three_way_comparable Ty>
Iter sequential_search(const Iter begin, const Iter end, Ty searchVal)
{
	for (auto it = begin; it != end; ++it) {
		if (*it == searchVal) {
			return it;
		}
	}

	return end;
}




int main(int, char**)
{
// Test 1
	std::vector<int> intVec {7, 21, 66, 13, 8, 1, 36, 72};
	int searchInt = 13;

	auto intVecIt = sequential_search(intVec.begin(), intVec.end(), searchInt);
	std::cout << (intVecIt != intVec.end() ? std::distance(intVec.begin(), intVecIt) : -1) << std::endl;


// Test 2
	std::list<std::string> strList {"abc", "def", "ghi", "jkl", "mno", "pqr"};
	std::string searchStr = "jkl";

	auto strListIt = sequential_search(strList.begin(), strList.end(), searchStr);
	std::cout << (strListIt != strList.end() ? std::distance(strList.begin(), strListIt) : -1) << std::endl;


	return 0;
}
