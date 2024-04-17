#include "AppData.h"
#include "../src/image_menu.h"

AppData::AppData(int height, int width)
    : mHeight( height ), mWidth( width ), mMaxNumber(400), \
    mInteractionMode(IM_FRACTAL), mFractalMode(M_JULIA), \
    mNumColor(50), 
    mColor1(Color(0, 120, 120)), mColor2(Color(120, 0, 120)), \
    mColor3(Color(60, 60, 210)),
    mMinX(-2), mMaxX(2), \
    mMinY(-2), mMaxY(2), mA(-0.7269), mB(0.1889), mInputStream(), \
    mOutputStream(), mActionData(mInputStream, mOutputStream), \
    mMenuData(), mColorTableMode(CT_GRADIENT), mHSVColor(false)
{
    mDebug = 1;
    configureMenu( mMenuData );
    mActionData.setGrid( new ComplexFractal );
    setColorTable();
    createFractal();
}

void AppData::setSize(int height, int width) {
    mHeight = height;
    mWidth = width;
}

int AppData::getHeight() const {
    return mHeight;
}

int AppData::getWidth() const {
    return mWidth;
}

PPM& AppData::getOutputImage() {
    return mActionData.getOutputImage();
}

ColorTable& AppData::getColorTable() {
    return mActionData.getTable();
}

void AppData::clearStreams() {
    mInputStream.clear();
    mInputStream.str("");
    mOutputStream.clear();
    mOutputStream.str("");
}


void AppData::createJulia1() {

    mA = -0.7629;
    mB =  0.1889;
    mMinX = 0.082;
    mMaxX = 1.15;
    mMinY = -0.67;
    mMaxY = 0.35;
    mMaxNumber = 550;
    mNumColor = 50;

    selectJulia();

    configureGrid(mMaxNumber);

    juliaParameters(mA, mB);

    fractalPlaneSize(mMinX, mMaxX, mMinY, mMaxY);

    fractalCalculate();

    setColorTable();

    gridApplyColorTable();
}

void AppData::createJulia2() {

    mA = -0.835;
    mB = -0.232;
    mMinX = -0.11;
    mMaxX = -0.09;
    mMinY = 0.33;
    mMaxY = 0.35;
    mMaxNumber = 550;
    mNumColor = 180;

    selectJulia();

    configureGrid(mMaxNumber);

    juliaParameters(mA, mB);

    fractalPlaneSize(mMinX, mMaxX, mMinY, mMaxY);

    fractalCalculate();

    setColorTable();

    gridApplyColorTable();
}

void AppData::createMandelbrot1() {
    mMinX = 0.36;
    mMaxX = 0.38;
    mMinY = 0.29;
    mMaxY = 0.32;
    mMaxNumber = 550;
    mNumColor = 760;

    selectMandelbrot();

    configureGrid(mMaxNumber);

    fractalPlaneSize(mMinX, mMaxX, mMinY, mMaxY);

    fractalCalculate();

    setColorTable();

    gridApplyColorTable();
}

void AppData::createMandelbrot2() {
    mMinX = 0.3792;
    mMaxX = 0.3819;
    mMinY = 0.3047;
    mMaxY = 0.3087;
    mMaxNumber = 550;
    mNumColor = 760;

    selectMandelbrot();

    configureGrid(mMaxNumber);

    fractalPlaneSize(mMinX, mMaxX, mMinY, mMaxY);

    fractalCalculate();

    setColorTable();

    gridApplyColorTable();
}

void AppData::createComplexFractal1() {
    mMinX = -2;
    mMaxX = 2;
    mMinY = -2;
    mMaxY = 2;
    mMaxNumber = 550;
    mNumColor = 180;

    selectComplexFractal();

    configureGrid(mMaxNumber);

    fractalPlaneSize(mMinX, mMaxX, mMinY, mMaxY);

    fractalCalculate();

    setColorTable();

    gridApplyColorTable();
}

void AppData::createComplexFractal2() {
    mMinX = -0.425;
    mMaxX = 0.829;
    mMinY = -0.558;
    mMaxY = 0.697;
    mMaxNumber = 550;
    mNumColor = 147;

    selectComplexFractal();

    configureGrid(mMaxNumber);

    fractalPlaneSize(mMinX, mMaxX, mMinY, mMaxY);

    fractalCalculate();

    setColorTable();

    gridApplyColorTable();
}

void AppData::runCommand(const std::string& choice) {
    if (mDebug != 0) {
        std::cout << choice << " " << mInputStream.str() << std::endl;
    }
    takeAction(choice, mMenuData, mActionData);

    if (mDebug != 0) {
        //std::cout << "Output after call: " << mOutputStream.str() << std::endl;
    }
}

void AppData::selectJulia() {
    clearStreams();
    runCommand("julia");
    clearStreams();
}

