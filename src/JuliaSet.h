#ifndef JULIA_SET_H
#define JULIA_SET_H

#include "ComplexFractal.h"

class JuliaSet: public ComplexFractal {
    public:
        JuliaSet( );
        JuliaSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y, const double& a, const double& b );
        virtual ~JuliaSet( );
        double getA( ) const;
        double getB( ) const;
        void setParameters( const double& a, const double& b );
        virtual void calculateNextPoint( const double x0, const double y0, double& x1, double &y1 ) const;
        virtual int calculatePlaneEscapeCount( const double& x0, const double& y0 ) const;
        virtual int calculateNumber( const int& row, const int& column ) const;
    
    protected:
        double mA;
        double mB;
};

class JuliaSetFour: public JuliaSet {
    public:
        JuliaSetFour();
        virtual ~JuliaSetFour();
        virtual void calculateNextPoint(const double x0, const double y0, double& x1, double &y1) const;
};

#endif