#ifndef __CHAMBER_H__
#define __CHAMBER_H__

class Chamber {
    int** r;
    int** c;
    int numRow;
    int totalNumRow;
    int totalNumColumn;
    int topBound;
    int bottomBound;
    int leftBound;
    int rightBound;
    
public:
    Chamber(int numRow);
    ~Chamber();
    void setObjectCoords(int thisR, int thisC, int r, int c);
    void setTotalNumRow(int top, int bottom);
    void setTotalNumColumn(int left, int right);
    void setTopBound(int topBound);
    void setBottomBound(int bottomBound);
    void setLeftBound(int leftBound);
    void setRightBound(int rightBound);
    int getTotalNumRow();
    int getTotalNumColumn();
    int getNumRows();
    int getColumnFirstBox(int rowNum);
    int getColumnLastBox(int rowNum);
    int getChamberRow();
    int getRowNumber(int chamberRowNum);
    int getColumnNumber(int chamberRowNum);
    int getTopBound();
    int getBottomBound();
    int getLeftBound();
    int getRightBound();
};

#endif