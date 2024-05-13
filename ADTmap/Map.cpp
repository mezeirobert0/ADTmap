#include "Map.h"
#include "MapIterator.h"
#include <utility>
#include <queue>
#include <iostream>

// function for returning modulo of 2 positive numbers OR of a negative number and then a positive number
int mod(int x, int y) {
	int r = x % y;
	return r < 0 ? r + y : r;
}

// complexity: Theta(1)
Map::Map() {
	// capacity should be a power of 2
	capacity = 16;

	currentSize = 0;
	e = new TElem[capacity];

	// initializing elements array
	for (int i = 0; i < capacity; i++)
		e[i] = NULL_TELEM;
}

// complexity: Theta(capacity)
Map::~Map() {
	delete[] e;
	e = nullptr;
}

// complexity: Theta(1) amortized
TValue Map::add(TKey c, TValue v) {
	// consider the hashing function h(k, i) = (k % capacity + 0.5 * i + 0.5 * i * i) % capacity, 
	// where i = 0, 1 , ... m - 1

	// the key c is guaranteed to be in the map
	if (search(c) != NULL_TVALUE)
	{
		// getting the index of the <key, value> pair in the dynamic array of TElem elements
		int i;
		TKey hashedKey;

		for (int i = 0; i < capacity; i++)
		{
			hashedKey = (TKey)mod((mod(c, capacity) + 0.5 * i + 0.5 * i * i), capacity);

			if (e[hashedKey].first == c)
			{
				TValue previousValue = e[hashedKey].second;

				e[hashedKey].second = v;
				return previousValue;
			}
		}
	}

	if (currentSize == capacity)
		resize();

	// hash the key c for i = 0
	int i = 0;
	TKey hashedKey = (TKey)mod((mod(c, capacity) + 0.5 * i + 0.5 * i * i), capacity);

	while (e[hashedKey] != NULL_TELEM && i < capacity)
	{
		i++;
		hashedKey = (TKey)mod((mod(c, capacity) + 0.5 * i + 0.5 * i * i), capacity);
	}

	e[hashedKey].first = c;
	e[hashedKey].second = v;
	currentSize++;

	return NULL_TVALUE;
}

// complexity: Theta(1) amortized
TValue Map::search(TKey c) const {
	TKey hashedKey;

	for (int i = 0; i < capacity; i++)
	{
		hashedKey = (TKey)mod((mod(c, capacity) + 0.5 * i + 0.5 * i * i), capacity);

		if (e[hashedKey].first == c)
			return e[hashedKey].second;

		else if (e[hashedKey] == NULL_TELEM)
			return NULL_TVALUE;
	}

	// all array slots are occupied
	return NULL_TVALUE;
}

// complexity: Theta(capacity)
void Map::resize()
{
	std::queue<TElem> elements;

	// copying elements from e to elements stack
	for (int i = 0; i < capacity; i++)
		if (e[i] != NULL_TELEM)
			elements.push(e[i]);

	delete[] e;
	e = nullptr;

	capacity *= 2;
	e = new TElem[capacity];
	for (int i = 0; i < capacity; i++)
		e[i] = NULL_TELEM;

	// need to rehash elements from elements stack
	while (!elements.empty())
	{
		TElem currentElement = elements.front();
		elements.pop();

		add(currentElement.first, currentElement.second);
		currentSize--; // the add function will continue to increment the current size, but here we are just re-adding elements
	}
}

// complexity: Theta(1) amortized
TValue Map::remove(TKey c) {
	TKey hashedKey;

	for (int i = 0; i < capacity; i++)
	{
		hashedKey = (TKey)mod((mod(c, capacity) + 0.5 * i + 0.5 * i * i), capacity);

		if (e[hashedKey].first == c)
		{
			TValue valueBeforeRemoval = e[hashedKey].second;

			currentSize--;
			e[hashedKey] = NULL_TELEM;
			return valueBeforeRemoval;
		}
	}

	return NULL_TVALUE;
}

// complexity: Theta(1)
int Map::size() const {

	return currentSize;
}

// complexity: Theta(1)
bool Map::isEmpty() const {

	return currentSize == 0;
}

// complexity: Theta(1)
MapIterator Map::iterator() const {
	return MapIterator(*this);
}

// complexity: Theta(currentSize)
std::vector<TValue> Map::valueBag() const {
	std::vector<TValue> valArr;

	auto it = iterator();
	while (it.valid())
	{
		valArr.push_back(it.getCurrent().second);
		it.next();
	}

	return valArr;
}
