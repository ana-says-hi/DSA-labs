#pragma once
//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Matrix {

    ///2. ADT Matrix – repräsentiert als schwachbesetze Matrix (sparse) in dem Compressed
    ///Column Storage Format (CCS) mithilfe von dynamischen Arrays

private:
    int nrLine;
    int nrCols;

    int *spalte;
    int *zeile;
    TElem *wert;

    int dimSpalten;
    int dimZeile;

    int capSpalten;
    int capZeilen;

    void resizeup();
    void resizedown();


public:
    ///constructor
    Matrix(int nrLine, int nrCols);

    ///returns the number of lines
    int nrLines() const;

    ///returns the number of columns
    int nrColumns() const;

    ///returns the element from line i and column j (indexing starts from 0)
    ///throws exception if (i,j) is not a valid position in the Matrix
    TElem element(int i, int j) const;

    ///modifies the value from line i and column j
    ///returns the previous value from the position
    ///throws exception if (i,j) is not a valid position in the Matrix
    TElem modify(int i, int j, TElem e);


    //TODO resize in jos si resize in sus in metoda de remove
    //TODO complexitati

    // destructor
    ~Matrix();

    void transpusa();

};
