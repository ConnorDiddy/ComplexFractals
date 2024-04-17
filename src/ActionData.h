#ifndef ACTION_DATA_H
#define ACTION_DATA_H

#include <iostream>
#include "PPM.h"
#include "NumberGrid.h"
#include "ColorTable.h"

/**
 * ActionData class description etc.
 * 
 * Requirement: A3985-G4
 */
class ActionData {
public:
    ActionData(std::istream& is, std::ostream& os);
    std::istream& getIS();
    std::ostream& getOS();
    PPM& getInputImage1();
    PPM& getInputImage2();
    PPM& getOutputImage();
    bool getDone() const;
    void setDone();
    ~ActionData();
    NumberGrid& getGrid();
    void setGrid(NumberGrid *grid);
    ColorTable& getTable();

private:
    std::istream& mIs;
    std::ostream& mOs;
    PPM mInputImage1;
    PPM mInputImage2;
    PPM mOutputImage;
    bool mDone;
    NumberGrid *mNumberGrid;
    ColorTable mColorTable;
};

#endif