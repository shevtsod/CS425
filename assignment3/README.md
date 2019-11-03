# CS 425 - Assignment 3

## Problem Statement

### Problem 1

Implement the 3x3 Sobel edge operator. Given the input file
[`building.raw`](./in/building.raw), compute the following:

- Horizontal edge image
- Vertical edge image
- Gradient image
- Thresholded gradient image using threshold _T<sub>E</sub>_ = 128.

### Problem 2

Implement the 3x3 Laplacian sharpening filter. Given the input file
[`moon.raw`](./in/moon.raw), sharpen the image with different values of _w_.

## Developing

Developed in C++ and compiled using [GCC](https://gcc.gnu.org/).

To build and run the program, use the following command:

```shell
make && ./build/out
```

Program outputs in `.raw` format are available under
[`./assets/out/raw/`](./assets/out/raw).

Screenshots of program outputs in `.png` format are available under
[`./assets/out/screenshots/`](./assets/out/screenshots).
