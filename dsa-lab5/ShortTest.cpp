#include "ShortTest.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <assert.h>
#include <iostream>

bool relation1(TComp e1, TComp e2) {
	return e1 <= e2;
}

void testAll() {
	SortedBag sb1(relation1);
    SortedBag sb2(relation1);
    assert(sb1.is_equal(sb2));
	sb1.add(5);
    //sb2.add(5);
    //assert(sb1.is_equal(sb2));
	sb1.add(6);
	sb1.add(0);
	sb1.add(5);
	sb1.add(10);
	sb1.add(8);
    assert(!sb1.is_equal(sb2));
    sb2.add(0);
    sb2.add(6);
    sb2.add(10);
    sb2.add(5);
    sb2.add(5);
    sb2.add(8);
    assert(!sb1.is_equal(sb2));

	assert(sb1.size() == 6);
    //std::cout << sb1.nrOccurrences(5);
	assert(sb1.nrOccurrences(5) == 2);

    //std::cout<<"ShortTest passed!\n";

	assert(sb1.remove(5) == true);
	assert(sb1.size() == 5);

	assert(sb1.search(6) == true);
	assert(sb1.isEmpty() == false);

	SortedBagIterator it = sb1.iterator();
	assert(it.valid() == true);
	while (it.valid()) {
		it.getCurrent();
		it.next();
	}
	assert(it.valid() == false);
	it.first();
	assert(it.valid() == true);

    //std::cout<<"ShortTest passed!\n";
}

