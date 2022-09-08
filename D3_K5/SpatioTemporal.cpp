#include <hls_stream.h>

//SODA for Jacobi_2D with k=3 & ts=2
#include "SODA_Jacobi.h"

void temporal(
		hls::stream <mat> &in0,
		hls::stream <mat> &in1,
		hls::stream <mat> &in2,
		hls::stream <mat> &in3,
		hls::stream <mat> &in4,
		hls::stream <mat> &out0,
		hls::stream <mat> &out1,
		hls::stream <mat> &out2,
		hls::stream <mat> &out3,
		hls::stream <mat> &out4
) {
	hls::stream<mat> stage0_0, stage0_1, stage0_2, stage0_3, stage0_4,stage1_0, stage1_1, stage1_2, stage1_3, stage1_4;
#pragma HLS DATAFLOW
/*
#pragma HLS STREAM variable=stage0_0 depth=9
#pragma HLS STREAM variable=stage0_1 depth=9
#pragma HLS STREAM variable=stage0_2 depth=9
#pragma HLS STREAM variable=stage0_3 depth=9
#pragma HLS STREAM variable=stage0_4 depth=9
*/
	jacobi9d_soda(in0, in1, in2, in3, in4, stage0_0, stage0_1, stage0_2, stage0_3,stage0_4);
	jacobi9d_soda(stage0_0, stage0_1, stage0_2, stage0_3,stage0_4, stage1_0, stage1_1, stage1_2, stage1_3, stage1_4);
	jacobi9d_soda(stage1_0, stage1_1, stage1_2, stage1_3, stage1_4, out0, out1, out2, out3, out4);

}