void AppData::selectMandelbrot() {
    clearStreams();
    runCommand("mandelbrot");
    clearStreams();
}

void AppData::selectComplexFractal() {
    clearStreams();
    runCommand("complex-fractal");
    clearStreams();
}

void AppData::configureGrid(int max) {
    clearStreams();
    {
        std::stringstream tmp;
        tmp << mHeight << " " << mWidth << " " << max;
        mInputStream.str(tmp.str());
    }
    runCommand("grid");
    clearStreams();
}

void AppData::juliaParameters(double a, double b) {
    clearStreams();
    {
        std::stringstream tmp;
        tmp << a << " " << b;
        mInputStream.str(tmp.str());
    }
    runCommand("julia-parameters");
    clearStreams();
}

void AppData::fractalPlaneSize(double x_min, double x_max, double y_min, double y_max) {
    clearStreams();
    {
        std::stringstream tmp;
        tmp << x_min << " " << x_max << " " << y_min << " " << y_max;
        mInputStream.str(tmp.str());
    }
    runCommand("fractal-plane-size");
    clearStreams();
}

void AppData::fractalCalculate() {
    clearStreams();
    runCommand("fractal-calculate");
    clearStreams();
}

void AppData::gridApplyColorTable() {
    clearStreams();
    runCommand("grid-apply-color-table");
    clearStreams();
}

void AppData::setInteractionMode(InteractionMode mode) {
    mInteractionMode = mode;
}

AppData::InteractionMode AppData::getInteractionMode() const {
    return mInteractionMode;
}

void AppData::setColorTable() {

    clearStreams();
    {
        std::stringstream tmp;
        tmp << mNumColor;
        mInputStream.str(tmp.str());
    }
    runCommand("set-color-table-size");

    if (mHSVColor == true) {
        clearStreams();
        {
            std::stringstream tmp;
            int middle_pos = mActionData.getTable().getNumberOfColors() / 2;

            Color c1 = mColor1;
            Color c2 = mColor2;
            double hue1, saturation1, value1, hue2, saturation2, value2;
            c1.getHSV( hue1, saturation1, value1 );
            c2.getHSV( hue2, saturation2, value2 );

            tmp << 0 << " " << hue1 << " " << saturation1 << " " << value1 << " " << middle_pos << " " << hue2 << " " << saturation2 << " " << value2;
            mInputStream.str(tmp.str());
        }
        runCommand("set-hsv-gradient");
        clearStreams();

        clearStreams();
        {
            std::stringstream tmp;
            int middle_pos = mActionData.getTable().getNumberOfColors() / 2;
            int last_pos = mActionData.getTable().getNumberOfColors() - 1;

            Color c2 = mColor2;
            Color c3 = mColor3;
            double hue1, saturation1, value1, hue2, saturation2, value2;
            c2.getHSV( hue1, saturation1, value1 );
            c3.getHSV( hue2, saturation2, value2 );

            tmp << middle_pos << " " << hue1 << " " << saturation1 << " " << value1 << " " << last_pos << " " << hue2 << " " << saturation2 << " " << value2;
            mInputStream.str(tmp.str());
        }
        runCommand("set-hsv-gradient");
        clearStreams();

        if ( mColorTableMode == CT_RANDOM3 ) {
            set3RandomColors();
        } else if ( mColorTableMode == CT_RANDOM ) {
            setAllRandomColors();
        } else if ( mColorTableMode == CT_REVERSE) {
            setReverseGradient();
        }
    } else if( mHSVColor == false ) {
        clearStreams();
        {
            std::stringstream tmp;
            int middle_pos = mActionData.getTable().getNumberOfColors() / 2;

            Color c1 = mColor1;
            Color c2 = mColor2;

            tmp << 0 << " " << c1.getRed() << " " << c1.getGreen() << " " << c1.getBlue() << " " << middle_pos << " " << c2.getRed() << " " << c2.getGreen() << " " << c2.getBlue();
            mInputStream.str(tmp.str());
        }
        runCommand("set-color-gradient");
        clearStreams();

        clearStreams();
        {
            std::stringstream tmp;
            int middle_pos = mActionData.getTable().getNumberOfColors() / 2;
            int last_pos = mActionData.getTable().getNumberOfColors() - 1;

            Color c2 = mColor2;
            Color c3 = mColor3;

            tmp << middle_pos << " " << c2.getRed() << " " << c2.getGreen() << " " << c2.getBlue() << " " << last_pos << " " << c3.getRed() << " " << c3.getGreen() << " " << c3.getBlue();
            mInputStream.str(tmp.str());
        }
        runCommand("set-color-gradient");
        clearStreams();
    }

    
}

void AppData::decreaseColorTableSize() {
    std::cout << mNumColor << std::endl;
    if ( mNumColor > 10 ) {
        mNumColor /= 1.1;
        setColorTable();
        gridApplyColorTable();
    }
}

