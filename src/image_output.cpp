#include "image_menu.h"
#include <fstream>

void drawAsciiImage( ActionData& action_data ) {

    PPM image = action_data.getOutputImage();
    image.setMaxColorValue(255);

    for (int r=0; r < image.getHeight(); r++) {
        // For each row
        std::string row = "";
        for (int c=0; c < image.getWidth(); c++) {
            // For each column
            double strength = 0;
            for (int ch=0; ch < 3; ch++) {
                // For each channel
                int channel = image.getChannel(r, c, ch);
                strength += channel;
            }
            strength = (strength / 765.0);
            // Turn strength into ASCII character
            if (strength < 0.1) {
                row += " ";
            } else if (strength < 0.2) {
                row += ".";
            } else if (strength < 0.3) {
                row += "-";
            } else if (strength < 0.4) {
                row += "~";
            } else if (strength < 0.5) {
                row += ";";
            } else if (strength < 0.6) {
                row += "+";
            } else if (strength < 0.7) {
                row += "|";
            } else if (strength < 0.8) {
                row += "*";
            } else if (strength < 0.9) {
                row += "%";
            } else if (strength < 1.0){
                row += "#";
            } else if (strength == 1.0) {
                row += "@";
            }
        }
        action_data.getOS() << row << "\n";
    }
}

void writeUserImage ( ActionData& action_data ) {
    std::string fileName;
    std::ofstream myfile;
    PPM p = action_data.getOutputImage();
     
    fileName = getString( action_data, "Output filename? ");
    myfile.open (fileName);
    p.writeStream( myfile );
    myfile.close();
}

void copyImage( ActionData& action_data ) {
    action_data.getOutputImage() = action_data.getInputImage1();
}

void readUserImage1( ActionData& action_data ) {
    std::string inputFileName = getString( action_data, "Input filename? " );
    
    std::ifstream myfile (inputFileName);
    if (myfile.is_open()) 
    {
        action_data.getInputImage1().readStream( myfile );
    }
    else 
    {
        std::cout << inputFileName << "could not be opened." << std::endl;
    }
}

void readUserImage2( ActionData& action_data ) {
    std::string inputFileName = getString( action_data, "Input filename? " );
    
    std::ifstream myfile (inputFileName);
    if (myfile.is_open()) 
    {
        action_data.getInputImage2().readStream( myfile );
    }
    else 
    {
        std::cout << inputFileName << "could not be opened." << std::endl;
    }
}