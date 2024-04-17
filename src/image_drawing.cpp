#include "image_menu.h"
#include <cmath>

void diagonalQuadPattern( ActionData& action_data )
{

    int height;
    int width;

    height = getInteger( action_data, "Image height? " );
    width = getInteger( action_data, "Image width? " );

    action_data.getInputImage1().setMaxColorValue(255);
    action_data.getInputImage1().setMaxColorValue(255);

    action_data.getInputImage1().setHeight(height);
    action_data.getInputImage1().setWidth(width);

    // Set top half Red channels to 0
    for (int r = 0; r < action_data.getInputImage1().getHeight() / 2; r++)
    {
        // For each row in top half
        for (int c = 0; c < action_data.getInputImage1().getWidth(); c++)
        {
            // For each column
            action_data.getInputImage1().setChannel(r, c, 0, 0);
        }
    }

    // Set bottom half Red channels to 255
    for (int r = action_data.getInputImage1().getHeight() / 2; r < action_data.getInputImage1().getHeight(); r++)
    {
        // For each row in bottom half
        for (int c = 0; c < action_data.getInputImage1().getWidth(); c++)
        {
            // For each column
            action_data.getInputImage1().setChannel(r, c, 0, 255);
        }
    }

    // Set left half Blue channels to 0
    for (int c = 0; c < action_data.getInputImage1().getWidth() / 2; c++)
    {
        // For each column in left half
        for (int r = 0; r < action_data.getInputImage1().getHeight(); r++)
        {
            // For each row
            action_data.getInputImage1().setChannel(r, c, 2, 0);
        }
    }

    // Set right half Blue channels to 255
    for (int c = action_data.getInputImage1().getWidth() / 2; c < action_data.getInputImage1().getWidth(); c++)
    {
        // For each column in the right half
        for (int r = 0; r < action_data.getInputImage1().getHeight(); r++)
        {
            // For each row
            action_data.getInputImage1().setChannel(r, c, 2, 255);
        }
    }

    // Set green channel for each pixel
    for (int r = 0; r < action_data.getInputImage1().getHeight(); r++)
    {
        // For each row
        for (int c = 0; c < action_data.getInputImage1().getWidth(); c++)
        {
            // For each column
            int value = (2 * r + 2 * c) % 256;
            action_data.getInputImage1().setChannel(r, c, 1, value);
        }
    }
}

void stripedDiagonalPattern( ActionData& action_data )
{
    int height;
    int width;
    int max_color_value;

    height = getInteger( action_data, "Image height? ");
    width = getInteger( action_data, "Image width? ");
    max_color_value = (height + width) / 3;
    if (max_color_value > 255)
    {
        max_color_value = 255;
    }

    action_data.getInputImage1().setHeight(height);
    action_data.getInputImage1().setWidth(width);
    action_data.getInputImage1().setMaxColorValue(max_color_value);

    // Set top half Red channels to 0
    for (int r = 0; r < action_data.getInputImage1().getHeight() / 2; r++)
    {
        // For each row in top half
        for (int c = 0; c < action_data.getInputImage1().getWidth(); c++)
        {
            // For each column
            action_data.getInputImage1().setChannel(r, c, 0, 0);
        }
    }

    // Set every third bottom half Red channels to 0
    for (int r = action_data.getInputImage1().getHeight() / 2; r < action_data.getInputImage1().getHeight(); r++)
    {
        // For each row in bottom half
        if (r % 3 == 0)
        {
            // If it is a multiple of 3
            for (int c = 0; c < action_data.getInputImage1().getWidth(); c++)
            {
                // For each channel
                action_data.getInputImage1().setChannel(r, c, 0, 0);
            }
        }
        else
        {
            // If it is NOT a multiple of 3
            for (int c = 0; c < action_data.getInputImage1().getWidth(); c++)
            {
                // For each channel
                action_data.getInputImage1().setChannel(r, c, 0, action_data.getInputImage1().getMaxColorValue());
            }
        }
    }

    // Set the green channels
    for (int r = 0; r < action_data.getInputImage1().getHeight(); r++){
        // For each row
        for (int c=0; c < action_data.getInputImage1().getWidth(); c++) {
            // For each column
            float greenValue = (r + action_data.getInputImage1().getWidth() - c - 1) % (action_data.getInputImage1().getMaxColorValue() + 1);
            action_data.getInputImage1().setChannel(r, c, 1, greenValue);
        }
    }

    // Sets the blue channel
    for (int r = 0; r < action_data.getInputImage1().getHeight(); r++){
        // For each row
        for (int c=0; c < action_data.getInputImage1().getWidth(); c++) {
            // For each column
            if (c < r) {
                action_data.getInputImage1().setChannel(r, c, 2, 0);
            }
            else {
                action_data.getInputImage1().setChannel(r, c, 2, action_data.getInputImage1().getMaxColorValue());
            }
        }
    }
}

