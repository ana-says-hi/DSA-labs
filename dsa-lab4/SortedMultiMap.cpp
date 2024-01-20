#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>

using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
    //TODO - Implementation
    capacity = 1;
    length = 0;
    array = new TElem[capacity];
    relation = r;
    for (int k = 0; k < capacity; k++)
        array[k] = NULL_TELEM;
}

///best=worst=avg=overall=θ(1)
int SortedMultiMap::hash(TKey elem, int i, int cap) const {
    int c1, c2;
    //c1=0; c2=0;
    c1 = 1; //1, 3, 5       //cap 3, c1=1, c2=3
    c2 = 5;
    return ((elem % cap) + c1 * i + c2 * i * i) % cap;
}

///best=θ(1)
///avg=1/(1−𝛼) (𝛼=n/m)
///worst=O(n)
///overall O(n)
void SortedMultiMap::add(TKey c, TValue v) {
    //TODO - Implementation
    length++;
    int i = 0;
    if(length==capacity)
        resize_up();
    int pos = hash(c, i, capacity);
    while (array[pos] != NULL_TELEM and i < capacity and array[pos] != DELETED) {
        i++;
        pos = hash(c, i, capacity);
    }
    if (i == capacity) {
        resize_up();

        pos = hash(c, i, capacity);

    }
    array[pos] = make_pair(c, v);
}

///best=worst=avg=overall=θ(n)
///
/// worst=1/(1−𝛼) (𝛼=n/m)
/// avg=1/𝛼*ln(1/(1−𝛼))
/// best=θ(1)
vector<TValue> SortedMultiMap::search(TKey c) const {
    vector<TValue> values;
    //values.clear();
//    int i = 0;
//    int map_elem = hash(c, i, capacity);
//    while (i < capacity and array[map_elem] != NULL_TELEM) {//
//        if (array[map_elem].first == c and array[map_elem] != DELETED) {
//            values.push_back(array[map_elem].second);
//            clog << array[map_elem].first << '-' << array[map_elem].second << '\n';
//        }
//        i++;
//        map_elem = hash(c, i, capacity);
//    }

    for (int i = 0; i < capacity; i++) {
        if (array[i] != DELETED and array[i] != NULL_TELEM)
            if (array[i].first == c)
                values.push_back(array[i].second);
    }

    //if(values.size()==0)    return NULL_TVALUE;

    return values;
    //return vector<TValue>();
}

/// worst=1/(1−𝛼) (𝛼=n/m)
/// avg=1/𝛼*ln(1/(1−𝛼))
/// best=θ(1)
///overall=O(n)
bool SortedMultiMap::remove(TKey c, TValue v) {
    //TODO - Implementation
    int i = 0;
    int pos = hash(c, i, capacity);
    while (i < capacity and array[pos] != NULL_TELEM) {  //
        if (array[pos].second == v and array[pos].first == c) {   //array[pos]==make_pair(c,v)
            array[pos] = DELETED;
            length--;
            resize_down();
            return true;
        }
        i++;
        pos = hash(c, i, capacity);
    }
    //TODO parcurs array, daca e egal elem curent cu c,v -> remove
//    for (int i = 0; i < capacity; i++)
//        if (array[i].first == c and array[i].second == v) {
//            array[i] = DELETED;
//            length--;
//            resize_down();
//            return true;
//        }

    return false;
}


int SortedMultiMap::size() const {
    return length;
}

bool SortedMultiMap::isEmpty() const {
    if (length == 0) return true;
    return false;
}

SMMIterator SortedMultiMap::iterator() const {
    return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
    delete[] array;
}

///best=worst=avg=overall=θ(n)
void SortedMultiMap::resize_up() {
    //if (length < capacity) return;
    int new_capacity = 2 * capacity;
    TElem *new_array = rehash(new_capacity);

    delete[] array;
    array = new_array;

    capacity = new_capacity;
}

