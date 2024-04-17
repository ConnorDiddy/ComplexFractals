#include "image_menu.h"

void plusEquals( ActionData& action_data ){
    action_data.getInputImage1() += action_data.getInputImage2();
}
void minusEquals( ActionData& action_data ){
    action_data.getInputImage1() -= action_data.getInputImage2();
}
void timesEquals( ActionData& action_data ){
    double doubleInput = getDouble( action_data, "Factor? ");
    action_data.getInputImage1() *= doubleInput;
}
void divideEquals( ActionData& action_data ){
    double doubleInput = getDouble( action_data, "Factor? ");
    action_data.getInputImage1() /= doubleInput;
}
void plus( ActionData& action_data ){
    action_data.getOutputImage() =  action_data.getInputImage1() + action_data.getInputImage2();
}
void minus( ActionData& action_data ){
    action_data.getOutputImage() =  action_data.getInputImage1() - action_data.getInputImage2();
}
void times( ActionData& action_data ){
    double doubleInput = getDouble( action_data, "Factor? ");
    action_data.getOutputImage() =  action_data.getInputImage1() * doubleInput;
}
void divide( ActionData& action_data ){
    double doubleInput = getDouble( action_data, "Factor? ");
    action_data.getOutputImage() =  action_data.getInputImage1() / doubleInput;
}

void grayFromRed(ActionData& action_data) {
    action_data.getInputImage1().grayFromRed( action_data.getOutputImage() );
}

void grayFromGreen(ActionData& action_data) {
    action_data.getInputImage1().grayFromGreen( action_data.getOutputImage() );
}

void grayFromBlue(ActionData& action_data) {
    action_data.getInputImage1().grayFromBlue( action_data.getOutputImage() );
}

void grayFromLinearColorimetric(ActionData& action_data) {
    action_data.getInputImage1().grayFromLinearColorimetric( action_data.getOutputImage() );
}

void plusEqualsInt( ActionData& action_data ) {
    int boost = getInteger( action_data, "Boost? " );
    action_data.getInputImage1() += boost;
}

void sepiaFilter(ActionData& action_data) {
    PPM dst;
    action_data.getInputImage1().sepiaFilter( dst );
    action_data.getOutputImage() = dst;
}

void orangeFilter(ActionData& action_data) {
    PPM dst;
    action_data.getInputImage1().orangeFilter( dst );
    action_data.getOutputImage() = dst;
}