void fourSquarePattern( ActionData& action_data ) {
    int imageSize;

    imageSize = getInteger( action_data , "Image size? ");
    action_data.getInputImage1().setHeight(imageSize);
    action_data.getInputImage1().setWidth(imageSize);
    action_data.getInputImage1().setMaxColorValue(100);

    // Set pixels in top left corner
    for (int r=0; r < action_data.getInputImage1().getHeight() / 2; r++) {
        // For each row in top half
        for (int c = 0; c < action_data.getInputImage1().getWidth() / 2; c++) {
            // For each column in left half
            action_data.getInputImage1().setChannel(r, c, 0, 100);
            action_data.getInputImage1().setChannel(r, c, 1, 0);
            action_data.getInputImage1().setChannel(r, c, 2, 66);
        }
    }

    // Set pixels in top right corner
    for (int r=0; r < action_data.getInputImage1().getHeight() / 2; r++) {
        // For each row in top half
        for (int c = action_data.getInputImage1().getWidth() / 2; c < action_data.getInputImage1().getWidth(); c++) {
            // For each column in right half
            action_data.getInputImage1().setChannel(r, c, 0, 0);
            action_data.getInputImage1().setChannel(r, c, 1, 100);
            action_data.getInputImage1().setChannel(r, c, 2, 33);
        }
    }

    // Set pixels in bottom left corner
    for (int r=action_data.getInputImage1().getHeight() / 2; r < action_data.getInputImage1().getHeight(); r++) {
        // For each row in bottom half
        for (int c = 0; c < action_data.getInputImage1().getWidth() / 2; c++) {
            // For each column in left half
            action_data.getInputImage1().setChannel(r, c, 0, 66);
            action_data.getInputImage1().setChannel(r, c, 1, 33);
            action_data.getInputImage1().setChannel(r, c, 2, 100);
        }
    }

    // Set pixels in bottom right corner
    for (int r=action_data.getInputImage1().getHeight() / 2; r < action_data.getInputImage1().getHeight(); r++) {
        // For each row in top half
        for (int c = action_data.getInputImage1().getWidth() / 2; c < action_data.getInputImage1().getWidth(); c++) {
            // For each column in right half
            action_data.getInputImage1().setChannel(r, c, 0, 33);
            action_data.getInputImage1().setChannel(r, c, 1, 66);
            action_data.getInputImage1().setChannel(r, c, 2, 0);
        }
    }
}

