#include <assert.h>
#include <iostream>
#include "Matrix.h"

using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
    //std::clog<<"short test1 passed"<<std::endl;
	assert(m.nrColumns() == 4);
    //std::clog<<"short test2 passed"<<std::endl;
	m.modify(1, 1, 5);
    //std::cout<<m.element(1,1);
	assert(m.element(1, 1) == 5);
    //std::clog<<"short test3 passed"<<std::endl;
	m.modify(1, 1, 6);
    //std::cout<<m.element(1,1);
    //std::clog<<"short test4 passed"<<std::endl;
	assert(m.element(1, 2) == NULL_TELEM);
    //std::clog<<"short test5 passed"<<std::endl;
}