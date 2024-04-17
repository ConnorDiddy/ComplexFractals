#include "image_menu.h"
#include <cmath>

JuliaSet::JuliaSet()
    :   ComplexFractal(), mA(-0.650492), mB(-0.478235) // Need to set max number
{
}

JuliaSet::JuliaSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y, const double& a, const double& b )
    :   ComplexFractal( height, width, min_x, max_x, min_y, max_y ), mA(a), mB(b)
{
}

JuliaSet::~JuliaSet( ) {}

double JuliaSet::getA( ) const {
    return mA;
}

double JuliaSet::getB( ) const {
    return mB;
}

void JuliaSet::setParameters( const double& a, const double& b ) {
    if ( 
        a < -2.0 || 
        a > 2.0 ||
        b < -2.0 ||
        b > 2.0
    ) { return; }

    mA = a;
    mB = b;
}

void JuliaSet::calculateNextPoint( const double x0, const double y0, double& x1, double &y1 ) const {
    x1 = (x0 * x0) - (y0 * y0) + mA;
    y1 = (2 * x0 * y0) + mB;
}

int JuliaSet::calculatePlaneEscapeCount( const double& x0, const double& y0 ) const {
    double distance = std::sqrt( x0 * x0 + y0 * y0 );

    int escapes = 0;
    double x1 = x0;
    double y1 = y0;

    while ( distance >= -2.0 && distance <= 2.0 ) {
        if ( escapes >= mMaxNumber ) { return mMaxNumber; }
        calculateNextPoint( x1, y1, x1, y1 );
        distance = std::sqrt( x1 * x1 + y1 * y1 );
        escapes++;
    }

    return escapes;
}

int JuliaSet::calculateNumber( const int& row, const int& column ) const {

    if ( row >= mHeight || column >= mWidth || row < 0 || column < 0 ) { return -1; }

    double x = 0;
    double y = 0;

    calculatePlaneCoordinatesFromPixelCoordinates( row, column, x, y );
    int count = calculatePlaneEscapeCount( x, y );

    return count;
}

JuliaSetFour::JuliaSetFour()
    : JuliaSet()
{}

JuliaSetFour::~JuliaSetFour() {};

void JuliaSetFour::calculateNextPoint(const double x0, const double y0, double& x1, double &y1) const {
    /*
    x1 = (x0 * x0) - (y0 * y0) + mA;
    y1 = (2 * x0 * y0) + mB;
    */

   x1 = (x0 * x0 * x0 * x0) - (6  * x0 * x0 * y0 * y0) + (y0 * y0 * y0 * y0) + mA;
   y1 = (4 * x0 * x0 * x0 * y0) - (4 * x0 * y0 * y0 * y0) + mB;
}