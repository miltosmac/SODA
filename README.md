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

This architecture is based on the work done in [9] which in turn is an expansion on [6]. The challenge
that this design addresses is the optimality of the design when more than one Computation Kernels (CKs)
are used in a single stage, where a CK is a compute module that implements the kernel function. That
means that more than one inputs are processed at each clock and more than one outputs are produced
17
by the design. Essentially, [9] introduces an optimal design that exploits spatial parallelism, i.e., the
concurrent calculation of results within the same clock cycle.
This architecture proposed in [9] retains the properties that the architecture in [6] achieves and
extends them to a design with multiple CKs. Firstly, the design is fully pipelined, meaning that the CKs are
able to consume one new input every clock. Additionally, it fully reuses the input data so that they only
need to be fetched once from external memory, as well as creating a memory system with the minimum
reuse buffer size. It is important to note that the input elements are lexicographically ordered and
streamed into the design. The architecture developed computes a 9-Point Jacobi kernel, therefore the
structure presented below is dedicated to the stencil pattern of a 9-Point stencil (square).
