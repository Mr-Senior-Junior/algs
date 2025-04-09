#include <iostream>



void shift(int diskNum, int direction)
{
	// TODO
	std::cout << (direction < 0 ? "-" : "+") << diskNum << " ";
}

// function option for 3 pillars (shift left from 1 pillar = shift to 3 pillar)
void hanoi(int disksCount, int direction = 1)
{
	if (!disksCount) {
		return;
	}

	hanoi(disksCount - 1, -direction); // shift left (right) at 1 position "disksCount-1" top disks
	shift(disksCount, direction); // shift right (left) at 1 position disksCount-th disk
	hanoi(disksCount - 1, -direction); // shift left (right) at 1 position (or right (left) at 2 positions) "disksCount-1" disks
}



int main(int argc, char** argv)
{
	if (argc < 2) {
		std::cout << "Enter disks count\n";
		return 0;
	}

	int count = std::atoi(argv[1]);
	hanoi(count);

	return 0;
}
