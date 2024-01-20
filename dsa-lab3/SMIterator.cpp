#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <utility>
#include <exception>
using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
    //TODO - Implementation
    //if(!map.isEmpty())
        current_index=map.head;
}

///best=avf=worst=θ(1)
void SMIterator::first(){
    //TODO - Implementation
    if(!map.isEmpty())
    {
        //throw exception();
        current_index=map.head;
    }

}

///best=avg=worst=θ(1)
void SMIterator::next(){
    //TODO - Implementation

    if(!valid())
    {
        throw exception();
    }
    current_index=map.array[current_index].next;
}

///best=avg=worst=θ(1)
bool SMIterator::valid() const{
    //TODO - Implementation
    if(current_index!=-1 and !map.isEmpty())
    {
        return true;
    }
    return false;
}

///best=avg=worst=θ(1)
TElem SMIterator::getCurrent() const{
    //TODO - Implementation
    if(!valid())
    {
        throw exception();
    }
    return map.array[current_index].elem;
    //  return NULL_TPAIR;
}