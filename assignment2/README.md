# CS 425 - Assignment 1

## Problem Statement

Given an image [`rose.raw`](./in/rose.raw):

### Problem 1

Apply the histogram equalization algorithm discussed in class to the input image
[`ct.raw`](./in/ct.raw).

### Problem 2

Implement the following averaging filters for smoothing:

```
         |1 1 1|
H1 = 1/9 |1 1 1|
         |1 1 1|
```

```
     |0.075 0.125 0.075|
H2 = |0.125 0.200 0.125|
     |0.075 0.125 0.075|
```

Apply the filters to input file [`testpattern.raw`](./in/testpattern.raw). Are
there visible visual differences between the results of the two filters?

### Problem 3

Apply the 3x3 median filter to the noisy input image
[`circuit.raw`](./in/circuit.raw).

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
