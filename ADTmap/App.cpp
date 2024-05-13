#include "ExtendedTest.h"
#include "ShortTest.h"

#include "Map.h"
#include "MapIterator.h"

#include <iostream>
#include <cassert>

int main() {
	testAll();
	testAllExtended();

	std::cout << "That's all!" << std::endl;
	system("pause");

	return 0;
}
