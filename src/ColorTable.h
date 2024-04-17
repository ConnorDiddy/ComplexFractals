#ifndef COLOR_TABLE_H
#define COLOR_TABLE_H

#include <ostream>
#include <vector>

void HSV_to_RGB(const double& hue, const double& saturation, const double& value, double& red, double &green, double& blue);
void RGB_to_HSV(const double& red0, const double &green0, const double& blue0, double& hue, double& saturation, double& value);

/**
 * The color class stores all information needed to store a color. Supports both HSV and RGB
 * 
 * Requirement: A3985-G4
 */
class Color {
    public:
    Color ( );
    Color( const int& red, const int& green, const int& blue );
    int getRed( ) const;
    int getGreen( ) const;
    int getBlue( ) const;
    int getChannel( const int& channel ) const;
    void setRed( const int& value );
    void setGreen( const int& value );
    void setBlue( const int& value );
    void setChannel( const int& channel, const int& value );
    void invert( const int& max_color_value );
    bool operator==( const Color& rhs ) const;
    void setFromHSV(const double& hue, const double& saturation, const double& value);
    void getHSV(double& hue, double& saturation, double& value) const;

    // Functions
    friend std::ostream& operator<<( std::ostream& os, const Color& color );

    private:
    double mRed;
    double mGreen;
    double mBlue;
};

class ColorTable {
    public:
    ColorTable( const int& num_color );
    int getNumberOfColors( ) const;
    void setNumberOfColors( const int& num_color );
    const Color& operator[]( const int& i ) const;
    Color& operator[]( const int& i );
    void setRandomColor( const int& max_color_value, const int& position );
    double gradientSlope(const double y1, const double y2, const double x1, const double x2) const;
    double gradientValue(const double y1, const double x1, const double slope, const double x) const;
    void insertGradient( const Color& color1, const Color& color2, const int& position1, const int& position2 );
    int getMaxChannelValue( ) const;
    void insertInvertedGradient(const Color& color1, const int& position1, const int& position2);
    void insertEasyRandomGradient(const int& position1, const int& position2);
    void insertHueSaturationValueGradient(const Color& color1, const Color& color2, const int& position1, const int& position2);

    private:
    std::vector<Color> mColors;

};

#endif