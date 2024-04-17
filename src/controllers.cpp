#include "image_menu.h"

int assignment1(std::istream& is, std::ostream& os) {
  ActionData action_data( is, os );
  return askQuestions3( action_data );
}

int assignment2( std::istream& is, std::ostream& os ) {
  ActionData action_data( is, os );
  diagonalQuadPattern( action_data );
  copyImage( action_data );
  drawAsciiImage( action_data );

  return 0;
}

int assignment3( std::istream& is, std::ostream& os ) {
  ActionData action_data( is, os );
  stripedDiagonalPattern( action_data );
  copyImage( action_data );
  writeUserImage( action_data );

  return 0;
}

int four_square( std::istream& is, std::ostream& os ) {
  ActionData action_data( is, os );
  fourSquarePattern( action_data );
  copyImage( action_data );
  writeUserImage( action_data );

  return 0;
}

int flag_romania( std::istream& is, std::ostream& os ) {
  ActionData action_data( is, os );
  flagRomaniaPattern( action_data );
  copyImage( action_data );
  writeUserImage( action_data);

  return 0;
}

void showMenu( MenuData& menu_data, ActionData& action_data ) {

  std::vector<std::string> commandList = menu_data.getNames();
  for (unsigned int i=0; i < commandList.size(); i++) {
    // For each command in menu_data
    std::string commandName = commandList[i];
    std::string commandDescription = menu_data.getDescription( commandName);
    action_data.getOS() << commandName << ") " << commandDescription << std::endl;
  }
}

void takeAction( const std::string& choice, MenuData& menu_data, ActionData& action_data ) {
  ActionFunctionType func = menu_data.getFunction( choice );
  if (func != 0) 
  {
    func( action_data );
  }
  else if ( choice == "menu" )
  {
    showMenu( menu_data, action_data );
  }
  else 
  {
    action_data.getOS() << "Unknown action " << "'" << choice << "'." << std::endl;
  }
}

void configureMenu( MenuData& menu_data ) {
  menu_data.addAction( "draw-ascii", drawAsciiImage, "Write output image to terminal as ASCII art.");
  menu_data.addAction( "write", writeUserImage, "Write output image to file.");
  menu_data.addAction( "copy", copyImage, "Copy input image 1 to output image.");
  menu_data.addAction( "read1", readUserImage1, "Read file into input image 1.");
  menu_data.addAction( "read2", readUserImage2, "Read file into input image 2.");
  menu_data.addAction( "+", plus, "Set output image from sum of input image 1 and input image 2.");
  menu_data.addAction( "+=", plusEquals, "Set input image 1 by adding in input image 2." );
  menu_data.addAction( "-", minus, "Set output image from difference of input image 1 and input image 2." );
  menu_data.addAction( "-=", minusEquals, "Set input image 1 by subtracting input image 2.");
  menu_data.addAction( "*", times, "Set output image from input image 1 multiplied by a number." );
  menu_data.addAction( "*=", timesEquals, "Set input image 1 by multiplying by a number." );
  menu_data.addAction( "/", divide, "Set output image from input image 1 divided by a number." );
  menu_data.addAction( "/=", divideEquals, "Set input image 1 by dividing by a number." );
  menu_data.addAction( "#", commentLine, "Comment to end of line.");
  menu_data.addAction( "size", setSize, "Set the size of input image 1.");
  menu_data.addAction( "max-color-value", setMaxColorValue, "Set the max color value of input image 1.");
  menu_data.addAction( "channel", setChannel, "Set a channel value in input image 1.");
  menu_data.addAction( "pixel", setPixel, "Set a pixel's 3 values in input image 1.");
  menu_data.addAction( "clear", clearAll, "Set all pixels to 0,0,0 in input image 1.");
  menu_data.addAction( "red-gray", grayFromRed, "Set output image by grayscale from red on input image 1.");
  menu_data.addAction( "green-gray", grayFromGreen, "Set output image by grayscale from green on input image 1.");
  menu_data.addAction( "blue-gray", grayFromBlue, "Set output image by grayscale from blue on input image 1.");
  menu_data.addAction( "linear-gray", grayFromLinearColorimetric, "Set output image by linear colorimetric grayscale on input image 1.");
  menu_data.addAction( "circle", drawCircle, "Draw a circle shape in input image 1.");
  menu_data.addAction( "box", drawBox, "Draw a box shape in input image 1." );
  menu_data.addAction( "test-pattern", drawTestColorPattern, "Draw a test pattern in input image 1." );
  menu_data.addAction( "diagonal-quad", diagonalQuadPattern, "Draw a diagonal quad pattern in input image 1." );
  menu_data.addAction( "striped-diagonal", stripedDiagonalPattern, "Draw a striped diagonal pattern in input image 1." );
  menu_data.addAction( "+=-int", plusEqualsInt, "Set input image 1 by adding by an integer." );
  menu_data.addAction( "sepia", sepiaFilter, "Set output image from sepia filter on input image 1." );
  menu_data.addAction( "square", drawSquare, "Draw a square shape in input image 1." );
  menu_data.addAction( "orange", orangeFilter, "Set output image from orange filter on input image 1." );
  menu_data.addAction( "grid", configureGrid, "Configure the grid." );
  menu_data.addAction( "grid-set", setGrid, "Set a single value in the grid." );
  menu_data.addAction( "grid-apply", applyGrid, "Use the grid values to set colors in the output image." );
  menu_data.addAction( "set-color-table-size", setColorTableSize, "Change the number of slots in the color table.");
  menu_data.addAction( "set-color", setColor, "Set the RGB values for one slot in the color table.");
  menu_data.addAction( "set-random-color", setRandomColor, "Randomly set the RGB values for one slot in the color table.");
  menu_data.addAction( "set-color-gradient", setColorGradient, "Smoothly set the RGB values for a range of slots in the color table.");
  menu_data.addAction( "grid-apply-color-table", applyGridColorTable, "Use the grid values to set colors in the output image using the color table.");
  menu_data.addAction( "fractal-plane-size",  setFractalPlaneSize, "Set the dimensions of the grid in the complex plane." );
  menu_data.addAction( "julia-parameters", setJuliaParameters, "Set the parameters of the Julia Set function." );
  menu_data.addAction( "complex-fractal", setComplexFractal, "Choose to make a complex plane." );
  menu_data.addAction( "julia", setJuliaFractal, "Choose to make a Julia set." );
  menu_data.addAction( "mandelbrot", setMandelbrotFractal, "Choose to make a Mandelbrot set." );
  menu_data.addAction( "set-inverted-color-gradient", setInvertedColorGradient, "Smoothly set the values for a range of slots in the color table, using a color and its inverse." );
  menu_data.addAction( "fractal-zoom", zoomPlane, "Zoom in or out of the complex plane." );
  menu_data.addAction( "set-easy-random-color-gradient", setEasyRandomColorGradient, "Smoothly set the values for a range of slots in the color table, using two random colors." );
  menu_data.addAction( "julia-four", setJuliaFourFractal, "Choose to make a Julia set with the fourth power function." );
  menu_data.addAction( "fractal-calculate", calculateFractal, "Calculate the escape values for the fractal." );
  menu_data.addAction( "fractal-calculate-single-thread", calculateFractalSingleThread, "Calculate the escape values for the fractal, single-thread." );
  menu_data.addAction( "set-hsv-gradient", setHueSaturationValueGradient, "Smoothly set colors for a range of slots in the color table, based on change of hue, saturation, and value." );
  menu_data.addAction( "quit", quit, "Quit.");
}

