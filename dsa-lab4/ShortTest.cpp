#include <assert.h>

#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <exception>
#include <vector>
#include <iostream>

using namespace std;

bool relation1(TKey cheie1, TKey cheie2) {
    if (cheie1 <= cheie2) {
        return true;
    } else {
        return false;
    }
}

void testAll() {
    SortedMultiMap smm1 = SortedMultiMap(relation1);
    SortedMultiMap smm2 = SortedMultiMap(relation1);
    assert(smm1.size() == 0);
    assert(smm1.isEmpty());
    smm1.add(1, 2);
    smm1.add(1, 3);
    smm2.add(2, 2);
    smm2.add(2, 3);
    assert(smm1.size() == 2);
    assert(!smm1.isEmpty());
    vector<TValue> v = smm1.search(1);
    //std::cout<<v.size();
    assert(v.size() == 2);
    v = smm1.search(3);
    assert(v.size() == 0);
    SMMIterator it = smm1.iterator();
    it.first();
    while (it.valid()) {
        TElem e = it.getCurrent();
        it.next();
    }


    SortedMultiMap smm3 = smm1.concatenare(smm2);
    assert(!smm3.isEmpty());
    assert(smm3.size()==4);
    assert(smm3.remove(1, 3) == true);
    assert(smm3.remove(2, 1) == false);

    assert(smm1.remove(1, 2) == true);
    assert(smm1.remove(1, 3) == true);
    assert(smm1.remove(2, 1) == false);
    assert(smm1.isEmpty());
}

