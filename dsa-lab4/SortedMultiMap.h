#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111)
#define DELETED pair<TKey, TValue>(NULL_TELEM.first-1, NULL_TELEM.second-1)
using namespace std;

class SMMIterator;

typedef bool(*Relation)(TKey, TKey);


class SortedMultiMap {
    friend class SMMIterator;

private:
    //TODO - Representation
    TElem *array;      ///element+ pozitia in hash??
    int capacity;
    int length;
    Relation relation;

    int hash(TKey elem, int i, int cap) const;   ///wo m = capacity

public:

    // constructor
    SortedMultiMap(Relation r);

    //adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

    //returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

    //removes a key value pair from the sorted multimap
    //returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multimap is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();

    void resize_up();

    TElem* rehash(int new_cap);

    void resize_down();

    SortedMultiMap concatenare(SortedMultiMap &other) const;
};

///concatenare a 2 sorted multimap