int imageMenu( std::istream& is, std::ostream& os ) {
  ActionData action_data( is, os );
  ComplexFractal *fractal = new ComplexFractal;
  action_data.setGrid( fractal );
  MenuData menu_data;

  configureMenu( menu_data );

  while (!action_data.getDone() && action_data.getIS().good()) {
    // While the action_data is not done and there are no errors from input stream
    std::string choice = getChoice( action_data );
    takeAction( choice, menu_data, action_data );
  }

  return 0;
}

void setComplexFractal( ActionData& action_data ) {
  NumberGrid *p = new ComplexFractal;
  action_data.setGrid( p );
}

void setJuliaFractal( ActionData& action_data ) {
  NumberGrid *p = new JuliaSet;
  action_data.setGrid( p );
}

void setMandelbrotFractal( ActionData& action_data ) {
  NumberGrid *p = new MandelbrotSet;
  action_data.setGrid( p );
}

void setJuliaFourFractal(ActionData& action_data) {
    NumberGrid *p = new JuliaSetFour;
    action_data.setGrid( p );
}

// Text for an awesome Julia Set
/*
# ###########################################
# Make a first image
# ###########################################
# ###########################################
# Fill the color table
# ###########################################
set-color-table-size 202
set-color 200 0 99 99
set-color 201 0 0 0
set-color-gradient   0 0 198 198   19 255 170 0
set-color-gradient  20 255 170 0   39 0 198 198
set-color-gradient  40 0 198 198   59 255 170 0
set-color-gradient  60 255 170 0   89 255 116 0
set-color-gradient  90 255 116 0  119 14 73 208
set-color-gradient 120 14 73 208  199  0  0   0

# Choose JuliaSetFour, and configure it
#julia-four
julia-parameters 0.34 0.73

# Configure the grid
grid 1000 1000 200

# Configure the fractal plane
fractal-plane-size -1.05 -0.495 0.15 0.75

# Calculate the escape values
fractal-calculate

# Apply grid values to the output PPM
grid-apply-color-table

# Save the image to file
write exam-julia-power-four-a.ppm

# ###########################################
# Done
# ###########################################

# Quit
quit
*/

// Text for another awesome Julia Set
/*
set-color-table-size 202
set-color 200 0 99 99
set-color 201 0 0 0
set-color-gradient   0 0 198 198   19 255 170 0
set-color-gradient  20 255 170 0   39 0 198 198
set-color-gradient  40 0 198 198   59 255 170 0
set-color-gradient  60 255 170 0   89 255 116 0
set-color-gradient  90 255 116 0  119 14 73 208
set-color-gradient 120 14 73 208  199  0  0   0

julia-four
julia-parameters -0.15 0.64

grid 1000 1000 200

fractal-plane-size -0.3 0.3 0.3 0.9

fractal-calculate

grid-apply-color-table

write exam-julia-power-four-b.ppm

quit
*/