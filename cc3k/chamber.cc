#include <cstdlib>

using namespace std;

#include "chamber.h"

/*********** Chamber ***********
 Purpose: constructor for Chamber which consumes an interger
 
 Returns: N/A
 
 Errors: none
 *********************************/
Chamber::Chamber(int numRow) {
    this->numRow = numRow;
    
    r = new int*[numRow];
    for (int i = 0; i < numRow; i++) {
        r[i] = new int[2];
    }
    
    c = new int*[numRow];
    for (int i = 0; i < numRow; i++) {
        c[i] = new int[2];
    }
}

/*********** ~Chamber ***********
 Purpose: destructor for Chamber
 
 Returns: N/A
 
 Errors: none
 *********************************/
Chamber::~Chamber() {
    for (int i = 0; i < numRow; i++) {
        delete [] r[i];
        r[i] = 0;
    }
    delete [] r;
    r = 0;
    
    for (int i = 0; i < numRow; i++) {
        delete [] c[i];
        c[i] = 0;
    }
    delete [] c;
    c = 0;
}

/*********** setObjectCoords ***********
 Purpose: function which sets the row and column number for a boundary of a row of a chamber
 
 Returns: void
 
 Errors: none
 *********************************/
void Chamber::setObjectCoords(int thisR, int thisC, int r, int c) {
    this->r[thisR][thisC] = r;
    this->c[thisR][thisC] = c;
}

/*********** setTotalNumRow ***********
 Purpose: function which sets total number of row of the chamber
 
 Returns: void
 
 Errors: none
 *********************************/
void Chamber::setTotalNumRow(int bottom, int top) {
    totalNumRow = bottom - top + 1;
}

/*********** setTotalNumColumn ***********
 Purpose: function which sets total number of columns of the chamber
 
 Returns: void
 
 Errors: none
 *********************************/
void Chamber::setTotalNumColumn(int left, int right) {
    totalNumColumn = right - left + 1;
}


/*********** setTopBound ***********
 Purpose: function which sets the topmost row of the chamber
 
 Returns: void
 
 Errors: none
 *********************************/
void Chamber::setTopBound(int topBound) {
    this->topBound = topBound;
}

/*********** setBottomBound ***********
 Purpose: function which sets the bottommostmost row of the chamber
 
 Returns: void
 
 Errors: none
 *********************************/
void Chamber::setBottomBound(int bottomBound) {
    this->bottomBound = bottomBound;
}

/*********** setLeftBound ***********
 Purpose: function which sets the leftmost column of the chamber
 
 Returns: void
 
 Errors: none
 *********************************/
void Chamber::setLeftBound(int leftBound) {
    this->leftBound = leftBound;
}

/*********** setRightBound ***********
 Purpose: function which sets the rightmost column of the chamber
 
 Returns: void
 
 Errors: none
 *********************************/
void Chamber::setRightBound(int rightBound) {
    this->rightBound = rightBound;
}

/*********** getTotalNumRow ***********
 Purpose: function which produces the total number of rows in the chamber
 
 Returns: int
 
 Errors: none
 *********************************/
int Chamber::getTotalNumRow() {
    return totalNumRow;
}

/*********** getTotalNumColumn ***********
 Purpose: function which produces the total number of columns in the chamber
 
 Returns: int
 
 Errors: none
 *********************************/
int Chamber::getTotalNumColumn() {
    return totalNumColumn;
}

/*********** getNumRows ***********
 Purpose: function which sets the row and column number for object
 
 Returns: int
 
 Errors: none
 *********************************/
int Chamber::getNumRows() {
    return numRow;
}

/*********** getColumnFirstBox ***********
 Purpose: function which sets the row and column number for object
 
 Returns: int
 
 Errors: none
 *********************************/
int Chamber::getColumnFirstBox(int rowNum) {
    return c[rowNum][0];
}

/*********** getColumnLastBox ***********
 Purpose: function which sets the row and column number for object
 
 Returns: int
 
 Errors: none
 *********************************/
int Chamber::getColumnLastBox(int rowNum) {
    return c[rowNum][1];
}

/*********** getChamberRow ***********
 Purpose: function which sets the row and column number for object
 
 Returns: int
 
 Errors: none
 *********************************/
int Chamber::getChamberRow() {
    return rand() % (numRow - 2) + 1;
}

/*********** getRowNumber ***********
 Purpose: function which sets the row and column number for object
 
 Returns: int
 
 Errors: none
 *********************************/
int Chamber::getRowNumber(int chamberRowNum) {
    return r[chamberRowNum][0];
}

/*********** getColumnNumber ***********
 Purpose: function which sets the row and column number for object
 
 Returns: int
 
 Errors: none
 *********************************/
int Chamber::getColumnNumber(int chamberRowNum) {
    return rand() % (c[chamberRowNum][1] - c[chamberRowNum][0] - 1) + c[chamberRowNum][0] + 1;
}

/*********** getTopBound ***********
 Purpose: function which sets the row and column number for object
 
 Returns: int
 
 Errors: none
 *********************************/
int Chamber::getTopBound() {
    return topBound;
}

/*********** getBottomBound ***********
 Purpose: function which sets the row and column number for object
 
 Returns: int
 
 Errors: none
 *********************************/
int Chamber::getBottomBound() {
    return bottomBound;
}

/*********** getLeftBound ***********
 Purpose: function which sets the row and column number for object
 
 Returns: int
 
 Errors: none
 *********************************/
int Chamber::getLeftBound() {
    return leftBound;
}

/*********** getRightBound ***********
 Purpose: function which sets the row and column number for object
 
 Returns: int
 
 Errors: none
 *********************************/
int Chamber::getRightBound() {
    return rightBound;
}