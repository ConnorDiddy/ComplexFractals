#include "ComplexFractal.h"
#include <cmath>

ComplexFractal::ComplexFractal( )
    : ThreadedGrid(201, 301), mMin_X(-1.5), mMax_X(1.5), mMin_Y(-1), mMax_Y(1), mDelta_X(0.01), mDelta_Y(0.01) {
}

ComplexFractal::ComplexFractal( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y )
    : ThreadedGrid( height, width ), mMin_X(min_x), mMax_X(max_x), mMin_Y(min_y), mMax_Y(max_y), mDelta_X(0.01), mDelta_Y(0.01) {
        setGridSize( height, width );
}

ComplexFractal::~ComplexFractal( ) {
}

double ComplexFractal::getMinX() const {
    return mMin_X;
}

double ComplexFractal::getMaxX() const {
    return mMax_X;
}

double ComplexFractal::getMinY() const {
    return mMin_Y;
}

double ComplexFractal::getMaxY() const {
    return mMax_Y;
}

void ComplexFractal::setGridSize( const int& height, const int& width ) {
    if ( height < 2 || width < 2 ) {
        return;
    }

    NumberGrid::setGridSize( height, width );
    double delta_X = calculateDeltaX();
    double delta_Y = calculateDeltaY();

    setDeltas( delta_X, delta_Y );
}

void ComplexFractal::setPlaneSize( const double& min_x, const double& max_x, const double& min_y, const double& max_y ) {
    if ( 
        min_x < -2.0 || 
        min_x > 2.0 || 
        max_x < -2.0 || 
        max_x > 2.0 || 
        min_y < -2.0 || 
        min_y > 2.0 || 
        max_y < -2.0 || 
        max_y > 2.0 ||
        min_x == max_x ||
        min_y == max_y
    )
    {
        return;
    }

    double small_x = std::min( min_x, max_x);
    double small_y = std::min( min_y, max_y);
    double big_x = std::max( min_x, max_x);
    double big_y = std::max( min_y, max_y);

    mMin_X = small_x;
    mMin_Y = small_y;
    mMax_X = big_x;
    mMax_Y = big_y;

    double delta_X = calculateDeltaX();
    double delta_Y = calculateDeltaY();
    setDeltas( delta_X, delta_Y );

}

double ComplexFractal::getDeltaX() const {
    return mDelta_X;
}

double ComplexFractal::getDeltaY() const {
    return mDelta_Y;
}

void ComplexFractal::setDeltas( const double& delta_x, const double& delta_y ) {
    if ( delta_x > 0 && delta_y > 0 ) {
        mDelta_X = delta_x;
        mDelta_Y = delta_y;
    }
}

double ComplexFractal::calculateDeltaX( ) const {
    double delta_x = (mMax_X - mMin_X) / ( this->getWidth() -1 );

    return delta_x;
}

double ComplexFractal::calculateDeltaY( ) const {
    double delta_y = (mMax_Y - mMin_Y) / ( this->getHeight() -1 );

    return delta_y;
}

double ComplexFractal::calculatePlaneXFromPixelColumn( const int& column ) const {
    if ( column < 0 || column >= this->getWidth() ) { return 0; }

    double x_column = mMin_X + column * mDelta_X;

    return x_column;
}

double ComplexFractal::calculatePlaneYFromPixelRow( const int& row ) const {
    if ( row < 0 || row >= this->getHeight() ) { return 0; }

    double y_row = mMax_Y - row * mDelta_Y;

    return y_row;
}

void ComplexFractal::calculatePlaneCoordinatesFromPixelCoordinates( const int& row, const int& column, double& x, double& y ) const {
    if ( row < 0 || row >= this->getHeight() || column < 0 || column >= this->getWidth() ) {
        x = 0;
        y = 0;
        return;
    }

    x = calculatePlaneXFromPixelColumn( column );
    y = calculatePlaneYFromPixelRow( row );
}

int ComplexFractal::calculateNumber( const int& row, const int& column ) const {
    if ( row < 0 || row >= this->getHeight() || column < 0 || column >= this->getWidth() ) {
        return -1;
    }

    double x = calculatePlaneXFromPixelColumn( column );
    double y = calculatePlaneYFromPixelRow( row );

    int num = std::abs(getMaxNumber() * std::sin(10*x) * std::cos(10*y));

    return num;
}

void ComplexFractal::zoomPlane(const double& zoom_factor) {
    double cur_x_size = mMax_X - mMin_X;
    double des_x_size = cur_x_size * zoom_factor;
    double x_change = (cur_x_size - des_x_size) / 2;
    double new_min_x = mMin_X + x_change;
    if ( new_min_x < -2.0 ) { new_min_x = -2.0; }
    if ( new_min_x > 2.0 ) { new_min_x = 2.0; }
    double new_max_x = mMax_X - x_change;
    if ( new_max_x < -2.0 ) { new_max_x = -2.0; }
    if ( new_max_x > 2.0 ) { new_max_x = 2.0; }

    double cur_y_size = mMax_Y - mMin_Y;
    double des_y_size = cur_y_size * zoom_factor;
    double y_change = (cur_y_size - des_y_size) / 2;
    double new_min_y = mMin_Y + y_change;
    if ( new_min_y < -2.0 ) { new_min_y = -2.0; }
    if ( new_min_y > 2.0 ) { new_min_y = 2.0; }
    double new_max_y = mMax_Y - y_change;
    if ( new_max_y < -2.0 ) { new_max_y = -2.0; }
    if ( new_max_y > 2.0 ) { new_max_y = 2.0; }

    this->setPlaneSize( new_min_x, new_max_x, new_min_y, new_max_y );
}