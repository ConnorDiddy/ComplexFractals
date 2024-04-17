#include "image_menu.h"
#include <cmath>

MandelbrotSet::MandelbrotSet( )
    : ComplexFractal() 
{}

MandelbrotSet::MandelbrotSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y )
    : ComplexFractal( height, width, min_x, max_x, min_y, max_y )
{}

MandelbrotSet::~MandelbrotSet( ) {}

void MandelbrotSet::calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double &y1 ) const {
    x1 = (x0 * x0) - (y0 * y0) + a;
    y1 = (2 * x0 * y0) + b;
}

int MandelbrotSet::calculatePlaneEscapeCount( const double& a, const double& b ) const {
    double x0 = 0;
    double y0 = 0;
    double x1, y1;

    calculateNextPoint( x0, y0, a, b, x1, y1 );

    double distance = std::sqrt( x1 * x1 + y1 * y1 );

    int escapes = 0;

    while ( distance >= -2.0 && distance <= 2.0 ) {
        if ( escapes >= mMaxNumber ) { return mMaxNumber; }
        calculateNextPoint( x1, y1, a, b, x1, y1 );
        distance = std::sqrt( x1 * x1 + y1 * y1 );
        escapes++;
    }

    return escapes;
}

int MandelbrotSet::calculateNumber( const int& row, const int& column ) const {
    if ( row >= mHeight || column >= mWidth || row < 0 || column < 0 ) { return -1; }

    double x = 0;
    double y = 0;

    calculatePlaneCoordinatesFromPixelCoordinates( row, column, x, y );
    int count = calculatePlaneEscapeCount( x, y );

    return count;
}