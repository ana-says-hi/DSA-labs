#include "ShortTest.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <assert.h>
#include <iostream>

bool relation1(TComp e1, TComp e2) {
	return e1 <= e2;
}

void anotherTest(){

    //std::cout<<it.getCurrent();

    SortedBag sb2(relation1);
    sb2.add(5);
    sb2.add(6);
    sb2.add(0);
    sb2.add(5);
    sb2.add(10);
    sb2.add(8);

    SortedBagIterator it2 = sb2.iterator();

//    it2.next();
//    it2.next();
//    //std::cout<<it.getCurrent();
//    assert(it2.getCurrent()==5);
//    SortedBag sb1=it2.removeCurrent();
//    SortedBagIterator it1 = sb1.iterator();
//    //std::cout<<sb1.size();
//    //std::cout<<it1.getCurrent();
//    it1.next();
//    //std::cout<<it1.getCurrent();
//    it1.next();
//    assert(it1.getCurrent()==6);


    SortedBag sb(relation1);
    sb.add(5);
    sb.add(6);
    sb.add(0);
    sb.add(5);
    sb.add(10);
    sb.add(8);
    SortedBagIterator it = sb.iterator();
    //std::cout<<it.getCurrent();
    it.next();
    assert(it.getCurrent()==5);
    it.removeCrt();
//    //std::cout<<it.getCurrent();
    assert(it.getCurrent()==5);
//    assert(it.valid());


}

void testAll() {
	SortedBag sb(relation1);
	sb.add(5);
	sb.add(6);
	sb.add(0);
	sb.add(5);
	sb.add(10);
	sb.add(8);

    //std::cout<<sb.size();
	assert(sb.size() == 6);
    //std::cout<<sb.nrOccurrences(5);
	assert(sb.nrOccurrences(5) == 2);

	assert(sb.remove(5) == true);
	assert(sb.size() == 5);
    //std::cout<<sb.size();
	assert(sb.search(6) == true);
    //std::cout<<sb.search(6);
	assert(sb.isEmpty() == false);

	SortedBagIterator it = sb.iterator();
	assert(it.valid() == true);
	while (it.valid()) {
		it.getCurrent();
		it.next();
	}
	assert(it.valid() == false);
	it.first();
	assert(it.valid() == true);

    std::cout<<"Short Test passed!"<<std::endl;

    anotherTest();

}

