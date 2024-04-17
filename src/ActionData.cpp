#include "image_menu.h"

ActionData::ActionData( std::istream& is, std::ostream& os ) 
    : mIs(is), mOs(os), mInputImage1(), mInputImage2(), mOutputImage(), mDone(false), mNumberGrid(0), mColorTable(16) {
        Color c1( 0, 255, 0 );
        Color c2( 255, 0, 255 );
        
        mColorTable.insertGradient( c1, c2, 0, 15 );
}

std::istream& ActionData::getIS() {
    return mIs;
}

std::ostream& ActionData::getOS() {
    return mOs;
}

PPM& ActionData::getInputImage1() {
    return mInputImage1;
}

PPM& ActionData::getInputImage2() {
    return mInputImage2;
}

PPM& ActionData::getOutputImage() {
    return mOutputImage;
}

bool ActionData::getDone() const{
    return mDone;
}

void ActionData::setDone() {
    mDone = true;
}

ActionData::~ActionData() {
    if (mNumberGrid != 0) {
        delete mNumberGrid;
        mNumberGrid = 0;
    }
}

NumberGrid& ActionData::getGrid() {
    return *mNumberGrid;
}

void ActionData::setGrid(NumberGrid *grid) {
    if (mNumberGrid != 0) {
        delete mNumberGrid;
        mNumberGrid = 0;
    }
    mNumberGrid = grid;
}

ColorTable& ActionData::getTable() {
    return mColorTable;
}