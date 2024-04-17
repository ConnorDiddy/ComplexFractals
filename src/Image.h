#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <string>
#include <vector>

class Image {
public:
    Image();
    Image(const int& height, const int& width);
    void setHeight(const int height);
    void setWidth(const int width);
    void setChannel( const int& row, const int& column, const int& channel, const int& value );
    int getHeight()const;
    int getWidth() const;
    int getChannel( const int& row, const int& column, const int& channel ) const;
    bool indexValid( const int& row, const int& column, const int& channel ) const;
    int index( const int& row, const int& column, const int& channel ) const;

private:
    int mHeight;
    int mWidth;
    int mChannel;
    std::vector<int> mVector;
};

#endif