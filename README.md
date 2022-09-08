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
* The SpatioTemporal.cpp file should be used as the top function for the implementation of multiple time-steps.
* Utilize the provided Test-Bench from the corresponding folder.
* In the header file the defined size of the grid can be modified.
* The number of Time-Steps can be modified in the Temporal.cpp file, by adding succesive calls to the jacobi9d funncion and declaring the intermediate variables.

### Introduction 

>This architecture is based on the work done in [[1]](#1) which in turn is an expansion on [[2]](#2). The challenge
that this design addresses is the optimality of the design when more than one Computation Kernels (CKs)
are used in a single stage, where a CK is a compute module that implements the kernel function. That
means that more than one inputs are processed at each clock and more than one outputs are produced
by the design. Essentially, [[1]](#1) introduces an optimal design that exploits spatial parallelism, i.e., the
concurrent calculation of results within the same clock cycle.
>This architecture proposed in [[1]](#1) retains the properties that the architecture in [[2]](#2) achieves and
extends them to a design with multiple CKs. Firstly, the design is fully pipelined, meaning that the CKs are
able to consume one new input every clock. Additionally, it fully reuses the input data so that they only
need to be fetched once from external memory, as well as creating a memory system with the minimum
reuse buffer size. It is important to note that the input elements are lexicographically ordered and
streamed into the design. The architecture developed computes a 9-Point Jacobi kernel, therefore the
structure presented below is dedicated to the stencil pattern of a 9-Point stencil (square).

![alt text](https://github.com/miltosmac/SODA/blob/main/SODA_Illustrations/SPTA_Overview.jpg?raw=true)

### References
<a id="1">[1]</a> 
Y. Chi, J. Cong, P. Wei and P. Zhou, "SODA: Stencil with Optimized Dataflow Architecture," 2018 IEEE/ACM International Conference on Computer-Aided Design (ICCAD), 2018, pp. 1-8, doi: 10.1145/3240765.3240850.

<a id="2">[2]</a> 
Cong, Jason & Li, Peng & Xiao, Bingjun & Zhang, Peng. (2014). An optimal microarchitecture for stencil computation acceleration based on non-uniform partitioning of data reuse buffers. 1-6. 10.1109/DAC.2014.6881404. 
