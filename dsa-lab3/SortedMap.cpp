#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

//TODO SCHIMBAT RESIZE DUPA FIRST EMPTY

///implicit constructor???
SortedMap::SortedMap(Relation r) {
    //TODO - Implementation
    relation = r;
    len = 0;
    capacity = 1;
    array = new Node[capacity];
    head = -1;
    tail = -1;
    firstEmpty = 0;
}

TValue SortedMap::add(TKey k, TValue v) {
    //TODO - Implementation
    //len++;  //TODO mutat len++
    //resize_up();    //TODO pus undeva
    if (head == -1) {
        ///daca lista goala
        len++;
        head = tail = firstEmpty;
        array[firstEmpty] = Node({{k, v}, -1, -1});
        firstEmpty++;
        resize_up();
        return NULL_TVALUE;
    }

    ///head
    if (!relation(array[head].elem.first, k)) {
        len++;
        array[firstEmpty] = Node({{k, v}, -1, head});
        //TODO cautat first empty
        while (firstEmpty < capacity and array[firstEmpty].elem != NULL_TPAIR) {
            firstEmpty++;
        }
        resize_up();
        return NULL_TVALUE;
    }
    if(array[head].elem.first==k) {
        TValue old_val=array[head].elem.second;
        array[head].elem.second = v;
        return old_val;
    }

    ///tail
    if (relation(array[tail].elem.first, k)) {
        if(k!=array[tail].elem.first) {
            len++;
            array[firstEmpty] = Node({{k, v}, tail, -1});

            while (firstEmpty < capacity and array[firstEmpty].elem != NULL_TPAIR) {
                firstEmpty++;
            }
            resize_up();

            return NULL_TVALUE;
        }
        TValue old_val=array[tail].elem.second;
        array[tail].elem.second=v;
        return old_val;
    }
    //TODO cautat noul is empty
    //resize_up
    //while is empty<capacity, cauta
    ///e deja in map
    if (search(k) != NULL_TVALUE) {
        Node curent_node = array[head];
        TValue old_val;
        while (relation(k, curent_node.elem.first) and curent_node.next != tail) {
            curent_node = array[curent_node.next];
        }
        ///! IFul ASTA la toate  while de parcurgere
        if (array[curent_node.prev].elem.first == k) curent_node = array[curent_node.prev];
        if (curent_node.elem.first == k) {
            old_val = curent_node.elem.second;
            curent_node.elem.second = v;
            return old_val;
        }
    }


    if(search(k)==NULL_TVALUE)
    {
        len++;
        Node curent_node = array[head];
        while (relation(k, curent_node.elem.first) and curent_node.next != tail) {
            curent_node = array[curent_node.next];
        }
        if (array[curent_node.prev].elem.first == k) curent_node = array[curent_node.prev];
        Node newNode={make_pair(k,v),curent_node.prev,array[curent_node.next].prev};
        array[firstEmpty]=newNode;
        array[curent_node.prev].next=firstEmpty;
        array[curent_node.next].prev=firstEmpty;

        while (firstEmpty < capacity and array[firstEmpty].elem != NULL_TPAIR) {
            firstEmpty++;
        }
        resize_up();
    }
    return NULL_TVALUE;
}

///best=avg=worst=θ(n)
TValue SortedMap::search(TKey k) const {
    if (isEmpty()) return NULL_TVALUE;

    if(k==array[head].elem.first)   return array[head].elem.second;

    Node curent_node = array[head];
    while (relation(k, curent_node.elem.first) and curent_node.next != tail) {
        curent_node = array[curent_node.next];
    }
    if (curent_node.elem.first == k) return curent_node.elem.second;
    if (array[curent_node.prev].elem.first == k) return array[curent_node.prev].elem.second;
    return NULL_TVALUE;
}

///best=avg=worst=θ(n)
TValue SortedMap::remove(TKey k) {
    //TODO - Implementation
    ///search, prev si next se schimba
    if (search(k) != NULL_TVALUE) {
        TValue ex_val;
        ///daca head/tail
        if (k == array[head].elem.first) {
            array[array[head].next].prev = -1;
            ex_val = array[head].elem.second;
            array[head].elem = NULL_TPAIR;
            if (firstEmpty > head) firstEmpty = head;
        }
        if (k == array[tail].elem.first) {
            array[array[tail].prev].next = -1;
            ex_val = array[tail].elem.second;
            array[tail].elem = NULL_TPAIR;
            if (firstEmpty > tail) firstEmpty = tail;
        }
        ///alte cazuri
        Node curent_node = array[head];
        while (relation(k, curent_node.elem.first)) {
            curent_node = array[curent_node.next];
        }
        //TODO ?pas inapoi?
        if (array[curent_node.prev].elem.first == k) return array[curent_node.prev].elem.second;
        if (curent_node.elem.first == k) {
            /// reclablare
            ///+stergere elem
            ///daca first empty este mai la dreapta decat pozitia eliberata
            if (firstEmpty > curent_node.next - 1) firstEmpty = curent_node.next;
            array[curent_node.prev].next = curent_node.next;
            array[curent_node.next].prev = curent_node.prev;
            ex_val = curent_node.elem.second;
            curent_node.elem = NULL_TPAIR;
        }
        len--;
        return ex_val;
    }
    return NULL_TVALUE;
}

///best=avg=worst=θ(1)
int SortedMap::size() const {
    return len;
}

///best=avg=worst=θ(1)
bool SortedMap::isEmpty() const {
    if (len == 0) return true;
    return false;
}

SMIterator SortedMap::iterator() const {
    return SMIterator(*this);
}

SortedMap::~SortedMap() {
    delete[] array;
//    delete[] array->elem;
//    delete[] array->prev;
//    delete[] array->next;
}

///best case- nu trebuie marit θ(1)
///avg=worst=O(n)
void SortedMap::resize_up() {
    if (firstEmpty == capacity or firstEmpty == capacity-1) {
        int old_cap=capacity;
        capacity = capacity * 2;

        Node *new_array = new Node[capacity];

        for (int i = 0; i < old_cap; i++) { ///copiaza elemetele
            new_array[i] = array[i];
        }
        for(int i=old_cap;i<capacity;i++){
            new_array[i]=Node({NULL_TPAIR, -1, -1});
        }

        delete[] array;

        array = new_array;
    }
}

/*!
 * @param other SortedMap
 * @return this==other [true/ false]
 */
 ///best case: lungimile nu sunt egale sau elementele de pe head si tail nu sunt egale: θ(1)
 ///avg=worst= O(n)
bool SortedMap::equal_smap(const SortedMap& other){
    if(this->len!=other.len) // or this->relation!=other.relation
        return false;

    Node curent_node1 = this->array[this->head];
    Node curent_node2 = other.array[other.head];

    if(curent_node1.elem!=curent_node2.elem or this->array[this->tail].elem!=other.array[other.tail].elem)
        return false;

    while(curent_node1.elem!=array[tail].elem){
        if(curent_node1.elem!=curent_node2.elem)    return false;
        curent_node1 = array[curent_node1.next];
        curent_node2 = array[curent_node2.next];
    }

    return true;
}