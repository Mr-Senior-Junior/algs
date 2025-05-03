#include "collections_helper.h"
#include <iostream>
#include <vector>




// #define WITH_ITERATORS




#ifdef WITH_ITERATORS

template <
	comparable_iter_value Iter1,
	comparable_iter_value Iter2,
	out_iterator Iter3> requires 
							std::same_as<typename Iter1::value_type, typename Iter2::value_type> &&
							std::same_as<typename Iter1::value_type, typename Iter3::container_type::value_type>
void basic_merge(Iter1 begin1, Iter1 end1,
				 Iter2 begin2, Iter2 end2,
				 Iter3 inserter)
{
	while (begin1 != end1 && begin2 != end2) {
		inserter = *begin1 < *begin2 ? *begin1++ : *begin2++;
	}

	if (begin1 == end1) {
		while (begin2 != end2) {
			inserter = *begin2++;
		}
	}
	if (begin2 == end2) {
		while (begin1 != end1) {
			inserter = *begin1++;
		}
	}
}

#else

template <
	is_cmp_array Array1,
	is_cmp_array Array2,
	is_cmp_array Array3>
void basic_merge(Array1& dest, Array2& src1, int size1, Array3& src2, int size2)
{
	for (int i1 = 0, i2 = 0, k = 0; k < size1 + size2; ++k) {
		if (i1 == size1) {
			dest[k] = src2[i2++];
			continue;
		}
		if (i2 == size2) {
			dest[k] = src1[i1++];
			continue;
		}
		dest[k] = (src1[i1] < src2[i2] ? src1[i1++] : src2[i2++]);
	}
}

#endif



static const int SIZE1 = 20;
static const int SIZE2 = 10;



int main(int, char**)
{
	std::vector<int> vec1, vec2, result;
	vec1.reserve(SIZE1);
	vec2.reserve(SIZE2);
#ifdef WITH_ITERATORS
	result.reserve(SIZE1 + SIZE2);
#else
	result.resize(SIZE1 + SIZE2);
#endif

	random_init(std::back_inserter(vec1), SIZE1);
	random_init(std::back_inserter(vec2), SIZE2);

	std::ranges::sort(vec1);
	std::ranges::sort(vec2);

#ifdef WITH_ITERATORS
	basic_merge(vec1.begin(), vec1.end(),
				vec2.begin(), vec2.end(),
				std::back_inserter(result));
#else
	basic_merge(result, vec1, SIZE1, vec2, SIZE2);
#endif

	print_collection(result);


	return 0;
}




