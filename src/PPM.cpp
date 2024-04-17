#include "image_menu.h"
#include <sstream>

PPM::PPM()
    : Image(), mMaxColorValue(1)
{
}

PPM::PPM(const int &height, const int &width)
    : Image(height, width), mMaxColorValue(1)
{
}

int PPM::getMaxColorValue() const
{
    return mMaxColorValue;
}

bool PPM::valueValid(const int &value) const
{
    if (value >= 0 && value <= mMaxColorValue)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PPM::setMaxColorValue(const int &max_color_value)
{
    if (max_color_value >= 1 && max_color_value <= 255)
    {
        mMaxColorValue = max_color_value;
    }
}

void PPM::setChannel(const int &row, const int &column, const int &channel, const int &value)
{
    if (valueValid(value))
    {
        Image::setChannel(row, column, channel, value);
    }
    else
    {
        std::cout << "INVALID VALUE" << std::endl;
    }
}

void PPM::setPixel(const int &row, const int &column, const int &red, const int &green, const int &blue)
{
    Image::setChannel(row, column, 0, red);
    Image::setChannel(row, column, 1, green);
    Image::setChannel(row, column, 2, blue);
}

void PPM::writeStream(std::ostream &os) const
{
    os << "P6 " << PPM::getWidth() << " " << PPM::getHeight() << " " << PPM::getMaxColorValue() << "\n";

    // Write the binary data
    for (int r = 0; r < PPM::getHeight(); r++)
    {
        // For each row
        for (int c = 0; c < PPM::getWidth(); c++)
        {
            // For each column
            for (int ch = 0; ch < 3; ch++)
            {
                // For each channel
                unsigned char byte = PPM::getChannel(r, c, ch);
                os.write((char *)&byte, 1);
            }
        }
    }
}

void PPM::readStream(std::istream &is)
{

    std::string magic_number;
    int width;
    int height;
    int max_color_value;
    std::string newLine;

    is >> magic_number;
    is >> width;
    is >> height;
    is >> max_color_value;
    std::getline( is, newLine );

    if (magic_number != "P6") {
        std::cout << "Invalid magic number: " << magic_number << std::endl;
    }

    PPM::setWidth(width);
    PPM::setHeight(height);
    PPM::setMaxColorValue(max_color_value);

    for (int r = 0; r < PPM::getHeight(); r++)
    {
        // For each row
        for (int c = 0; c < PPM::getWidth(); c++)
        {
            // For each column
            for (int ch = 0; ch < 3; ch++)
            {
                // For each channel
                unsigned char byte;
                is.read((char *)&byte, sizeof( byte ));
                PPM::setChannel(r, c, ch, byte);
            }
        }
    }
}

bool PPM::operator==(const PPM &rhs) const
{
    int lhsPixelCount = this->getWidth() * this->getHeight();
    int rhsPixelCount = rhs.getWidth() * rhs.getHeight();
    return (lhsPixelCount == rhsPixelCount);
}

bool PPM::operator!=(const PPM &rhs) const
{
    int lhsPixelCount = this->getWidth() * this->getHeight();
    int rhsPixelCount = rhs.getWidth() * rhs.getHeight();
    return (lhsPixelCount != rhsPixelCount);
}

bool PPM::operator<(const PPM &rhs) const
{
    int lhsPixelCount = this->getWidth() * this->getHeight();
    int rhsPixelCount = rhs.getWidth() * rhs.getHeight();
    return (lhsPixelCount < rhsPixelCount);
}

bool PPM::operator<=(const PPM &rhs) const
{
    int lhsPixelCount = this->getWidth() * this->getHeight();
    int rhsPixelCount = rhs.getWidth() * rhs.getHeight();
    return (lhsPixelCount <= rhsPixelCount);
}

bool PPM::operator>(const PPM &rhs) const
{
    int lhsPixelCount = this->getWidth() * this->getHeight();
    int rhsPixelCount = rhs.getWidth() * rhs.getHeight();
    return (lhsPixelCount > rhsPixelCount);
}

bool PPM::operator>=(const PPM &rhs) const
{
    int lhsPixelCount = this->getWidth() * this->getHeight();
    int rhsPixelCount = rhs.getWidth() * rhs.getHeight();
    return (lhsPixelCount >= rhsPixelCount);
}

PPM &PPM::operator+=(const PPM &rhs)
{
    for (int r = 0; r < rhs.getHeight(); r++)
    {
        // For each row
        for (int c = 0; c < rhs.getWidth(); c++)
        {
            // For each column
            int rChannel = rhs.getChannel(r, c, 0);
            int gChannel = rhs.getChannel(r, c, 1);
            int bChannel = rhs.getChannel(r, c, 2);
            rChannel += this->getChannel(r, c, 0);
            gChannel += this->getChannel(r, c, 1);
            bChannel += this->getChannel(r, c, 2);
            if (rChannel > this->getMaxColorValue())
            {
                rChannel = this->getMaxColorValue();
            }
            if (gChannel > this->getMaxColorValue())
            {
                gChannel = this->getMaxColorValue();
            }
            if (bChannel > this->getMaxColorValue())
            {
                bChannel = this->getMaxColorValue();
            }
            this->setChannel(r, c, 0, rChannel);
            this->setChannel(r, c, 1, gChannel);
            this->setChannel(r, c, 2, bChannel);
        }
    }

    return *this;
}

PPM &PPM::operator-=(const PPM &rhs)
{
    for (int r = 0; r < rhs.getHeight(); r++)
    {
        // For each row
        for (int c = 0; c < rhs.getWidth(); c++)
        {
            // For each column
            int rChannel = this->getChannel(r, c, 0);
            int gChannel = this->getChannel(r, c, 1);
            int bChannel = this->getChannel(r, c, 2);
            rChannel -= rhs.getChannel(r, c, 0);
            gChannel -= rhs.getChannel(r, c, 1);
            bChannel -= rhs.getChannel(r, c, 2);

            if (rChannel < 0)
            {
                rChannel = 0;
            }
            if (gChannel < 0)
            {
                gChannel = 0;
            }
            if (bChannel < 0)
            {
                bChannel = 0;
            }
            this->setChannel(r, c, 0, rChannel);
            this->setChannel(r, c, 1, gChannel);
            this->setChannel(r, c, 2, bChannel);
        }
    }

    return *this;
}

PPM &PPM::operator*=(const double &rhs)
{
    for (int r = 0; r < this->getHeight(); r++)
    {
        // For each row
        for (int c = 0; c < this->getWidth(); c++)
        {
            // For each column
            int rChannel = this->getChannel(r, c, 0);
            int gChannel = this->getChannel(r, c, 1);
            int bChannel = this->getChannel(r, c, 2);
            rChannel *= rhs;
            gChannel *= rhs;
            bChannel *= rhs;

            if (rChannel < 0)
            {
                rChannel = 0;
            }
            if (gChannel < 0)
            {
                gChannel = 0;
            }
            if (bChannel < 0)
            {
                bChannel = 0;
            }

            if (rChannel > this->getMaxColorValue())
            {
                rChannel = this->getMaxColorValue();
            }
            if (gChannel > this->getMaxColorValue())
            {
                gChannel = this->getMaxColorValue();
            }
            if (bChannel > this->getMaxColorValue())
            {
                bChannel = this->getMaxColorValue();
            }
            this->setChannel(r, c, 0, rChannel);
            this->setChannel(r, c, 1, gChannel);
            this->setChannel(r, c, 2, bChannel);
        }
    }

    return *this;
}

PPM &PPM::operator/=(const double &rhs)
{
    for (int r = 0; r < this->getHeight(); r++)
    {
        // For each row
        for (int c = 0; c < this->getWidth(); c++)
        {
            // For each column
            int rChannel = this->getChannel(r, c, 0);
            int gChannel = this->getChannel(r, c, 1);
            int bChannel = this->getChannel(r, c, 2);
            rChannel /= rhs;
            gChannel /= rhs;
            bChannel /= rhs;

            if (rChannel < 0)
            {
                rChannel = 0;
            }
            if (gChannel < 0)
            {
                gChannel = 0;
            }
            if (bChannel < 0)
            {
                bChannel = 0;
            }

            if (rChannel > this->getMaxColorValue())
            {
                rChannel = this->getMaxColorValue();
            }
            if (gChannel > this->getMaxColorValue())
            {
                gChannel = this->getMaxColorValue();
            }
            if (bChannel > this->getMaxColorValue())
            {
                bChannel = this->getMaxColorValue();
            }
            this->setChannel(r, c, 0, rChannel);
            this->setChannel(r, c, 1, gChannel);
            this->setChannel(r, c, 2, bChannel);
        }
    }

    return *this;
}

PPM PPM::operator+(const PPM &rhs) const
{
    PPM p;
    p.setHeight(this->getHeight());
    p.setWidth(this->getWidth());
    p.setMaxColorValue(this->getMaxColorValue());

    for (int r = 0; r < rhs.getHeight(); r++)
    {
        // For each row
        for (int c = 0; c < rhs.getWidth(); c++)
        {
            // For each column
            int rChannel = this->getChannel(r, c, 0);
            int gChannel = this->getChannel(r, c, 1);
            int bChannel = this->getChannel(r, c, 2);
            rChannel += rhs.getChannel(r, c, 0);
            gChannel += rhs.getChannel(r, c, 1);
            bChannel += rhs.getChannel(r, c, 2);

            if (rChannel > this->getMaxColorValue())
            {
                rChannel = this->getMaxColorValue();
            }
            if (gChannel > this->getMaxColorValue())
            {
                gChannel = this->getMaxColorValue();
            }
            if (bChannel > this->getMaxColorValue())
            {
                bChannel = this->getMaxColorValue();
            }

            p.setChannel(r, c, 0, rChannel);
            p.setChannel(r, c, 1, gChannel);
            p.setChannel(r, c, 2, bChannel);
        }
    }

    return p;
}

PPM PPM::operator-(const PPM &rhs) const
{
    PPM p;
    p.setHeight(this->getHeight());
    p.setWidth(this->getWidth());
    p.setMaxColorValue(this->getMaxColorValue());

    for (int r = 0; r < rhs.getHeight(); r++)
    {
        // For each row
        for (int c = 0; c < rhs.getWidth(); c++)
        {
            // For each column
            int rChannel = this->getChannel(r, c, 0);
            int gChannel = this->getChannel(r, c, 1);
            int bChannel = this->getChannel(r, c, 2);
            rChannel -= rhs.getChannel(r, c, 0);
            gChannel -= rhs.getChannel(r, c, 1);
            bChannel -= rhs.getChannel(r, c, 2);

            if (rChannel < 0)
            {
                rChannel = 0;
            }
            if (gChannel < 0)
            {
                gChannel = 0;
            }
            if (bChannel < 0)
            {
                bChannel = 0;
            }

            p.setChannel(r, c, 0, rChannel);
            p.setChannel(r, c, 1, gChannel);
            p.setChannel(r, c, 2, bChannel);
        }
    }

    return p;
}

PPM PPM::operator*(const double &rhs) const
{
    PPM p;
    p.setHeight(this->getHeight());
    p.setWidth(this->getWidth());
    p.setMaxColorValue(this->getMaxColorValue());

    for (int r = 0; r < p.getHeight(); r++)
    {
        // For each row
        for (int c = 0; c < p.getWidth(); c++)
        {
            // For each column
            int rChannel = this->getChannel(r, c, 0);
            int gChannel = this->getChannel(r, c, 1);
            int bChannel = this->getChannel(r, c, 2);
            rChannel *= rhs;
            gChannel *= rhs;
            bChannel *= rhs;

            if (rChannel < 0)
            {
                rChannel = 0;
            }
            if (gChannel < 0)
            {
                gChannel = 0;
            }
            if (bChannel < 0)
            {
                bChannel = 0;
            }

            if (rChannel > p.getMaxColorValue())
            {
                rChannel = p.getMaxColorValue();
            }
            if (gChannel > p.getMaxColorValue())
            {
                gChannel = p.getMaxColorValue();
            }
            if (bChannel > p.getMaxColorValue())
            {
                bChannel = p.getMaxColorValue();
            }

            p.setChannel(r, c, 0, rChannel);
            p.setChannel(r, c, 1, gChannel);
            p.setChannel(r, c, 2, bChannel);
        }
    }

    return p;
}

PPM PPM::operator/(const double &rhs) const
{
    PPM p;
    p.setHeight(this->getHeight());
    p.setWidth(this->getWidth());
    p.setMaxColorValue(this->getMaxColorValue());

    for (int r = 0; r < p.getHeight(); r++)
    {
        // For each row
        for (int c = 0; c < p.getWidth(); c++)
        {
            // For each column
            int rChannel = this->getChannel(r, c, 0);
            int gChannel = this->getChannel(r, c, 1);
            int bChannel = this->getChannel(r, c, 2);
            rChannel /= rhs;
            gChannel /= rhs;
            bChannel /= rhs;

            if (rChannel < 0)
            {
                rChannel = 0;
            }
            if (gChannel < 0)
            {
                gChannel = 0;
            }
            if (bChannel < 0)
            {
                bChannel = 0;
            }

            if (rChannel > p.getMaxColorValue())
            {
                rChannel = p.getMaxColorValue();
            }
            if (gChannel > p.getMaxColorValue())
            {
                gChannel = p.getMaxColorValue();
            }
            if (bChannel > p.getMaxColorValue())
            {
                bChannel = p.getMaxColorValue();
            }

            p.setChannel(r, c, 0, rChannel);
            p.setChannel(r, c, 1, gChannel);
            p.setChannel(r, c, 2, bChannel);
        }
    }

    return p;
}

void PPM::grayFromChannel( PPM& dst, const int& src_channel ) const {
    dst.setHeight( this->getHeight() );
    dst.setWidth( this->getWidth() );
    dst.setMaxColorValue( this->getMaxColorValue() );

    for (int r=0; r < dst.getHeight(); r++) {
        // For each row
        for (int c=0; c < dst.getWidth(); c++) {
            // For each column
            int colorValue = this->getChannel( r, c, src_channel );
            for (int ch=0; ch < 3; ch++) {
                // For each channel
                dst.setChannel( r, c, ch, colorValue );
            }
        }
    }
}

void PPM::grayFromRed( PPM& dst ) const {
    grayFromChannel( dst, 0 );
}

void PPM::grayFromGreen( PPM& dst ) const {
    grayFromChannel( dst, 1 );
}

void PPM::grayFromBlue( PPM& dst ) const {
    grayFromChannel( dst, 2 );
}

double PPM::linearColorimetricPixelValue( const int& row, const int& column ) const {
    int red = this->getChannel( row, column, 0 );
    int green = this->getChannel( row, column, 1 );
    int blue = this->getChannel( row, column, 2 );

    return 0.2126*red + 0.7152*green + 0.0722*blue;
}

void PPM::grayFromLinearColorimetric( PPM& dst ) const {
    dst.setHeight( this->getHeight() );
    dst.setWidth( this->getWidth() );
    dst.setMaxColorValue( this->getMaxColorValue() );
    
    for (int r=0; r < dst.getHeight(); r++) {
        // For each row
        for (int c=0; c < dst.getWidth(); c++) {
            // For each column
            for (int ch=0; ch < 3; ch++) {
                // For each channel
                int value = this->linearColorimetricPixelValue( r, c );
                dst.setChannel( r, c, ch, value );
            }
        }
    }
}

PPM& PPM::operator+=( const int& rhs ) {

    for (int r=0; r < this->getHeight(); r++ ) {
        // For each column
        for (int c=0; c < this->getWidth(); c++ ) {
            // For each column
            int red = this->getChannel( r, c, 0 );
            int green = this->getChannel( r, c, 1 );
            int blue = this->getChannel( r, c, 2 );

            red += rhs;
            green += rhs;
            blue += rhs;

            if (red < 0 ) { red = 0; }
            if (red > this->getMaxColorValue() ) { red = this->getMaxColorValue(); }

            if (green < 0 ) { green = 0; }
            if (green > this->getMaxColorValue() ) { green = this->getMaxColorValue(); }

            if (blue < 0 ) { blue = 0; }
            if (blue > this->getMaxColorValue() ) { blue = this->getMaxColorValue(); }

            this->setChannel( r, c, 0, red );
            this->setChannel( r, c, 1, green );
            this->setChannel( r, c, 2, blue );
        }
    }
    return *this;
}

void PPM::sepiaFilter( PPM& dst ) const {
    int height = this->getHeight();
    int width = this->getWidth();
    int max_color_value = this->getMaxColorValue();

    dst.setHeight( height );
    dst.setWidth( width );
    dst.setMaxColorValue( max_color_value );

    for (int r=0; r < height; r++ ) {
        // For each row
        for (int c=0; c < width; c++ ) {
            // For each column
            int red = this->getChannel( r, c, 0 );
            int green = this->getChannel( r, c, 1 );
            int blue = this->getChannel( r, c, 2 );

            red = 0.393*red + 0.769*green + 0.189*blue;
            green = 0.349*red + 0.686*green + 0.168*blue;
            blue = 0.272*red + 0.534*green + 0.131*blue;

            if ( red > max_color_value ) { red = max_color_value; }
            if ( blue > max_color_value ) { blue = max_color_value; }
            if ( green > max_color_value ) { green = max_color_value; }

            dst.setChannel( r, c, 0, red );
            dst.setChannel( r, c, 1, green );
            dst.setChannel( r, c, 2, blue );
        }
    }
}

void PPM::orangeFilter(PPM& dst) const {
    dst.setHeight( this->getHeight() );
    dst.setWidth( this->getWidth() );
    dst.setMaxColorValue( this->getMaxColorValue() );

    int max_color_value = this->getMaxColorValue();

    for (int r=0; r < this->getHeight(); r++ ) {
        // For each row
        for (int c=0; c < this->getWidth(); c++ ) {
            // For each column
            int old_red = this->getChannel( r, c, 0 );
            int old_green = this->getChannel( r, c, 1 );
            int old_blue = this->getChannel( r, c, 2 );

            int red = 2*(2*old_red + old_green) / 3;
            int green = 2*(2*old_red + old_green) / 6;
            int blue = old_blue / 2;

            if ( red > max_color_value ) { red = max_color_value; }
            if ( blue > max_color_value ) { blue = max_color_value; }
            if ( green > max_color_value ) { green = max_color_value; }

            dst.setChannel( r, c, 0, red );
            dst.setChannel( r, c, 1, green );
            dst.setChannel( r, c, 2, blue );
        }
    }
}