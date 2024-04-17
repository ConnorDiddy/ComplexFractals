COMMON_OBJECTS := user_io.o controllers.o image_output.o Image.o image_drawing.o PPM.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o

all: hello questions_3 ascii_image image_file four_square flag_romania ppm_menu

hello: hello.o
	g++ -std=c++11 -o hello hello.o
hello.o: hello.cpp
	g++ -std=c++11 -c hello.cpp

questions_3: questions_3.o $(COMMON_OBJECTS)
	g++ -std=c++11 -o questions_3 questions_3.o $(COMMON_OBJECTS)
questions_3.o: questions_3.cpp image_menu.h
	g++ -std=c++11 -c questions_3.cpp

user_io.o: user_io.cpp image_menu.h
	g++ -std=c++11 -c user_io.cpp
controllers.o: controllers.cpp image_menu.h Image.h PPM.h
	g++ -std=c++11 -c controllers.cpp

ascii_image: ascii_image.o $(COMMON_OBJECTS)
	g++ -std=c++11 -o ascii_image ascii_image.o $(COMMON_OBJECTS)
ascii_image.o: ascii_image.cpp image_menu.h Image.h PPM.h
	g++ -std=c++11 -c ascii_image.cpp

image_output.o: image_output.cpp image_menu.h Image.h
	g++ -std=c++11 -c image_output.cpp
image_drawing.o: image_drawing.cpp image_menu.h Image.h
	g++ -std=c++11 -c image_drawing.cpp
Image.o: Image.cpp image_menu.h Image.h PPM.h
	g++ -std=c++11 -c Image.cpp

image_file: image_file.o $(COMMON_OBJECTS)
	g++ -std=c++11 -o image_file image_file.o $(COMMON_OBJECTS)

image_file.o: image_file.cpp image_menu.h Image.h PPM.h
	g++ -std=c++11 -c image_file.cpp

PPM.o: PPM.cpp image_menu.h Image.h PPM.h
	g++ -std=c++11 -c PPM.cpp

four_square: four_square.o $(COMMON_OBJECTS)
	g++ -std=c++11 -o four_square four_square.o $(COMMON_OBJECTS)

four_square.o: four_square.cpp image_menu.h Image.h PPM.h
	g++ -std=c++11 -c four_square.cpp

flag_romania: flag_romania.o $(COMMON_OBJECTS)
	g++ -std=c++11 -o flag_romania flag_romania.o $(COMMON_OBJECTS)

flag_romania.o: flag_romania.cpp image_menu.h Image.h PPM.h
	g++ -std=c++11 -c flag_romania.cpp

ppm_menu: ppm_menu.o $(COMMON_OBJECTS)
	g++ -std=c++11 -o ppm_menu ppm_menu.o $(COMMON_OBJECTS)

ppm_menu.o: ppm_menu.cpp image_menu.h Image.h PPM.h ColorTable.h
	g++ -std=c++11 -c ppm_menu.cpp

ActionData.o: ActionData.cpp image_menu.h Image.h PPM.h ColorTable.h
	g++ -std=c++11 -c ActionData.cpp

MenuData.o: MenuData.cpp ActionData.h
	g++ -std=c++11 -c MenuData.cpp

image_filters.o: image_filters.cpp
	g++ -std=c++11 -c image_filters.cpp

NumberGrid.o: NumberGrid.cpp NumberGrid.h
	g++ -std=c++11 -c NumberGrid.cpp

ColorTable.o: ColorTable.cpp ColorTable.h
	g++ -std=c++11 -c ColorTable.cpp

ComplexFractal.o: ComplexFractal.cpp ComplexFractal.h
	g++ -std=c++11 -c ComplexFractal.cpp

JuliaSet.o: JuliaSet.cpp JuliaSet.h
	g++ -std=c++11 -c JuliaSet.cpp

MandelbrotSet.o: MandelbrotSet.cpp MandelbrotSet.h
	g++ -std=c++11 -c MandelbrotSet.cpp

ThreadedGrid.o: ThreadedGrid.cpp ThreadedGrid.h
	g++ -std=c++11 -c ThreadedGrid.cpp

clean:
	rm *.o
	rm hello
	rm ascii_image
	rm four_square
	rm flag_romania
	rm image_file
	rm ppm_menu
	rm questions_3