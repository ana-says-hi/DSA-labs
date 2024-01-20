#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

///best=worst=avg=overall=θ(logn)
SortedBagIterator::SortedBagIterator(const SortedBag &b) : bag(b) {
    nod_crt = bag.wurzel;
    if (!bag.isEmpty()) {
        while (nod_crt->left != nullptr)
            nod_crt = nod_crt->left;
        crt = 0;
    }
}

///best=worst=avg=overall=θ(1)
TComp SortedBagIterator::getCurrent() {
    if (!valid())
        throw exception();
    return nod_crt->info;
}

///best=worst=avg=overall=θ(1)
bool SortedBagIterator::valid() {
    if (!bag.isEmpty() and crt >= 0 and crt < bag.size())
        return true;
    return false;
}

///best=θ(1)
///best=avg=worst=θ(logn)
void SortedBagIterator::next() {
    if (valid()) {
        if (nod_crt->right != nullptr) {
            nod_crt = nod_crt->right;
            while (nod_crt->left != nullptr)
                nod_crt = nod_crt->left;
        } else if (nod_crt->vater!= nullptr and nod_crt == nod_crt->vater->left)
            nod_crt = nod_crt->vater;
        else {
            while (nod_crt->vater!= nullptr and bag.relation(nod_crt->info, nod_crt->vater->info))
                nod_crt = nod_crt->vater;
        }
        crt++;
        return;
    }
    throw exception();
}

void SortedBagIterator::first() {
    nod *nod_crt = bag.wurzel;
    while (nod_crt->left != nullptr)
        nod_crt = nod_crt->left;
    crt = 0;
}

