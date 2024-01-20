#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	//TODO - Representation
    TElem *map_elem;
    int crt;

    void quick_sort(int start, int fin);
    int partition(int start, int fin);

public:
	void first();
	void next();
	bool valid()const;
   	TElem getCurrent() const;
};