void AppData::increaseColorTableSize() {
    std::cout << mNumColor << std::endl;
    if ( mNumColor < 1024 ) {
        mNumColor *= 1.1;
        setColorTable();
        gridApplyColorTable();
    }
}

void AppData::randomColor1() {
    int red, green, blue;
    red = rand() % 255;
    green = rand() % 255;
    blue = rand() % 255;
    mColor1.setRed(red);
    mColor1.setGreen(green);
    mColor1.setBlue(blue);

    setColorTable();
    gridApplyColorTable();
}

void AppData::randomColor2() {
    int red, green, blue;
    red = rand() % 255;
    green = rand() % 255;
    blue = rand() % 255;
    mColor2.setRed(red);
    mColor2.setGreen(green);
    mColor2.setBlue(blue);

    setColorTable();
    gridApplyColorTable();
}

void AppData::randomColor3() {
    int red, green, blue;
    red = rand() % 255;
    green = rand() % 255;
    blue = rand() % 255;
    mColor3.setRed(red);
    mColor3.setGreen(green);
    mColor3.setBlue(blue);

    setColorTable();
    gridApplyColorTable();
}

void AppData::zoomIn() {
    double dx = (1.0 - 0.9) * (mMaxX - mMinX) / 2.0;
    double dy = (1.0 - 0.9) * (mMaxY - mMinY) / 2.0;

    mMinX += dx;
    mMaxX -= dx;
    mMinY += dy;
    mMaxY -= dy;
}

void AppData::zoomOut() {
    double dx = (1.0 - 0.9) * (mMaxX - mMinX) / 2.0;
    double dy = (1.0 - 0.9) * (mMaxY - mMinY) / 2.0;

    mMinX -= dx;
    mMaxX += dx;
    mMinY -= dy;
    mMaxY += dy;
}

void AppData::moveLeft() {
    double dx = (1.0 - 0.9) * (mMaxX - mMinX) / 2.0;

    if (mMinX - dx >= -2.0) {
        mMinX -= dx;
        mMaxX -= dx;
    }
}

void AppData::moveRight() {
    double dx = (1.0 - 0.9) * (mMaxX - mMinX) / 2.0;

    if (mMaxX + dx <= 2.0) {
        mMinX += dx;
        mMaxX += dx;
    }
}

void AppData::moveDown() {
    double dy = (1.0 - 0.9) * (mMaxY - mMinY) / 2.0;

    if (mMinY - dy >= -2.0) {
        mMinY -= dy;
        mMaxY -= dy;
    }
}

void AppData::moveUp() {
    double dy = (1.0 - 0.9) * (mMaxY - mMinY) / 2.0;

    if (mMaxY + dy <= 2.0) {
        mMinY += dy;
        mMaxY += dy;
    }
}

void AppData::setFractalMode( FractalMode mode) {
    mFractalMode = mode;
}

AppData::FractalMode AppData::getFractalMode() const{
    return mFractalMode;
}

void AppData::increaseMaxNumber() {
    if ( mMaxNumber < 2048 ) {
        mMaxNumber *= 1.1;
    }
}

void AppData::decreaseMaxNumber() {
    if ( mMaxNumber > 11 ) {
        mMaxNumber /= 1.1;
    }
}

void AppData::setAB(int x, int y) {
    if (mFractalMode == M_MANDELBROT) {
        NumberGrid *grid = &mActionData.getGrid();
        ComplexFractal *fractal = dynamic_cast<ComplexFractal *>(grid);

        double delta_x = fractal->calculateDeltaX();
        double delta_y = fractal->calculateDeltaY();

        if (fractal != 0) {
            mA = mMinX + x * delta_x;
            mB = mMinY + y * delta_y;
        }
    }
}

void AppData::resetPlane() {
    mMinX = -2.0;
    mMaxX = 2.0;
    mMinY = -2.0;
    mMaxY = 2.0;
}

void AppData::createFractal() {

    if (mFractalMode == M_MANDELBROT) {
        selectMandelbrot();
    } else if (mFractalMode == M_JULIA) {
        selectJulia();
        juliaParameters(mA, mB);
    } else if (mFractalMode == M_COMPLEX) {
        selectComplexFractal();
    }

    configureGrid(mMaxNumber);
    fractalPlaneSize(mMinX, mMaxX, mMinY, mMaxY);
    fractalCalculate();
    gridApplyColorTable();
}

