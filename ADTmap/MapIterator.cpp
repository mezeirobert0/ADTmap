#include "Map.h"
#include "MapIterator.h"
#include <stdexcept>
using namespace std;

// complexity: O(1) amortized
MapIterator::MapIterator(const Map& d) : map(d)
{
	currentIndex = 0;
	while (map.e[currentIndex] == NULL_TELEM && currentIndex < map.capacity)
		currentIndex++;
}

// complexity: O(1) amortized
void MapIterator::first() {
	currentIndex = 0;
	while (map.e[currentIndex] == NULL_TELEM && currentIndex < map.capacity)
		currentIndex++;
}

// complexity: O(1) amortized
void MapIterator::next() {
	if (!valid())
		throw std::out_of_range("Iterator is out of range!");
	
	currentIndex++;
	while (map.e[currentIndex] == NULL_TELEM && currentIndex < map.capacity)
		currentIndex++;
}

// complexity: Theta(1)
TElem MapIterator::getCurrent(){
	
	if (!valid())
		throw std::out_of_range("Iterator is out of range!");

	return map.e[currentIndex];
}

// complexity: Theta(1)
bool MapIterator::valid() const {
	return currentIndex < map.capacity;
}
