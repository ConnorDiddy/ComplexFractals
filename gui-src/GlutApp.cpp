#include "GlutApp.h"
#include "glut_app.h"
#include "AppData.h"
#include "../src/ColorTable.h"
#include "image_menu.h"

GlutApp::GlutApp(int height, int width)
  : mData(height, width) {
    //setSize(height, width);
    //mData.setSize(height, width);
    //glutPostRedisplay();
    //mData.createJulia1();
}

void GlutApp::setSize(int height, int width) {
  mData.setSize(height, width);
  
  mData.createFractal();
  //displayOutputImage();
}

int GlutApp::getHeight() const {
  return mData.getHeight();
}
int GlutApp::getWidth() const {
  return mData.getWidth();
}

void GlutApp::display() {

 if (mData.getInteractionMode() == 0 ) {
  displayOutputImage();
 } else if (mData.getInteractionMode() == 1 ) {
  displayColorTable();
 } else if (mData.getInteractionMode() == 2) {
  displayColorTable();
 } else if (mData.getInteractionMode() == 3) {
  displayColorTable();
 } else if (mData.getInteractionMode() == 4) {
  displayColorTable();
 }

}

void GlutApp::displayOutputImage() {
  PPM &p = mData.getOutputImage();
  double max = static_cast<double>(p.getMaxColorValue());
  double r, g, b;
  int row, column;
  glBegin( GL_POINTS );
  
  for (row=0; row < p.getHeight(); row++) {
    for (column=0; column <= p.getWidth(); column++) {
      r = p.getChannel( row, column, 0) / max;
      g = p.getChannel(row, column, 1) / max;
      b = p.getChannel(row, column, 2) / max;
      glColor3d(r, g, b);
      glVertex2i(column, p.getHeight()-row-1);
    }
  }
  glEnd();
}

void GlutApp::displayColorTable() {

  int r, c;
  int table_size = mData.getColorTable().getNumberOfColors();

  glBegin( GL_POINTS );
  for (r=0; r < getHeight(); r++)
    for (c=0; c <= getWidth(); c++) {
      // For each pixel in display
      int i = c * table_size / getWidth();
      Color color = mData.getColorTable()[i];
      double red = color.getRed() / 255.0;
      double green = color.getGreen() / 255.0;
      double blue = color.getBlue() / 255.0;
      glColor3d(red, green, blue);
      glVertex2i(c, r);
    }
  glEnd();
}

bool GlutApp::keyboard(unsigned char c) {
  AppData::InteractionMode interaction_mode = mData.getInteractionMode();
  AppData::FractalMode fractal_mode = mData.getFractalMode();

  bool post_redisplay = true;

  switch (c) {
    case 'J':
      mData.createJulia1();
      break;

    case 'j':
      mData.createJulia2();
      break;

    case 'M':
      mData.createMandelbrot1();
      break;
    
    case 'm':
      mData.createMandelbrot2();
      break;

    case 'C':
      mData.createComplexFractal1();
      break;

    case 'c':
      mData.createComplexFractal2();
      break;

    case 'T':
      interaction_mode = AppData::InteractionMode::IM_COLORTABLE;
      mData.setInteractionMode(interaction_mode);
      break;

    case 't':
      interaction_mode = AppData::InteractionMode::IM_FRACTAL;
      mData.setInteractionMode(interaction_mode);
      break;

    case 'b':
      fractal_mode = AppData::FractalMode::M_MANDELBROT;
      mData.setFractalMode(fractal_mode);
      mData.createFractal();
      break;

    case 'n':
      fractal_mode = AppData::FractalMode::M_JULIA;
      mData.setFractalMode(fractal_mode);
      mData.createFractal();
      break;

    case 'F':
      fractal_mode = AppData::FractalMode::M_COMPLEX;
      mData.setFractalMode(fractal_mode);
      mData.createFractal();
      break;

    case '>':
      mData.increaseColorTableSize();
      break;

    case '.':
      mData.increaseColorTableSize();
      break;

    case '<':
      mData.decreaseColorTableSize();
      break;

    case ',':
      mData.decreaseColorTableSize();
      break;

    case 'r':
      if (interaction_mode == AppData::InteractionMode::IM_COLORTABLE) {
        mData.randomColor1();
        break;
      }
      post_redisplay = false;
      break;

    case 'R':
      if (interaction_mode == AppData::InteractionMode::IM_COLORTABLE) {      
        mData.randomColor2();
        break;
      } else if (interaction_mode == AppData::InteractionMode::IM_FRACTAL) {
        mData.resetPlane();
        mData.createFractal();
        break;
      }
      post_redisplay = false;
      break;
    
    case 'z':
      mData.zoomIn();
      mData.createFractal();
      break;

    case 'Z':
      mData.zoomOut();
      mData.createFractal();
      break;

    case '+':
      mData.increaseMaxNumber();
      mData.createFractal();
      break;

    case '=':
      mData.increaseMaxNumber();
      mData.createFractal();
      break;

    case '-':
      mData.decreaseMaxNumber();
      mData.createFractal();
      break;

    case '_':
      mData.decreaseMaxNumber();
      mData.createFractal();
      break;

    case '0':
      mData.nextColorTableMode();
      break;

    case '1':
      mData.setInteractionMode(AppData::IM_COLOR1);
      break;

    case '2':
      mData.setInteractionMode(AppData::IM_COLOR2);
      break;

    case 'Y':
      mData.increaseRed();
      break;

    case 'y':
      mData.decreaseRed();
      break;

    case 'U':
      mData.increaseGreen();
      break;

    case 'u':
      mData.decreaseGreen();
      break;

    case 'I':
      mData.increaseBlue();
      break;

    case 'i':
      mData.decreaseBlue();
      break;

    case 'e':
      if (mData.getInteractionMode() == AppData::IM_COLORTABLE) {
        mData.randomColor3();
      }
      break;

    case '3':
      mData.setInteractionMode(AppData::IM_COLOR3);
      break;

    case 'h':
      mData.toggleHSVColor();
      break;

    default:
      post_redisplay = false;
      break;
  }
  return post_redisplay;
}

bool GlutApp::special(unsigned char c) {

  bool post_redisplay = true;

  switch (c) {
    case GLUT_KEY_LEFT:
      mData.moveLeft();
      mData.createFractal();
      break;
    
    case GLUT_KEY_DOWN:
      mData.moveDown();
      mData.createFractal();
      break;

    case GLUT_KEY_RIGHT:
      mData.moveRight();
      mData.createFractal();
      break;

    case GLUT_KEY_UP:
      mData.moveUp();
      mData.createFractal();
      break;

    default:
      post_redisplay = false;
      break;
  }

  return post_redisplay;
}

bool GlutApp::mouse(int mouse_button, int state, int x, int y) {

  AppData::InteractionMode interaction_mode = mData.getInteractionMode();
  AppData::FractalMode fractal_mode = mData.getFractalMode();

  if (fractal_mode != AppData::FractalMode::M_MANDELBROT || interaction_mode != AppData::InteractionMode::IM_FRACTAL) {
    return false;
  }

  if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    mData.setAB(x, y);
    mData.setFractalMode(AppData::FractalMode::M_JULIA);
    mData.createFractal();
  }

  return true;
}