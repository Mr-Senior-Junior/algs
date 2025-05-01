#include "collections_helper.h"
#include <iostream>
#include <ranges>






void in_place_rearrangement(char* vec, int* vecInd, int size)
{
	for (int i = 0; i < size; ++i) {
		char tmp = vec[i];
		int j = i;
		while (vecInd[j] != i) {
			vec[j] = vec[vecInd[j]];
			std::swap(vecInd[j], j);
		}
		vec[j] = tmp;
		vecInd[j] = j;
	}
}




static const int SIZE = 20;



int main(int, char**)
{
	char* vec = new char[SIZE] {'d','r','q','j','i','y','z','a','x','n','m','l','k','w','e','t','u','o','s','f'};
	int* vecInd = new int[SIZE];
	for (auto i : std::ranges::views::iota(0, SIZE)) {
		vecInd[i] = i;
	}

	std::sort(vecInd, vecInd + SIZE, [vec](int l, int r){ return vec[l] < vec[r]; });

	print_collection(vec, vec + SIZE);

	in_place_rearrangement(vec, vecInd, SIZE);

	print_collection(vec, vec + SIZE);


	return 0;
}