void AppData::nextColorTableMode() {
    std::cout << mColorTableMode << std::endl;
    if (mColorTableMode == CT_GRADIENT) { 
        mColorTableMode = CT_RANDOM3; 
    } else if (mColorTableMode == CT_RANDOM3) { 
        mColorTableMode = CT_RANDOM; 
    } else if (mColorTableMode == CT_RANDOM) {
        mColorTableMode = CT_REVERSE;
    } else if (mColorTableMode == CT_REVERSE ) {
        mColorTableMode = CT_GRADIENT;
    }
    std::cout << mColorTableMode << std::endl;


    setColorTable();
    gridApplyColorTable();
}

AppData::ColorTableMode AppData::getColorTableMode() const{
    return mColorTableMode;
}

void AppData::set3RandomColors() {

    clearStreams();
    {
        std::stringstream tmp;
        tmp << 0;
        mInputStream.str(tmp.str());
    }
    runCommand("set-random-color");
    clearStreams();

    clearStreams();
    {
        std::stringstream tmp;
        tmp << mNumColor / 2;
        mInputStream.str(tmp.str());
    }
    runCommand("set-random-color");
    clearStreams();

    clearStreams();
    {
        std::stringstream tmp;
        tmp << mNumColor-1;
        mInputStream.str(tmp.str());
    }
    runCommand("set-random-color");
    clearStreams();
}

void AppData::setAllRandomColors() {
    int i;
    for (i=0; i < mNumColor-1; i++) {
        clearStreams();
        {
            std::stringstream tmp;
            tmp << i;
            mInputStream.str(tmp.str());
        }
        runCommand("set-random-color");
        clearStreams();
    }
}

void AppData::setReverseGradient() {
    clearStreams();
    {
        std::stringstream tmp;
        int middle_pos = mNumColor / 2;

        Color c1 = mColor1;
        Color c2 = mColor2;

        tmp << 0 << " " << c1.getRed() << " " << c1.getGreen() << " " << c1.getBlue() << " " << middle_pos << " " << c2.getRed() << " " << c2.getGreen() << " " << c2.getBlue();
        mInputStream.str(tmp.str());
    }
    runCommand("set-color-gradient");
    clearStreams();

    clearStreams();
    {
        std::stringstream tmp;
        int middle_pos = mNumColor / 2;
        int endPos = mNumColor - 1;

        Color c1 = mColor2;
        Color c2 = mColor1;

        tmp << middle_pos << " " << c1.getRed() << " " << c1.getGreen() << " " << c1.getBlue() << " " << endPos << " " << c2.getRed() << " " << c2.getGreen() << " " << c2.getBlue();
        mInputStream.str(tmp.str());
    }
    runCommand("set-color-gradient");
    clearStreams();
}

void AppData::increaseChannel(Color& color, int channel) {
    int newColor;

    if (channel == 0) {
        newColor = color.getRed() + 10;
        if (newColor > 255) {
            newColor = 255;
        }
        color.setRed(newColor);
    } else if (channel == 1) {
        newColor = color.getGreen() + 10;
        if (newColor > 255) {
            newColor = 255;
        }
        color.setGreen(newColor);
    } else if (channel == 2) {
        newColor = color.getBlue() + 10;
        if (newColor > 255) {
            newColor = 255;
        }
        color.setBlue(newColor);
    }

    setColorTable();
    gridApplyColorTable();
}

void AppData::decreaseChannel(Color& color, int channel) {
    int newColor;

    if (channel == 0) {
        newColor = color.getRed() - 10;
        if (newColor < 0) {
            newColor = 0;
        }
        color.setRed(newColor);
    } else if (channel == 1) {
        newColor = color.getGreen() - 10;
        if (newColor < 0) {
            newColor = 0;
        }
        color.setGreen(newColor);
    } else if (channel == 2) {
        newColor = color.getBlue() - 10;
        if (newColor < 0) {
            newColor = 0;
        }
        color.setBlue(newColor);
    }

    setColorTable();
    gridApplyColorTable();
}

Color& AppData::fetchColor() {
    if (mInteractionMode == IM_COLOR1) {
        return mColor1;
    } else if (mInteractionMode == IM_COLOR2) {
        return mColor2;
    } else if (mInteractionMode == IM_COLOR3) {
        return mColor3;
    } else {
        static Color c;
        return c;
    }
}

void AppData::increaseRed() {
    increaseChannel(fetchColor(), 0);
}

void AppData::decreaseRed() {
    decreaseChannel(fetchColor(), 0);
}

void AppData::increaseGreen() {
    increaseChannel(fetchColor(), 1);
}

void AppData::decreaseGreen() {
    decreaseChannel(fetchColor(), 1);
}

void AppData::increaseBlue() {
    increaseChannel(fetchColor(), 2);
}

void AppData::decreaseBlue() {
    decreaseChannel(fetchColor(), 2);
}

void AppData::toggleHSVColor() {

    if (mHSVColor == true) { 
        mHSVColor = false;
    } else if (mHSVColor == false) { 
        mHSVColor = true;
    }

    setColorTable();
    gridApplyColorTable();
}