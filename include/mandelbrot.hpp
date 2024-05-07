#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

#include <complex>
#include <cstdint>
#include <optional>
#include <vector>

using std::complex;
using namespace std::complex_literals;
using std::optional;
using std::vector;

typedef struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Color;

typedef struct Pixel {
    size_t x;
    size_t y;
    Color color;
} Pixel;

optional<size_t> escapeTime(complex<double> c, size_t iterationMax);

complex<double> pixelToComplex(
    size_t pixelX,
    size_t pixelY,
    size_t imageWidth,
    size_t imageHeight,
    complex<double> topLeft,
    complex<double> topRight
);

vector<Pixel> calculatePixelData(
    size_t imageWidth,
    size_t imageHeight,
    double scaleFactor,
    complex<double> topLeft,
    complex<double> topRight,
    size_t iterationMax
);

#endif