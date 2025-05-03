#include <iostream>
#include <bitset>






int main(int, char**)
{
	using BS9 = std::bitset<9>;
    using BS9_COUNT = std::pair<BS9, size_t>;

	BS9_COUNT row;
	BS9_COUNT boxes[3];
	BS9_COUNT cols[9];

	std::cout << row.first << "  " << row.second << std::endl;
	for (int i = 0; i < 3; ++i) {
		std::cout << boxes[i].first << "  " << boxes[i].second << std::endl;
	}


	return 0;
}


// . 1 1 . 2 . 1 . 3
// cnt = 4
// 000000111

