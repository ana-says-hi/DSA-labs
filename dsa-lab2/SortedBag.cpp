#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
    //TODO - Implementation

    head = nullptr;
    tail = nullptr;

    relation = r;
    length = 0;
}

///best cases = bag gol, elem e head sau tail : θ(1)
///worst=avg=O(n)
void SortedBag::add(TComp e) {
    //TODO - Implementation
    ///daca e head
    ///daca e tail

    nod *new_nod = new nod{e, nullptr, nullptr};

    ///daca bag e gol
    if (isEmpty()) {
        head = new_nod;
        tail = new_nod;
        length++;
        return;

    } else {
        if (relation(e, head->info)) {
            ///e e noul head
            new_nod->next = head;
            head->prev = new_nod;
            head = new_nod;  ///?!?!
            length++;
            return;
        }

        if (!relation(e, tail->info)) {
            ///e e noul tail
            new_nod->prev = tail;
            tail->next = new_nod;
            tail = new_nod;
            length++;
            return;
        }

        nod *curent = head;
        ///gaseste unde trebuie pus
        while (!relation(e, curent->info) and curent != tail) {
            curent = curent->next;
        }
        ///il leaga de vecini
        curent->prev->next = new_nod;
        new_nod->next = curent;
        new_nod->prev = curent->prev;
        curent->prev = new_nod;
        length++;
        return;
    }
}

///best cases = bag are un singur element, elem e head sau tail : θ(1)
///worst=avg=O(n) [search+while]
bool SortedBag::remove(TComp e) {
    //TODO - Implementation
    ///daca exista in lista
    ///daca e head sau tail

    if (length == 1 and head->info == e) {
        length--;
//        delete head;
//        delete tail;
        head = tail = nullptr;
    }

    if (e == head->info) {
        length--;
        nod *old_head = head;
        head = head->next;
        head->prev = nullptr;
        delete old_head;
        return true;
    }

    if (e == tail->info) {
        length--;
        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
        return true;
    }

    if (!search(e)) return false;

    nod *crt = head;
    while (crt->info != e and crt != tail) {
        crt = crt->next;
    }
    crt->prev->next = crt->next;
    crt->next->prev = crt->prev;
    delete crt;
    length--;
    return true;
}

///best case = bag gol : θ(1)
///worst=avg=overall=O(n)
bool SortedBag::search(TComp elem) const {
    //TODO - Implementation

    if (length == 0) return false;

    //if (head->info == elem or tail->info == elem) return true;

    nod *crt = head;
    while (crt->info != elem and crt != tail) {
        crt = crt->next;
    }

    if (crt->info == elem)
        return true;

    return false;
}

///best case -> bag gol θ(1)
///worst=avg=overall=O(n)
int SortedBag::nrOccurrences(TComp elem) const {
    //TODO - Implementation
    ///serach pana la prima aparitie, apoi nr de cate ori mai apare

    if (!search(elem)) return 0;

    int ct = 0;
    nod *crt = head;
    for (int i = 0; i < length and crt != tail; i++) {
        if (crt->info == elem) ct++;
        crt = crt->next;
    }
    if (tail->info == elem) ct++;

//    int ct = 1;
//    nod *crt = head;
//    if (crt->info != elem and crt != tail)
//        while (crt->info != elem and crt != tail)
//            crt = crt->next;
//    if (crt->info == elem and crt->next != nullptr) {
//        crt = crt->next;
//        while (crt->info == elem and crt->next != nullptr) {
//            crt = crt->next;
//            ct++;
//        }
//    }
    return ct;
}

///worst=best=avg=θ(1)
int SortedBag::size() const {
    //TODO - Implementation
    return length;
}

///worst=best=avg=θ(1)
bool SortedBag::isEmpty() const {
    //TODO - Implementation
    if (length == 0) //sau head/tail e null
        return true;
    return false;
}


SortedBagIterator SortedBag::iterator()  {
    return SortedBagIterator(*this);
}

///worst=best=avg=θ(n)
///best case ->  bag e deja gol (n=0, nu se intampla nimic)
SortedBag::~SortedBag() {
    //TODO - Implementation
    ///sterse pe rand, nu doar head sau tail

    if (!isEmpty()) {
        nod *crt = head;
        while (crt != tail) {
            crt = crt->next;
            delete crt->prev;
        }
        delete crt;
        head = nullptr;
        tail = nullptr;
        length = 0;
    }
}

void SortedBag::setLength(int new_len) {
    length=new_len;
}