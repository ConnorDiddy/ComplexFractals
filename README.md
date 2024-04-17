# Complex Fractals

This complex fractal image generator is a C++ program with a GUI that allows the user to create beautiful images of both Mandelbrot and Julia sets, as well as customize the colors and zoom/pan around the images. There is a lot that goes into this project, such as multithreading with mutexes to ensure rapid image generation. 

## Installation instructions
1. Navigate to the source/gui-src directory
2. Run the "make" command
~~~~~~~~~~~~~.bash
make
~~~~~~~~~~~~~
3. Run the created executable
~~~~~~~~~~~~~.bash
./glut_main
~~~~~~~~~~~~~

## Usage

| Key/Action         | Method(s) called                                       | Notes                                                                      |
|--------------------|--------------------------------------------------------|----------------------------------------------------------------------------|
|                    |                                                        | Initial image                                                              |
| start              |                                                        | Displays a Julia set different from others in methods.                     |
|                    |                                                        | Pre-built configurations                                                   |
| 'J'                | `createJulia1()`                                      |                                                                            |
| 'j'                | `createJulia2()`                                      |                                                                            |
| 'M'                | `createMandelbrot1()`                                 |                                                                            |
| 'm'                | `createMandelbrot2()`                                 |                                                                            |
| 'C'                | `createComplexFractal1()`                             |                                                                            |
| 'c'                | `createComplexFractal2()`                             |                                                                            |
|                    |                                                        | Interaction modes                                                          |
| 'T'                | `setInteractionMode()`                                | Color table interaction mode                                               |
| 't'                | `setInteractionMode()`                                | Fractal interaction mode                                                   |
|                    |                                                        | Fractal Modes                                                              |
| 'b'                | `setFractalMode()`, `createFractal()`                 | Mandelbrot mode                                                            |
| 'n'                | `setFractalMode()`, `createFractal()`                 | Julia mode                                                                 |
| 'F'                | `setFractalMode()`, `createFractal()`                 | Complex fractal mode                                                       |
|                    |                                                        | Color table operations                                                     |
| '>' or '.'         | `increaseColorTableSize()`                            | The user can use either '>' or '.', your code must support both.           |
| '<' or ','         | `decreaseColorTableSize()`                            | The user can use either '<' or ',', your code must support both.           |
| 'r'                | `randomColor1()`                                      | Color table display mode only. Otherwise, do not do this action.           |
| 'R'                | `randomColor2()`                                      | Color table display mode only. Otherwise, do not do this action.           |
|                    |                                                        | Plane coordinate operations                                                 |
| 'z'                | `zoomIn()`, `createFractal()`                        | Zoom into the plane.                                                       |
| 'Z'                | `zoomOut()`, `createFractal()`                       | Zoom out of the plane.                                                     |
| left arrow         | `moveLeft()`, `createFractal()`                      | Move the view port left in the plane.                                       |
| right arrow        | `moveRight()`, `createFractal()`                     | Move the view port right in the plane.                                      |
| down arrow         | `moveDown()`, `createFractal()`                      | Move the view port down in the plane.                                       |
| up arrow           | `moveUp()`, `createFractal()`                        | Move the view port up in the plane.                                         |
| 'R'                | `resetPlane()`, `createFractal()`                     | Fractal display mode only. Otherwise, do not do this action.               |
| left mouse button  | `setAB()`, `setFractalMode()`, `createFractal()`     | Fractal display mode and Mandelbrot fractal mode only. Otherwise, do not do this action. Set the A/B values, change the fractal mode to Julia, the create the fractal. |
|                    |                                                        | Fractal calculation configuration                                          |
| '+' or '='         | `increaseMaxNumber()`, `createFractal()`             | The user can use either '+' or '=', your code must support both.           |
| '-' or '_'         | `decreaseMaxNumber()`, `createFractal()`             | The user can use either '-' or '_', your code must support both.           |
|                    |                                                        | Window configuration                                                       |
| resize             |                                                        | `setSize()` is called. It should recreate the fractal currently configured in the data. |


## Example Images

![alt text](https://github.com/connordiddy/complexfractals/blob/main/julia.png?raw=true)
![alt text](https://github.com/connordiddy/complexfractals/blob/main/mandelbrot.png?raw=true)
![alt text](https://github.com/connordiddy/complexfractals/blob/main/mandelbrot2.png?raw=true)