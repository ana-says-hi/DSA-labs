#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <stdexcept>

using namespace std;

///worst=best=avg=θ(1)
SortedBagIterator::SortedBagIterator( SortedBag& b) : bag(b) {
	//TODO - Implementation
    if(!bag.isEmpty())
    {
        index = 0;
        nod_curent = bag.head;
    }
}

///worst=best=avg=θ(1)
TComp SortedBagIterator::getCurrent() {
	//TODO - Implementation
    if(valid() and !bag.isEmpty())
        return nod_curent->info;
    throw std::out_of_range("index invalid");
}

///worst=best=avg=θ(1)
bool SortedBagIterator::valid() {
	//TODO - Implementation
    if(index<bag.size() and index>=0)
        return true;
	return false;
}

///worst=best=avg=θ(1)
void SortedBagIterator::next() {
	//TODO - Implementation
    if(valid() and !bag.isEmpty())
    {
        nod_curent = nod_curent->next;
        index++;
        return;
    }
    throw std::out_of_range("index invalid");
}

///worst=best=avg=θ(1)
void SortedBagIterator::first() {
	//TODO - Implementation
    if(!bag.isEmpty())
    {
        index = 0;
        nod_curent = bag.head;
    }
}

///best -> bag gol, are un singur element sau index invalid θ(1)
///avg=worst=O(n)
SortedBag SortedBagIterator::removeCurrent() {
    if(bag.isEmpty() or !valid())   throw invalid_argument("EMPTY BAG?");

    if(index==0 and bag.length==1) {
        //if(bag.length==1) {///nodul e head, singurul element
        SortedBag new_bag(bag.relation);
        return new_bag;
    }

    SortedBag new_bag(bag.relation);
    nod* crt=bag.head;
    for(int i=0;i<bag.size();i++)
    {
        if(crt!=nod_curent and crt->next!=nod_curent) {
            new_bag.add(crt->info);
            crt = crt->next;
        }
    }
    return new_bag;
}

///complexitatile de la bag.remove + daca bag e gol -> θ(1)
///best cases = bag gol, bag are un singur element, elem e head sau tail : θ(1)
///worst=avg=O(n) [search+while]

///pre: bag
///post: bag' [bag.len--; 1 element a fost inlaturat]

void SortedBagIterator::removeCrt() {
    if(bag.size()>1){
        nod_curent = nod_curent->next;
        bag.remove(nod_curent->prev->info);
        return;
    }
    if(bag.size()==1) { bag.remove(nod_curent->info); return;}
    throw invalid_argument("BAG IS EMPTY!");
}