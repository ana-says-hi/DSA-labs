#include "Matrix.h"
#include <exception>
#include <iostream>

using namespace std;

/*!
 * best: o coloana θ(1)
 * worst: Ω(n)
 * avg: O(n)
 */
Matrix::Matrix(int nrLine, int nrCols) {    /// comp = θ(n) -n nr de coloane

    this->nrLine = nrLine;
    this->nrCols = nrCols;

    this->dimSpalten = nrCols + 1;
    this->capSpalten = this->dimSpalten; //nu se schimba, nu are dc, capSpalten e putin nefolositor
    this->dimZeile = 0;
    this->capZeilen = 1;

    spalte = new int(capSpalten);
    zeile = new int(capZeilen);
    wert = new TElem(capZeilen);

    ///matricea e goala -> spalten:{0,0,0,0,0,0}
    /// pt o matrice de 5 coloane   [numerotarea incepe de la 0]
    for (int j = 0; j < dimSpalten; j++)
        this->spalte[j] = dimZeile;
}

//! best=worst=avg=θ(1)
//pre:-   post:n
int Matrix::nrLines() const {    ///comp = θ(1)
    //TODO - Implementation
    return this->nrLine;
}

//! best=worst=avg=θ(1)

//pre:-   post:n
int Matrix::nrColumns() const {     ///comp = θ(1)
    //TODO - Implementation
    return this->nrCols;
}

/*!
 * best case: indexul e invalid->exception, θ(1)
 *            coloana nu ere elemente, 2 pasi -> θ(2) apartine de θ(1)
 *            elementul este primul de pe coloana
 * worst case: elemntul este pe ultimul de pe coloana
 * average case: O(n)
*/

/*!
 * pre
 * @param i
 * @param j
 *
 * post
 * @return e [TElem de pe poz (i,j) in matrice]
 */
TElem Matrix::element(int i, int j) const {     ///comp = O(n)
    //TODO - Implementation
    exception InvalidIndex;
    if (i < this->nrLines() and i >= 0 and j < this->nrColumns() and j >= 0) {  ///validare i si j
        //clog<< j << "    |" <<spalte[j]<<"  :  "<<spalte[j+1]-1<<endl;
//        if (spalte[j] == spalte[j + 1]) {
//            clog << i << ' ' << j << " null" << endl;
//            return NULL_TELEM;
//        }
        for (int z = this->spalte[j]; z <= this->spalte[j + 1] - 1; z++) {
            //clog<<"i= "<<i<<"  z= "<<z<<endl;
            if (zeile[z] == i) {
                //clog << wert[z];
                return wert[z];
            }
        }
        //clog << i << ' ' << j << " null" << endl;
        return NULL_TELEM;
    }
    throw InvalidIndex;
}


/*!
 * best: θ(n)
 * worst: Ω(n^2)
 * avg: O(n^2)
 *
 * complexitati amortizate
 * best: θ(n)
 * worst: Ω(n^2)
 * avg: O(n^2)
 */

/// primeste i, j si e(val cu care sa schimbe)      pre
///returneaza valoarea care era inainte     post

