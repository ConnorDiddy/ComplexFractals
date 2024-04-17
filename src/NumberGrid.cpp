#include <vector>
#include "image_menu.h"

NumberGrid::NumberGrid() 
    : mHeight(300), mWidth(400), mMaxNumber(255),  mGridNumbers(300 * 400, 0) {
}

NumberGrid::NumberGrid( const int& height, const int& width )
    : mHeight(height), mWidth(width), mMaxNumber(255), mGridNumbers(height * width, 0) {
}

NumberGrid::~NumberGrid() {
    // Leaving empty
}

int NumberGrid::getHeight( ) const {
    return mHeight;
}

int NumberGrid::getWidth( ) const {
    return mWidth;
}

int NumberGrid::getMaxNumber( ) const {
    return mMaxNumber;
}

void NumberGrid::setGridSize( const int& height, const int& width ) {
    if ( height > 1 && width > 1 ) {
        mHeight = height;
        mWidth = width;
        mGridNumbers.resize(height * width);
    }
}

void NumberGrid::setMaxNumber( const int& number ) {
    if ( number >= 0 ) {
        mMaxNumber = number;
    }
    // The state of grid values that are larger than 
    // the new maximum allowed value is undefined.
    // ^ Whatever that means?
}

const std::vector< int >& NumberGrid::getNumbers( ) const {
    return mGridNumbers;
}

int NumberGrid::index( const int& row, const int& column ) const {
    return (row * this->getWidth() + column);
}

bool NumberGrid::indexValid( const int& row, const int& column ) const {
    if ( row >= 0 && row < this->getHeight() ) {
        if ( column >= 0 && column < this->getWidth() ) {
            return true;
        }
    }
    return false;
}

bool NumberGrid::numberValid( const int& number ) const {
    if ( number >= 0 && number <= this->getMaxNumber() ) {
        return true;
    }
    return false;
}

int NumberGrid::getNumber( const int& row, const int& column ) const {
    if ( indexValid(row, column) ) {
        int width = this->getWidth();
        int index = width * row;
        index += column;

        return mGridNumbers[index];
    }
    return -1;
}

void NumberGrid::setNumber( const int& row, const int& column, const int& number ) {
    if ( indexValid(row, column) && numberValid(number) ) {
        int width = this->getWidth();
        int index = width * row;
        index += column;

        mGridNumbers[index] = number;
    }
}

void NumberGrid::setPPM( PPM& ppm ) const {
    ppm.setHeight(mHeight);
    ppm.setWidth(mWidth);
    ppm.setMaxColorValue(63);

    for (int r=0; r < ppm.getHeight(); r++) {
        // For each row
        for (int c=0; c < ppm.getWidth(); c++) {
            // For each column
            int number = this->getNumber( r, c );

            if (number == 0) { ppm.setPixel( r, c, 0, 0, 0 ); }
            else if (number == mMaxNumber) { ppm.setPixel( r, c, 63, 31, 31 ); }
            else if (number % 8 == 0) { ppm.setPixel( r, c, 63, 63, 63 ); }
            else if (number % 8 == 1) { ppm.setPixel( r, c, 63, 31, 31 ); }
            else if (number % 8 == 2) { ppm.setPixel( r, c, 63, 63, 31 ); }
            else if (number % 8 == 3) { ppm.setPixel( r, c, 31, 63, 31 ); }
            else if (number % 8 == 4) { ppm.setPixel( r, c, 0, 0, 0 ); }
            else if (number % 8 == 5) { ppm.setPixel( r, c, 31, 63, 63 ); }
            else if (number % 8 == 6) { ppm.setPixel( r, c, 31, 31, 63 ); }
            else if (number % 8 == 7) { ppm.setPixel( r, c, 63, 31, 63 ); }
        }
    }
}

void NumberGrid::setPPM( PPM& ppm, const ColorTable& colors ) const {
    
    if ( colors.getNumberOfColors() < 2 )  { return; }// Only make a change if more than 2 colors

    ppm.setHeight(mHeight);
    ppm.setWidth(mWidth);
    ppm.setMaxColorValue( colors.getMaxChannelValue() );
    
        for (int r=0; r < ppm.getHeight(); r++ ) {
            for (int c=0; c < ppm.getWidth(); c++ ) {
                int grid_number = this->getNumber( r, c );

                Color color = colors[grid_number % colors.getNumberOfColors()];
                ppm.setPixel( r, c, color.getRed(), color.getGreen(), color.getBlue() );

                if (grid_number == this->getMaxNumber() ) {
                    Color color = colors[colors.getNumberOfColors() - 1];

                    ppm.setPixel( r, c, color.getRed(), color.getGreen(), color.getBlue() );
                }                
            }
        }
    
}

void NumberGrid::calculateAllNumbers() {
    for ( int r=0; r < this->getHeight(); r++ ) {
        for ( int c=0; c < this->getWidth(); c++ ) {
            int number = calculateNumber( r, c );
            setNumber( r, c, number );
        }
    }
}