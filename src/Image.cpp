#include "image_menu.h"

Image::Image()
    : mHeight(0), mWidth(0), mVector(0) {
}

Image::Image(const int& height, const int& width)
    : mHeight(height), mWidth(width), mVector(height * width) {
}

void Image::setHeight(const int height) {
    if (height >= 0){
        mHeight = height;
        mVector.resize(mHeight * mWidth * 3);
    }
}

void Image::setWidth(const int width) {
    if (width >= 0){
        mWidth = width;
        mVector.resize(mHeight * mWidth * 3);
    }
}

void Image::setChannel( const int& row, const int& column, const int& channel, const int& value ) {
    if (indexValid(row, column, channel)) {
        mVector[index(row, column, channel)] = value;
    }
}

int Image::getHeight() const{
    return mHeight;
}

int Image::getWidth() const{
    return mWidth;
}

int Image::getChannel( const int& row, const int& column, const int& channel ) const{
    if (indexValid(row, column, channel)) {
        return mVector[index(row, column, channel)];
    }
    return -1;
}

bool Image::indexValid( const int& row, const int& column, const int& channel) const{

    if (row >= 0 && row < mHeight) {
        if (column >= 0 && column < mWidth) {
            if (channel >= 0 && channel < 3) {
                return true;
            }
        }
    }
    return false;
}

int Image::index( const int& row, const int& column, const int& channel) const{
    
    if (indexValid(row, column, channel)) {
        return ((mWidth * row * 3) + (3 * column) + (channel));
    }
    return -1;
}