///best=worst=avg=overall=θ(n)
void SortedMultiMap::resize_down() {
    if (length != capacity / 4) {
        return;
    }

    int new_capacity = capacity / 2;

    TElem *new_array = rehash(new_capacity);

    delete[] array;
    array = new_array;

    capacity = new_capacity;
}

///best=worst=avg=overall=θ(n)
TElem *SortedMultiMap::rehash(int new_cap) {
    TElem *new_arr = new TElem[new_cap];
    for (int k = 0; k < new_cap; k++)
        new_arr[k] = NULL_TELEM;
    int new_pos;
    for (int k = 0; k < capacity; k++)
        if (array[k] != NULL_TELEM or array[k] != DELETED) {
            int i = 0;
            while (i < new_cap) {
                new_pos = hash(array[k].first, i, new_cap);
                if (new_arr[new_pos] != NULL_TELEM)
                    i++;
                else {
                    new_arr[new_pos] = array[k];
                    break;
                }
            }
        }
    return new_arr;
    //return (elem%new_cap)+c1*i+c2*i*i;
}


/*!
 * @pre: this, other SMM
 * @post: new SMM (=this+other)
 */
SortedMultiMap SortedMultiMap::concatenare(SortedMultiMap &other) const {
    ///copiaza toate elem din this si alt smm
    ///complexitate θ(n^2)  (add<-O(n))
    SortedMultiMap newMap(this->relation);
//    for(int i=0;i<this->capacity;i++)
//        if(array[i]!=DELETED and array[i]!=NULL_TELEM)
//            newMap.add(array[i].first,array[i].second);
//    for(int j=0;j<other.capacity;j++)
//        if(array[j]!=DELETED and array[j]!=NULL_TELEM)
//            newMap.add(array[j].first,array[j].second);
//    return newMap;

    /*!pseudocod
     * for elem in this
     *     newMap.add(elem)     [elem={cheie, valoare}]
     *          [
     *          - cauta poz pe care trebuie adaugat
     *              while(poz ocupata/ deleted)
     *                  i++
     *                  hash(i, cheie)  //recalcularea poz
     *              daca i=capcitate
     *                  resize_up
     *                  hash(i,cheie)
     *          - adauga elementul
     *              newMap[poz]=elem
     *          ]
     * for elem in other
     *      newMap.add(elem)
     * return newMap
     */



///best=θ(1)
///avg=1/(1−𝛼) (𝛼=n/m)
///worst=O(n)
///overall O(n)
    newMap.length=this->length+other.length;
    newMap.capacity=this->capacity+other.capacity;
    TKey c; TValue v;
    for(int k=0;k<this->capacity;k++) {
        if(this->array[k]!=DELETED and this->array[k]!=NULL_TELEM) {
            c = this->array[k].first;
            v = this->array[k].second;
            int i = 0;
            int pos = hash(c, i, newMap.capacity);
            while (this->array[pos] != NULL_TELEM and i < newMap.capacity) {
                i++;
                pos = hash(c, i, newMap.capacity);
            }
            if (i == newMap.capacity) {
                newMap.resize_up();
                pos = hash(c, i, newMap.capacity);
            }
            newMap.array[pos] = make_pair(c, v);
        }
    }
    for(int k=0;k<other.capacity;k++) {
        if(other.array[k]!=DELETED and other.array[k]!=NULL_TELEM) {
            c = other.array[k].first;
            v = other.array[k].second;
            int i = 0;
            int pos = hash(c, i, newMap.capacity);
            while (other.array[pos] != NULL_TELEM and i < newMap.capacity) {
                i++;
                pos = hash(c, i, newMap.capacity);
            }
            if (i == newMap.capacity) {
                newMap.resize_up();
                pos = hash(c, i, newMap.capacity);
            }
            newMap.array[pos] = make_pair(c, v);
        }
    }
    newMap.resize_down();
    return newMap;
}