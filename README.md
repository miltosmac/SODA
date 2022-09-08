# SODA
## Stencil with Optimized Dataflow Architecture

### Table of contents
* [Technologies](#Technologies)
* [Setup](#setup)
* [Introduction](#Introduction)
* [Single Time-Step](#Single-Time-Step)
* [Multiple Time-Stepsp](#Multiple-Time-Steps)
* [Detailed Explanation](#Detailed-Explanation)

### Technologies
Project is created with:
* C/C+
* Vitis HLS 2021.2

### Setup
* Run Vitis (or Vivado) HLS adding the source & header files from the corresponding folder.
* The jacobi9d.cpp file should be used as the top function for the implementation of a single time-step.
* The Temporal.cpp file should be used as the top function for the implementation of multiple time-steps.
* Utilize the provided Test-Bench from the corresponding folder.
* In the header file the defined size of the grid can be modified.
* The number of Time-Steps can be modified in the Temporal.cpp file, by adding succesive calls to the jacobi9d funncion and declaring the intermediate variables.

### Introduction 
