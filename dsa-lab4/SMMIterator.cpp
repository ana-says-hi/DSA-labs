#include <exception>
#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap &d) : map(d) {
    //TODO - Implementation
    int j=0;
    map_elem=new TElem [map.length];
    for(int k=0;k<map.capacity;k++)
    {
        if(map.array[k]!=NULL_TELEM and map.array[k]!=DELETED)
        {
            map_elem[j]=map.array[k];
        }
    }
    quick_sort(0,map.size());
    crt = 0;
}

void SMMIterator::quick_sort(int start,int fin) {
    int part;
    if(start<fin)
    {
        part=partition(start, fin);
        quick_sort(start,part-1);
        quick_sort(part, fin);
    }
}

int SMMIterator::partition(int start, int fin) {
    TElem piv=map_elem[fin];
    TElem aux;
    int i=start-1; //poz a pivotului
    for(int j=start;j<fin;j++)
        if(map.relation(map_elem[j].first, piv.first)){
            i++;
            aux=map_elem[j];
            map_elem[j]=map_elem[i];
            map_elem[i]=aux;
        }
    aux=map_elem[i+1];
    map_elem[i+1]=map_elem[fin];
    map_elem[fin]=aux;
    return i+1;
}

///best=worst=avg=overall=θ(1)
void SMMIterator::first() {
    //TODO - Implementation
    crt = 0;
}

///best=worst=avg=overall=θ(1)
void SMMIterator::next() {
    //TODO - Implementation
    if (valid()) {
        crt++;
        return;
    }
    throw exception();
}

///best=worst=avg=overall=θ(1)
bool SMMIterator::valid() const {
    //TODO - Implementation
    if (crt < map.length and crt > -1) return true;
    return false;
}

///best=worst=avg=overall=θ(1)
TElem SMMIterator::getCurrent() const {
    //TODO - Implementation
    if(!valid())
        throw exception();
    return map_elem[crt];
}


