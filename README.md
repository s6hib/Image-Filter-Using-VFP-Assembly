# Image filter using VFP Assembly

This repository contains ARM assembly code and a C++ wrapper that performs selective enhancement of the blue color channel in an image.

## Overview

The ARM assembly script reads an image's pixels and for each pixel, it calculates the ratio of the red to green channel intensities. If this ratio is greater than a certain threshold (1.5 in the provided code), it enhances the intensity of the blue channel by multiplying it by this ratio.

The C++ wrapper uses the CImg library to load an image, perform the filtering operation (either a default operation or the custom assembly operation defined in the assembly code), and then save the filtered image.

## Usage

Compile the project using the provided Makefile. This should produce an executable program.
Run the program with a command-line argument specifying the path to the image file you want to process. The program will save the processed image as output.jpg.

## Requirements

To use this code, you'll need:

- An ARM-based system or emulator
- A C++ compiler
- The CImg library
- A program for reading and writing image data
- Make utility for building the project

## Building

The project includes a Makefile that defines rules for building the project. To build the project, simply navigate to the project directory in a terminal and run the make command. The Makefile should handle the rest.

Please note that this code operates on low-level image data and does not handle file I/O, image decoding or encoding, or memory management. It's intended to be used as part of a larger program that handles these tasks.

## Tested

The "278485.jpg" file is my original picture **BEFORE** the filter, and "output.jpg" is **AFTER** the filter was used.
