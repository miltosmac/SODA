#include <hls_stream.h>

//SODA for Jacobi_2D with k=3 & ts=2
#include "SODA_Jacobi.h"

void temporal(
		hls::stream <mat> &in0,
		hls::stream <mat> &in1,
		hls::stream <mat> &in2,
		hls::stream <mat> &out0,
		hls::stream <mat> &out1,
		hls::stream <mat> &out2
) {
	hls::stream<mat> stage0_0, stage0_1, stage0_2,stage1_0,stage1_1,stage1_2,
	stage2_0,stage2_1,stage2_2,stage3_0,stage3_1,stage3_2,stage4_0,stage4_1,stage4_2,
	stage5_0,stage5_1,stage5_2,stage6_0,stage6_1,stage6_2,stage7_0,stage7_1,stage7_2,stage8_0,stage8_1,stage8_2;
#pragma HLS DATAFLOW
#pragma HLS STREAM variable=stage0_0 depth=9
#pragma HLS STREAM variable=stage0_1 depth=9
#pragma HLS STREAM variable=stage0_2 depth=9
#pragma HLS STREAM variable=stage1_0 depth=9
#pragma HLS STREAM variable=stage1_1 depth=9
#pragma HLS STREAM variable=stage1_2 depth=9
#pragma HLS STREAM variable=stage2_0 depth=9
#pragma HLS STREAM variable=stage2_1 depth=9
#pragma HLS STREAM variable=stage2_2 depth=9
#pragma HLS STREAM variable=stage3_0 depth=9
#pragma HLS STREAM variable=stage3_1 depth=9
#pragma HLS STREAM variable=stage3_2 depth=9
#pragma HLS STREAM variable=stage4_0 depth=9
#pragma HLS STREAM variable=stage4_1 depth=9
#pragma HLS STREAM variable=stage4_2 depth=9
#pragma HLS STREAM variable=stage5_0 depth=9
#pragma HLS STREAM variable=stage5_1 depth=9
#pragma HLS STREAM variable=stage5_2 depth=9
#pragma HLS STREAM variable=stage6_0 depth=9
#pragma HLS STREAM variable=stage6_1 depth=9
#pragma HLS STREAM variable=stage6_2 depth=9
#pragma HLS STREAM variable=stage7_0 depth=9
#pragma HLS STREAM variable=stage7_1 depth=9
#pragma HLS STREAM variable=stage7_2 depth=9
#pragma HLS STREAM variable=stage8_0 depth=9
#pragma HLS STREAM variable=stage8_1 depth=9
#pragma HLS STREAM variable=stage8_2 depth=9
	jacobi9d_soda(in0, in1, in2,stage0_0, stage0_1, stage0_2);
	jacobi9d_soda(stage0_0, stage0_1, stage0_2, stage1_0,stage1_1,stage1_2);
	jacobi9d_soda(stage1_0, stage1_1, stage1_2, stage2_0,stage2_1,stage2_2);
	jacobi9d_soda(stage2_0, stage2_1, stage2_2, stage3_0,stage3_1,stage3_2);
	jacobi9d_soda(stage3_0, stage3_1, stage3_2, stage4_0,stage4_1,stage4_2);
	jacobi9d_soda(stage4_0, stage4_1, stage4_2, stage5_0,stage5_1,stage5_2);
	jacobi9d_soda(stage5_0, stage5_1, stage5_2, stage6_0,stage6_1,stage6_2);
	jacobi9d_soda(stage6_0, stage6_1, stage6_2, stage7_0,stage7_1,stage7_2);
	jacobi9d_soda(stage7_0, stage7_1, stage7_2, stage8_0,stage8_1,stage8_2);
	jacobi9d_soda(stage8_0,stage8_1,stage8_2, out0, out1, out2);
}