void flagRomaniaPattern( ActionData& action_data ) {

    int height;
    int thirdWidth;
    height = getInteger( action_data, "Image height? ");


    action_data.getInputImage1().setHeight(height);
    action_data.getInputImage1().setWidth(height * 1.5);
    action_data.getInputImage1().setMaxColorValue(255);
    thirdWidth = action_data.getInputImage1().getWidth() / 3;



    // Set first third to blue
    for (int r=0; r < action_data.getInputImage1().getHeight(); r++) {
        // For each row in first third
        for (int c=0; c < thirdWidth; c++) {
            // For each column
            action_data.getInputImage1().setChannel(r, c, 0, 0);
            action_data.getInputImage1().setChannel(r, c, 1, 43);
            action_data.getInputImage1().setChannel(r, c, 2, 127);
        }
    } 

    // Set second third to yellow
    for (int r=0; r < action_data.getInputImage1().getHeight(); r++) {
        // For each row in second third
        for (int c=thirdWidth; c < thirdWidth * 2; c++) {
            // For each column
            action_data.getInputImage1().setChannel(r, c, 0, 252);
            action_data.getInputImage1().setChannel(r, c, 1, 209);
            action_data.getInputImage1().setChannel(r, c, 2, 22);
        }
    }

    // Set third third to red
    for (int r=0; r < action_data.getInputImage1().getHeight(); r++) {
        // For each row in third third
        for (int c=thirdWidth * 2; c < thirdWidth * 3; c++) {
            // For each column
            action_data.getInputImage1().setChannel(r, c, 0, 206);
            action_data.getInputImage1().setChannel(r, c, 1, 17);
            action_data.getInputImage1().setChannel(r, c, 2, 38);
        }
    }
}

void setSize( ActionData& action_data ) {

    int height = getInteger( action_data, "Height? ");
    int width = getInteger( action_data, "Width? ");

    PPM p = action_data.getInputImage1();

    action_data.getInputImage1().setHeight(height);
    action_data.getInputImage1().setWidth(width);
}

void setMaxColorValue( ActionData& action_data ) {
    int maxColorValue = getInteger( action_data, "Max color value? ");

    action_data.getInputImage1().setMaxColorValue(maxColorValue);
}

void setChannel( ActionData& action_data ) {
    int r = getInteger( action_data, "Row? ");
    int c = getInteger( action_data, "Column? ");
    int ch = getInteger( action_data, "Channel? ");
    int v = getInteger( action_data, "Value? ");

    action_data.getInputImage1().setChannel( r, c, ch, v );
}

void setPixel( ActionData& action_data ) {
    int r = getInteger( action_data, "Row? ");
    int c = getInteger( action_data, "Column? ");
    int red = getInteger( action_data, "Red? ");
    int green = getInteger( action_data, "Green? ");
    int blue = getInteger( action_data, "Blue? ");

    action_data.getInputImage1().setPixel( r, c, red, green, blue );
}

void clearAll( ActionData& action_data ) {
    PPM p = action_data.getInputImage1();

    for (int r=0; r < action_data.getInputImage1().getHeight(); r++) {
        // For each row
        for (int c=0; c < action_data.getInputImage1().getWidth(); c++) {
            // For each column
            action_data.getInputImage1().setPixel( r, c, 0, 0, 0);
        }
    }
}

void drawCircle(ActionData& action_data) {
    int centerRow = getInteger( action_data, "Center Row? " );
    int centerColumn = getInteger( action_data, "Center Column? " );
    int radius = getInteger( action_data, "Radius? " );
    int red = getInteger( action_data, "Red? " );
    int green = getInteger( action_data, "Green? " );
    int blue = getInteger( action_data, "Blue? " );

    int numRows = action_data.getInputImage1().getHeight();
    int numCols = action_data.getInputImage1().getWidth();

    for (int r=0; r < numRows; r++) {
        for (int c=0; c < numCols; c++) {
            // For each pixel
            int side1 = (centerRow - r) * (centerRow -r);
            int side2 = (centerColumn - c) * (centerColumn - c);
            double distance = std::sqrt( side1 + side2 );

            if (distance <= radius) {
                action_data.getInputImage1().setChannel( r, c, 0, red );
                action_data.getInputImage1().setChannel( r, c, 1, green );
                action_data.getInputImage1().setChannel( r, c, 2, blue );
            }
        }
    }
}

void drawBox(ActionData& action_data) {
    int topRow = getInteger( action_data, "Top Row? " );
    int leftColumn = getInteger( action_data, "Left Column? " );
    int bottomRow = getInteger( action_data, "Bottom Row? " );
    int rightColumn = getInteger( action_data, "Right Column? " );
    int red = getInteger( action_data, "Red? " );
    int green = getInteger( action_data, "Green? " );
    int blue = getInteger( action_data, "Blue? " );

    for (int r=topRow; r < bottomRow+1; r++) {
        for (int c=leftColumn; c < rightColumn+1; c++) {
            action_data.getInputImage1().setChannel( r, c, 0, red );
            action_data.getInputImage1().setChannel( r, c, 1, green );
            action_data.getInputImage1().setChannel( r, c, 2, blue );
        }
    }
}

