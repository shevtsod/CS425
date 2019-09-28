# CS 425 - Assignment 1

## Problem Statement

Given an image [`rose.raw`](./in/rose.raw):

1. Resize the image to 128x128, 64x64, and 32x32 pixels.
2. Create three different quantized versions of the image:
   1. Set the 2 lowest order bits to 0.
   2. Set the 3 lowest order bits to 0.
   3. Set the 4 lowest order bits to 0.
3. Output a histogram of the image in 256x256 pixels. The background has value
   255, and columns value 0. Run this program with `rose.raw` and the three
   images generated in step 2.

## Developing

Developed in C++ and compiled using [GCC](https://gcc.gnu.org/).

To build and run the program, run:

```shell
make
./build/out
```

Program outputs in `.raw` format are available under
[`./assets/out/raw/`](./assets/out/raw).

Screenshots of program outputs in `.png` format are available under
[`./assets/out/screenshots/`](./assets/out/screenshots).
