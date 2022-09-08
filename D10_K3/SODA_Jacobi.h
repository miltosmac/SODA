/**************************************************************************
9-Point Jacobi 2-D SODA Implementation Header File
***************************************************************************/
#include <stdio.h>
#include "hls_stream.h"
#include <assert.h>
#include <ap_fixed.h>

// Compare TB vs HW C-model and/or RTL
#ifndef __JACOBI9SODA__
#define __JACOBI9SODA__

#define HW_COSIM

#define MAX_ROWS 2160
#define MAX_COLUMNS 4096

#define WIDTH 159
#define HEIGHT 159
#define k 3 // The number of PE's (k) should divide WIDTH perfectly i.e. leaving zero remainder
#define ts 10//TIME STEPS (Temporal Parallelism): The number of time steps after which we want the result produced i.e. the n. of Stages cascaded together.
#define FIFO_DEPTH (WIDTH/k-1)

//typedef float mat;
typedef ap_fixed<36,18> mat;

void jacobi9d_soda(
		hls::stream <mat> &in0,
		hls::stream <mat> &in1,
		hls::stream <mat> &in2,
		hls::stream <mat> &out0,
		hls::stream <mat> &out1,
		hls::stream <mat> &out2
		);

void temporal(
	hls::stream <mat> &in0,
	hls::stream <mat> &in1,
	hls::stream <mat> &in2,
	hls::stream <mat> &out0,
	hls::stream <mat> &out1,
	hls::stream <mat> &out2
);
#endif // __JACOBI9SODA__ not defined