void drawTestColorPattern(ActionData& action_data) {
    int height = getInteger( action_data, "Height? " );
    int width = getInteger( action_data, "Width? " );
    int max_color_value = getInteger( action_data, "Max color value? " );

    action_data.getInputImage1().setHeight( height );
    action_data.getInputImage1().setWidth( width );
    action_data.getInputImage1().setMaxColorValue( max_color_value );

    for ( int r=0; r < height / 2; r++ ) {
        // For each row in top half
        for (int c=0; c < width / 2; c++ ) {
            // For each column in left half
            action_data.getInputImage1().setPixel( r, c, max_color_value, 0, 0 );
        }
    }

    for ( int r=0; r < height / 2; r++ ) {
        // For each row in top half
        for (int c= width / 2; c < width; c++ ) {
            // For each column in right half
            action_data.getInputImage1().setPixel( r, c, 0, max_color_value, 0 );
        }
    }

    for ( int r= height / 2; r < height; r++ ) {
        // For each row in bottom half
        for (int c=0; c < width / 2; c++ ) {
            // For each column in left half
            action_data.getInputImage1().setPixel( r, c, 0, 0, max_color_value );
        }
    }

    for ( int r= height / 2; r < height; r++ ) {
        // For each row in bottom half
        for (int c= width / 2; c < width; c++ ) {
            // For each column in right half
            action_data.getInputImage1().setPixel( r, c, max_color_value / 2, max_color_value / 2, max_color_value / 2 );
        }
    }
}

void drawSquare(ActionData& action_data) {
    int row = getInteger( action_data, "Row? ");
    int column = getInteger( action_data, "Column? ");
    int size = getInteger( action_data, "Size? ");
    int red = getInteger( action_data, "Red? ");
    int green = getInteger( action_data, "Green? ");
    int blue = getInteger( action_data, "Blue? ");

    for (int r=row - size / 2; r < row + size / 2; r++) {
        for (int c = column - size / 2; c < column + size / 2; c++) {
            action_data.getInputImage1().setPixel( r, c, red, green, blue );
        }
    }

}

void configureGrid(ActionData& action_data) {
    int height = getInteger( action_data, "Grid Height? " );
    int width = getInteger( action_data, "Grid Width? " );
    int maxValue = getInteger( action_data, "Grid Max Value? " );

    action_data.getGrid().setGridSize( height, width );
    action_data.getGrid().setMaxNumber( maxValue );
}

void setGrid(ActionData& action_data) {
    int row = getInteger( action_data, "Grid Row? " );
    int column = getInteger( action_data, "Grid Column? " );
    int value = getInteger( action_data, "Grid Value? " );

    action_data.getGrid().setNumber( row, column, value );
}

void applyGrid(ActionData& action_data) {
    action_data.getGrid().setPPM( action_data.getOutputImage() );
}

void setColorTableSize(ActionData& action_data) {
    int size = getInteger( action_data, "Size? " );
    action_data.getTable().setNumberOfColors( size );
}

void setColor(ActionData& action_data) {
    int pos = getInteger( action_data, "Position? " );
    int red = getInteger( action_data, "Red? " );
    int green = getInteger( action_data, "Green? " );
    int blue = getInteger( action_data, "Blue? " );

    action_data.getTable()[pos].setRed( red );
    action_data.getTable()[pos].setGreen( green );
    action_data.getTable()[pos].setBlue( blue );
}

void setRandomColor(ActionData& action_data) {
    int pos = getInteger( action_data, "Position? " );
    action_data.getTable().setRandomColor( 255, pos );
}

