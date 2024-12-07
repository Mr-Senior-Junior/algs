#include <compare>
#include <iterator>
#include <iostream>
#include <vector>
#include <list>
#include <concepts>


template <typename Ty, typename Iter>
concept comparable_iter_value = std::same_as<Ty, typename Iter::value_type> && std::three_way_comparable<Ty>;


template <std::input_or_output_iterator Iter, comparable_iter_value<Iter> Ty>
Iter binary_search2(Iter begin, Iter end, Ty searchVal)
{
	auto notFound = end;
	while (begin != end) {
		auto size = std::distance(begin, end);
		auto mid = std::next(begin, size / 2);
		if (*mid == searchVal) {
			return mid;
		} else if (*mid < searchVal) {
			begin = std::next(mid);
		} else {
			end = mid;
		}
	}

	return notFound;
}




int main(int, char**)
{
// Test 1
	std::vector<int> intVec {1, 7, 8, 13, 36, 44, 72, 89, 103, 231, 243, 287}; // Отсортированный массив
	int searchInt = 13;

	auto intVecIt = binary_search2(intVec.begin(), intVec.end(), searchInt);
	std::cout << (intVecIt != intVec.end() ? std::distance(intVec.begin(), intVecIt) : -1) << std::endl;


// Test 2
	std::list<std::string> strList {"abc", "def", "ghi", "jkl", "mno", "pqr"}; // Отсортированный список
	std::string searchStr = "jkl";

	auto strListIt = binary_search2(strList.begin(), strList.end(), searchStr);
	std::cout << (strListIt != strList.end() ? std::distance(strList.begin(), strListIt) : -1) << std::endl;


	return 0;
}
