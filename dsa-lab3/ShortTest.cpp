#include <assert.h>

#include "SortedMap.h"
#include "SMIterator.h"
#include "ShortTest.h"
#include <exception>
#include <iostream>

using namespace std;

bool relatie1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedMap sm1(relatie1);
	SortedMap sm2(relatie1);
	assert(sm1.size() == 0);
	assert(sm1.isEmpty());
    sm1.add(1, 2);

    sm2.add(1,3);
    assert(!sm1.equal_smap(sm2));

    assert(sm1.size() == 1);
    assert(!sm1.isEmpty());
    assert(sm1.search(1) != NULL_TVALUE);
    TValue v =sm1.add(1, 3);
    assert(v == 2);

    assert(sm1.equal_smap(sm2));

    assert(sm1.search(1) == 3);
    SMIterator it = sm1.iterator();
    it.first();
    while (it.valid()){
    	TElem e = it.getCurrent();
    	assert(e.second != NULL_TVALUE);
    	it.next();
    }
    assert(sm1.remove(1) == 3);
    assert(sm1.isEmpty());
    cout<<"Short Test passed!\n";
}