//!
//! \param i
//! \param j
//! \param e
//! \return
TElem Matrix::modify(int i, int j, TElem e) {
    //TODO inversat conditii & clean code
    resizeup(); ///O(n)
    int start_int = this->spalte[j];  //start interval cautare -> randurile cu elem nenule pt acele coloane
    int end_int = this->spalte[j + 1] - 1; // sf interval cautare
    if (e != 0) {
        //cout<<e<< " e "<<endl;
        if (spalte[j] == spalte[j + 1]) {   ///compl=O(n)

            for (int inc_sp = j + 1; inc_sp < dimSpalten; inc_sp++)
                spalte[inc_sp]++;

            dimZeile++;
            resizeup(); ///O(n)

            for (int indx = this->dimZeile; indx > spalte[j]; indx--) { //z= poz pe care adaug
                zeile[indx] = zeile[indx - 1];
                wert[indx] = wert[indx - 1];
            }
            zeile[spalte[j]] = i;
            wert[spalte[j]] = e;
            return NULL_TELEM;
        }
        //coloana are elemente
        for (int z = start_int; z <= end_int; z++) {    ///comp=O(n^2)
            if (zeile[z] == i) {   //a gasit elementul
                TElem aux;
                aux = wert[z];
                //cout<<z<<wert[z];
                wert[z] = e;
                return aux;
                //return e;
            }

            // elem trebuie inserat
            dimZeile++;
            resizeup();
            //spalte[j + 1]++; /// urmatorea coloana incepe mai incolo cu un elem
            if (i > zeile[end_int]) // ultimul zeile cu wert de pe coloana asta
                z = end_int;
            if (i <= z || z == end_int) {
                for (int indx = this->dimZeile; indx > z; indx--) { ///z= poz pe care adaug
                    zeile[indx] = zeile[indx - 1];
                    wert[indx] = wert[indx - 1];
                }
                zeile[z] = i;
                wert[z] = e;
                return NULL_TELEM;
            }
        }

    }
    {    //!    O(n^2)
        //old e = 0 -> nimic
        if (start_int <= i and i <= nrLines()) {  //  TODO nr lines
            for (int z = start_int; z <= end_int; z++)
                if (zeile[z] == i) {
                    //shift left zeile & wert
                    for (int strt_new = z; strt_new < dimZeile; strt_new++) {
                        zeile[strt_new] = zeile[strt_new + 1];
                        wert[strt_new] = wert[strt_new + 1];
                    }
                    dimZeile--;
                    resizedown();
                    return NULL_TELEM;
                }
        }
    }
    resizedown();   ///O(n)
    return NULL_TELEM;
}


Matrix::~Matrix() {
    delete[] this->spalte;
    delete[] this->zeile;
    delete[] this->wert;
}


/*!
 * best case: nu trebuie schimbata marimea  -> θ(1)
 * in rest O(n) din cauza copierii
 * worst: Ω(n)
 * avg: O(n)
 */
void Matrix::resizeup() {
    if (dimZeile != capZeilen) {
        return;
    }
    this->capZeilen = this->capZeilen * 2;

    int *new_zeile = new int(this->capZeilen);
    TElem *new_wert = new TElem(this->capZeilen);

    for (int i = 0; i < dimZeile; i++) { ///copiaza elemetele
        new_zeile[i] = zeile[i];
        new_wert[i] = wert[i];
    }

    delete[] zeile;
    delete[] wert;

    zeile = new_zeile;
    wert = new_wert;
}

void Matrix::resizedown() {
    if (dimZeile != capZeilen / 4) {
        return;
    }
    this->capZeilen = this->capZeilen / 2;

    int *new_zeile = new int(this->capZeilen);
    TElem *new_wert = new TElem(this->capZeilen);

    for (int i = 0; i < dimZeile; i++) {    ///copiaza elementele
        new_zeile[i] = zeile[i];
        new_wert[i] = wert[i];
    }

    delete[] zeile;
    delete[] wert;

    zeile = new_zeile;
    wert = new_wert;
}


void Matrix::transpusa() {
    int new_j = 0, new_i = 0; //noii indici in new_spalte si new_zeile
    int *new_zeile = new int(dimZeile);  //coloanele transpuse
    int *new_spalte = new int(nrLines() + 1);    //randurile transpuse
    int *new_wert = new int(dimZeile);   //valorile rearanjate

    while (new_j < nrLine) {
        for (int z = 0; z < dimZeile; z++) {
            if (zeile[z] == new_j) {
                for (int sp = 0; sp < dimSpalten - 1; sp++) {
                    if (spalte[sp] == z or spalte[sp + 1] > z and spalte[sp] < z) {
                        /// adauga elem in matrice [in new_zeile, -spalte, -wert]
                        new_zeile[new_i] = sp;
                        new_wert[new_i] = wert[z];
                        new_i++;
                    }
                }
            }
        }
        new_j++;
        new_spalte[new_j] = new_i;
    }

    //matricea ia noile valori

    delete[] this->spalte;
    delete[] this->zeile;
    delete[] this->wert;

    spalte = new_spalte;
    zeile = new_zeile;
    wert = new_wert;

    int aux = nrLine;
    nrLine = nrCols;
    nrCols = aux;

}