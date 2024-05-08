#include <cmath>
#include "mandelbrot.hpp"

optional<size_t> calculateEscapeTime(complex<double> c, size_t iterationMax) {
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

Color escapeTimeToGrayscale(optional<size_t> escapeTime) {
    uint8_t red   = 0;
    uint8_t green = 0;
    uint8_t blue  = 0;


    if (escapeTime.has_value()) {
        red   = static_cast<uint8_t>(*escapeTime);
        green = static_cast<uint8_t>(*escapeTime);
        blue  = static_cast<uint8_t>(*escapeTime);
    }

    return {red, green, blue};
}

complex<double> pixelCoordsToComplex(
    size_t          pixelX,
    size_t          pixelY,
    size_t          imageWidth,
    size_t          imageHeight,
    complex<double> topLeft,
    complex<double> bottomRight
) {
    double leftBound   = topLeft.real();
    double topBound    = topLeft.imag();
    double rightBound  = bottomRight.real();
    double bottomBound = bottomRight.imag();

    double rectangleWidth  = (rightBound - leftBound) * pixelX / imageWidth;
    double rectangleHeight = (bottomBound - topBound) * pixelY / imageHeight;

    double real      = leftBound + rectangleWidth;
    double imaginary = topBound + rectangleHeight;

    return complex<double>(real, imaginary);
}

vector<Pixel> calculatePixelData(
    size_t          imageWidth,
    size_t          imageHeight,
    double          scaleFactor,
    complex<double> topLeft,
    complex<double> bottomRight,
    size_t          iterationMax
) {
    vector<Pixel> pixels;
    pixels.reserve(imageWidth * imageHeight);

    for (size_t pixelX = 0; pixelX < imageWidth; pixelX++) {
        for (size_t pixelY = 0; pixelY < imageHeight; pixelY++) {

            complex<double>  c          = pixelCoordsToComplex(pixelY, pixelX, imageWidth, imageHeight, topLeft, bottomRight);
            optional<size_t> escapeTime = calculateEscapeTime(c, iterationMax);
            Color            color      = escapeTimeToGrayscale(escapeTime);
            
            Pixel            pixel      = { pixelY, pixelX, color };
            pixels.push_back(pixel);
        }
    }

    return pixels;
}
