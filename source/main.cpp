#include "input_utilities.hpp"
#include "mandelbrot.hpp"

int main() {
    // size_t          imageWidth      = getParsedInput<size_t>("Please enter image width: ");
    // size_t          imageHeight     = getParsedInput<size_t>("Please enter a image height: ");
    // double          scaleFactor     = getParsedInput<double>("Please enter a scale factor: ");
    // double          topLeftReal     = getParsedInput<double>("Please enter the REAL part of a complex number for the TOP LEFT: ");
    // double          topLeftImag     = getParsedInput<double>("Please enter the IMAGINARY part of a complex number for the TOP LEFT: ");
    // double          bottomRightReal = getParsedInput<double>("Please enter the REAL part of a complex number for the BOTTOM RIGHT: ");
    // double          bottomRightImag = getParsedInput<double>("Please enter the IMAGINARY part of a complex number for the BOTTOM RIGHT: ");
    // complex<double> topLeft         = complex<double>(topLeftReal, topLeftImag);
    // complex<double> bottomRight     = complex<double>(bottomRightReal, bottomRightImag);
    // size_t          iterationMax    = getParsedInput<size_t>("Please enter the iteration cutoff: ");
    size_t          imageWidth   = 500;
    size_t          imageHeight  = 500;
    double          scaleFactor  = 1.0;
    complex<double> topLeft      = -2.0 + 1.2i;
    complex<double> bottomRight  = 0.5 - 1.2i;
    size_t          iterationMax = 500;

    vector<Pixel> imageData = calculatePixelData(imageWidth, imageHeight, scaleFactor, topLeft, bottomRight, iterationMax);

    for (auto& pixel : imageData) {
        std::cout << "Pixel { x: " << pixel.x << ", y: " << pixel.y << ", color: Color(" << static_cast<int>(pixel.color.r) << "," << static_cast<int>(pixel.color.g) << "," << static_cast<int>(pixel.color.b) << ")}, ";
    }

    return 0;
}