void setColorGradient(ActionData& action_data) {
    int first_position = getInteger( action_data, "First position? " );
    int first_red = getInteger( action_data, "First red? " );
    int first_green = getInteger( action_data, "First green? " );
    int first_blue = getInteger( action_data, "First blue? " );

    int second_position = getInteger( action_data, "Second position? " );
    int second_red = getInteger( action_data, "Second red? " );
    int second_green = getInteger( action_data, "Second green? " );
    int second_blue = getInteger( action_data, "Second blue? " );

    Color c1( first_red, first_green, first_blue );
    Color c2( second_red, second_green, second_blue );
    action_data.getTable().insertGradient( c1, c2, first_position, second_position );
}

void applyGridColorTable(ActionData& action_data) {
    action_data.getGrid().setPPM( action_data.getOutputImage(), action_data.getTable() );
}

void setFractalPlaneSize(ActionData& action_data) {

    NumberGrid *grid = &action_data.getGrid();
    ComplexFractal *fractal = dynamic_cast<ComplexFractal *>(grid);

    if (fractal != 0) {
        double min_x = getDouble( action_data, "Min X? " );
        double max_x = getDouble( action_data, "Max X? " );

        double min_y = getDouble( action_data, "Min Y? " );
        double max_y = getDouble( action_data, "Max Y? " );

        fractal->setPlaneSize( min_x, max_x, min_y, max_y );
    } else {
        action_data.getOS() << "Not a ComplexFractal object. Can't set plane size." << std::endl;
    }
    
}

void calculateFractal(ActionData& action_data) {
    action_data.getGrid().calculateAllNumbers();
}

void setJuliaParameters(ActionData& action_data) {

    NumberGrid *grid = &action_data.getGrid();
    JuliaSet *julia = dynamic_cast<JuliaSet *>(grid);

    if ( julia != 0 ) {
        double a = getDouble( action_data, "Parameter a? ");
        double b = getDouble( action_data, "Parameter b? ");

        julia->setParameters( a, b );
    } else {action_data.getOS() << "Not a JuliaSet object. Can't set parameters." << std::endl;
    }
}

void setInvertedColorGradient(ActionData& action_data) {
    int first_pos = getInteger( action_data, "First Position? " );
    int red = getInteger( action_data, "First red? " );
    int green = getInteger( action_data, "First green? " );
    int blue = getInteger( action_data, "First blue? " );
    int second_pos = getInteger( action_data, "Second Position? " );

    Color color1;
    color1.setRed(red);
    color1.setGreen(green);
    color1.setBlue(blue);

    action_data.getTable().insertInvertedGradient( color1, first_pos, second_pos );
}

void zoomPlane(ActionData& action_data) {
    NumberGrid *grid = &action_data.getGrid();
    ComplexFractal *fractal = dynamic_cast<ComplexFractal *>(grid);

    if (fractal != 0) {
        double zoom_factor = getDouble( action_data, "Zoom factor? " );
        fractal->zoomPlane( zoom_factor );
    } else {
        action_data.getOS() << "Not a ComplexFractal object. Can't zoom plane." << std::endl;
    }
}

void setEasyRandomColorGradient(ActionData& action_data) {
    int first_position = getInteger( action_data, "First position? ");
    int second_position = getInteger( action_data, "Second position? ");

    action_data.getTable().insertEasyRandomGradient( first_position, second_position );
}

void calculateFractalSingleThread(ActionData& action_data) {
    action_data.getGrid().NumberGrid::calculateAllNumbers();
}

void setHueSaturationValueGradient(ActionData& action_data) {
    int first_position = getInteger( action_data, "First position? ");
    double first_hue = getDouble( action_data, "First hue? ");
    double first_saturation = getDouble( action_data, "First saturation? ");
    double first_value = getDouble( action_data, "First value? ");

    int second_position = getInteger( action_data, "Second position? ");
    double second_hue = getDouble( action_data, "Second hue? ");
    double second_saturation = getDouble( action_data, "Second saturation? ");
    double second_value = getDouble( action_data, "Second value? ");

    Color color1, color2;
    color1.setFromHSV( first_hue, first_saturation, first_value );
    color2.setFromHSV( second_hue, second_saturation, second_value );

    action_data.getTable().insertHueSaturationValueGradient( color1, color2, first_position, second_position );
}