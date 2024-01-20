#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
    SortedBag& bag;
	SortedBagIterator(SortedBag& b);

	//TODO - Representation
    nod* nod_curent;
    int index;

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
    SortedBag removeCurrent();
    void removeCrt();
};

