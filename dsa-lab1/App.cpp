
#include <iostream>
#include <cassert>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"

using namespace std;


int main() {

    Matrix m(4, 5);
    assert(m.nrLines() == 4);
    assert(m.nrColumns() == 5);
    m.modify(1, 1, 5);
    m.modify(1, 3, 6);
    assert(m.element(1, 1) == 5);
    m.transpusa();
    assert(m.nrLines() == 5);
    assert(m.nrColumns() == 4);
    assert(m.element(1, 1) == 5);
    assert(m.element(3, 1) == 6);
    assert(m.element(1, 2) == NULL_TELEM);


	testAll();
	testAllExtended();
	cout << "Test End" << endl;
	system("pause");
}