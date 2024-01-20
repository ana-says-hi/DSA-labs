#include "SortedBag.h"
#include "SortedBagIterator.h"

///verif daca 2 containere sunt egale

SortedBag::SortedBag(Relation r) {
    wurzel = nullptr;
    relation = r;
    length = 0;
}

///best=avg=worst= θ(logn)
void SortedBag::add(TComp e) {
    length++;

    nod *new_nod = new nod{e, nullptr, nullptr, nullptr};

    if (wurzel == nullptr) {
        wurzel = new_nod;
        return;
    }

    nod *crt = wurzel;
    while (crt != nullptr) {
        if (relation(e, crt->info)) {   //adaugare
            if (crt->left == nullptr) {
                crt->left = new_nod;
                new_nod->vater = crt;
                break;
            }
            crt = crt->left;    //mers mai departe
        } else {
            if (crt->right == nullptr) {    //adaugare
                crt->right = new_nod;
                new_nod->vater = crt;
                break;
            }
            crt = crt->right;   //mers mai departe
        }
    }
    //crt = new_nod;
}

///avg=worst= 0(logn)  coboara cat posibil in dreapta (partii stangi)
///best=θ(1)    daca nu are stanga->un pas ca sa ajunga in dreapta
bool SortedBag::remove(TComp e) {
    if (!search(e) or isEmpty()) return false;

    length--;

    nod *crt = wurzel;
    while (crt != nullptr and crt->info != e) {
        if (relation(e, crt->info))
            crt = crt->left;
        else crt = crt->right;
    }

    if (crt->left != nullptr) {
        nod *swap = crt->left;
        while (swap->right != nullptr)
            swap = swap->right;
        if (swap->left != nullptr)
            swap->left->vater = swap->vater;
        swap->vater->right = swap->left;
        //else swap->vater->left = nullptr;
        swap->left = nullptr;
        //swap->vater = crt->vater;
        crt->info = swap->info;
        return true;
    }

    if (crt->right != nullptr) {
        //crt->vater->right=crt->right;
        crt->right->vater = crt->vater;
        if (crt == wurzel) {
            wurzel = crt->right;
        } else if (crt == crt->vater->left) {
            crt->vater->left = crt->right;
        } else {
            crt->vater->right = crt->right;
        }
        return true;
    }

    if (crt->vater != nullptr)
        if (crt == crt->vater->left) {
            crt->vater->left = nullptr;
        } else {
            crt->vater->right = nullptr;
        }
    crt = nullptr;
    return true;
}

///best=θ(1)    este wurzel
///best=avg=worst= θ(logn)
bool SortedBag::search(TComp elem) const {
    nod *crt = wurzel;
    while (crt != nullptr) {
        if (elem == crt->info) return true;
        if (relation(elem, crt->info))
            crt = crt->left;
        else crt = crt->right;
    }
    return false;
}

///best=avg=worst= θ(logn)
int SortedBag::nrOccurrences(TComp elem) const {
    int occ = 0;
    if (!search(elem)) return 0;
    nod *crt = wurzel;
    while (crt != nullptr) {
        if (elem == crt->info) occ++;
        if (relation(elem, crt->info))
            crt = crt->left;
        else crt = crt->right;
    }
    return occ;
}

///best=avg=worst= θ(1)
int SortedBag::size() const {
    return length;
}

///best=avg=worst= θ(1)
bool SortedBag::isEmpty() const {
    return length == 0;
}


SortedBagIterator SortedBag::iterator() const {
    return SortedBagIterator(*this);
}

///best=avg=worst=θ(n)
SortedBag::~SortedBag() {
    if (!isEmpty()) {
        destroy_branch(wurzel);
    }
}

void SortedBag::destroy_branch(nod *temp_wrz) {
    if (temp_wrz->left != nullptr) {
        nod *links = temp_wrz->left;
        destroy_branch(links);
    }

    if (temp_wrz->right != nullptr) {
        nod *rechts = temp_wrz->right;
        destroy_branch(rechts);
    }

    delete temp_wrz;
}

bool is_eq_aux(nod* nod1, nod* nod2){
    if(nod1==nullptr and nod2== nullptr)
        return true;

    if(nod1->info!=nod2->info)
        return false;

    return is_eq_aux(nod1->left,nod2->left) and is_eq_aux(nod1->right,nod2->right);
}

/*!
 * @param this & other
 * @return true (this=other), false (this!=other)
 */

///best=θ(1) lungimi inegale, radcini cu informatii diferite, relatii diferite
///avg=worst=O(n)
///overall O(n)
//bool SortedBag::is_equal(const SortedBag &other) {
//    if(this->length!=other.length)  return false;
//    if(this->relation!=other.relation)  return false;
//    if(this->wurzel->info!=other.wurzel->info)  return false;
//    return is_eq_aux(this->wurzel, other.wurzel);
//}

/*!
 * pseudocod
 *
 * this.len !=t other.len sau this.rel!=other.rel ->fals
 * parcurge this si other comparand informatia din noduri
 *      incepe din stanga:
 *          while(crt.left!=nil)    crt<-crt.left   ->pt crt1 in this, crt2 in  other
 *      crt.next [cat timp e posibil]       ->pt crt1 in this, crt2 in  other
 *          -ori urca in tata
 *          -ori coboara in dreapta
 *          if(crt1!=crt2)  ret false
 *      ret true
 */


///best=θ(1) lungimi inegale, relatii diferite
///avg=worst= O(n)
bool SortedBag::is_equal(const SortedBag &other) {

    if(this->length!=other.length)  return false;
    if(this->relation!=other.relation)  return false;

    nod *nod_crt1 = this->wurzel;
    nod *nod_crt2 = other.wurzel;
    if(!this->isEmpty()) {
        while (nod_crt1->left != nullptr) {
            nod_crt1 = nod_crt1->left;
        }
        while (nod_crt2->left != nullptr) {
            nod_crt2 = nod_crt2->left;
        }
        if(nod_crt1->info==nod_crt2->info) {
            while (nod_crt1->info == nod_crt2->info) {
                if (nod_crt1->right != nullptr) {
                    nod_crt1 = nod_crt1->right;
                    while (nod_crt1->left != nullptr)
                        nod_crt1 = nod_crt1->left;
                } else if (nod_crt1->vater != nullptr and nod_crt1 == nod_crt1->vater->left)
                    nod_crt1 = nod_crt1->vater;
                else {
                    ///urca in vater
                    while (nod_crt1->vater != nullptr and this->relation(nod_crt1->info, nod_crt1->vater->info))
                        nod_crt1 = nod_crt1->vater;
                }

                if (nod_crt2->right != nullptr) {
                    nod_crt2 = nod_crt2->right;
                    while (nod_crt2->left != nullptr)
                        nod_crt2 = nod_crt2->left;
                } else if (nod_crt2->vater != nullptr and nod_crt2 == nod_crt2->vater->left)
                    nod_crt2 = nod_crt2->vater;
                else {
                    while (nod_crt2->vater != nullptr and other.relation(nod_crt2->info, nod_crt2->vater->info))
                        nod_crt2 = nod_crt2->vater;
                }

                if (nod_crt1->info != nod_crt2->info) return false;
            }
        }
        else return false;
    }
    return true;
}

