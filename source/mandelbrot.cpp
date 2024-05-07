#include <cmath>
#include "mandelbrot.hpp"

optional<size_t> escapeTime(complex<double> c, size_t iterationMax) {
    complex<double> z = 0.0 + 0.0i;

    for (size_t n = 0; n < iterationMax; n++) {
        z = (z * z) + c;
        double zNormSquared = z.real() * z.real() + z.imag() * z.imag();

        if (zNormSquared > 4.0) {
            // not in mandelbrot set
            return n;
        }
    }
    // in the mandelbrot set
    return std::nullopt;
}

Color complexToGrayscale(complex<double> c, size_t iterationMax) {
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;

    if (auto escapeIterationCount = escapeTime(c, iterationMax)) {
        red = static_cast<uint8_t>(*escapeIterationCount);
        green = static_cast<uint8_t>(*escapeIterationCount);
        blue = static_cast<uint8_t>(*escapeIterationCount);
    }

    return {red, green, blue};
}

complex<double> pixelToComplex(
    size_t pixelX,
    size_t pixelY,
    size_t imageWidth,
    size_t imageHeight,
    complex<double> topLeft,
    complex<double> topRight
) {
    double leftBound   = topLeft.real();
    double topBound    = topLeft.imag();
    double rightBound  = topRight.real();
    double bottomBound = topRight.imag();

    double rectangleWidth = (rightBound - leftBound) * pixelX / imageWidth;
    double rectangleHeight = (bottomBound - topBound) * pixelY / imageHeight;

    double real = leftBound + rectangleWidth;
    double imaginary = topBound + rectangleHeight;

    return complex<double>(real, imaginary);
}

vector<Pixel> calculatePixelData(
    size_t imageWidth,
    size_t imageHeight,
    double scaleFactor,
    complex<double> topLeft,
    complex<double> topRight,
    size_t iterationMax
) {
    vector<Pixel> pixels;
    pixels.reserve(imageWidth * imageHeight);

    for (size_t pixelY = 0; pixelY < imageHeight; pixelY++) {
        for (size_t pixelX = 0; pixelX < imageWidth; pixelX++) {
            complex<double> c = pixelToComplex(pixelY, pixelX, imageWidth, imageHeight, topLeft, topRight);
            Color color = complexToGrayscale(c, iterationMax);
            pixels.push_back({pixelY, pixelX, color});
        }
    }

    return pixels;
}


