#pragma once
#include "Map.h"
class MapIterator
{
	friend class Map;

private:
	const Map& map;
	TKey currentIndex;
	MapIterator(const Map& m);

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};
