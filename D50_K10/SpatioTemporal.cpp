#include <hls_stream.h>

//SODA for Jacobi_2D with k=3 & ts=2
#include "SODA_Jacobi.h"

void temporal(
		hls::stream <mat> &in0,
		hls::stream <mat> &in1,
		hls::stream <mat> &in2,
		hls::stream <mat> &in3,
		hls::stream <mat> &in4,
		hls::stream <mat> &in5,
		hls::stream <mat> &in6,
		hls::stream <mat> &in7,
		hls::stream <mat> &in8,
		hls::stream <mat> &in9,
		hls::stream <mat> &out0,
		hls::stream <mat> &out1,
		hls::stream <mat> &out2,
		hls::stream <mat> &out3,
		hls::stream <mat> &out4,
		hls::stream <mat> &out5,
		hls::stream <mat> &out6,
		hls::stream <mat> &out7,
		hls::stream <mat> &out8,
		hls::stream <mat> &out9
) {
	hls::stream<mat> stage0_0, stage0_1, stage0_2, stage0_3, stage0_4, stage0_5, stage0_6, stage0_7, stage0_8, stage0_9,
	stage1_0, stage1_1, stage1_2, stage1_3, stage1_4, stage1_5, stage1_6, stage1_7, stage1_8, stage1_9,
	stage2_0, stage2_1, stage2_2, stage2_3, stage2_4, stage2_5, stage2_6, stage2_7, stage2_8, stage2_9,
	stage3_0, stage3_1, stage3_2, stage3_3, stage3_4, stage3_5, stage3_6, stage3_7, stage3_8, stage3_9,
	stage4_0, stage4_1, stage4_2, stage4_3, stage4_4, stage4_5, stage4_6, stage4_7, stage4_8, stage4_9,
	stage5_0, stage5_1, stage5_2, stage5_3, stage5_4, stage5_5, stage5_6, stage5_7, stage5_8, stage5_9,
	stage6_0, stage6_1, stage6_2, stage6_3, stage6_4, stage6_5, stage6_6, stage6_7, stage6_8, stage6_9,
	stage7_0, stage7_1, stage7_2, stage7_3, stage7_4, stage7_5, stage7_6, stage7_7, stage7_8, stage7_9,
	stage8_0, stage8_1, stage8_2, stage8_3, stage8_4, stage8_5, stage8_6, stage8_7, stage8_8, stage8_9,
	stage9_0, stage9_1, stage9_2, stage9_3, stage9_4, stage9_5, stage9_6, stage9_7, stage9_8, stage9_9,
	stage10_0, stage10_1, stage10_2, stage10_3, stage10_4, stage10_5, stage10_6, stage10_7, stage10_8, stage10_9,
	stage11_0, stage11_1, stage11_2, stage11_3, stage11_4, stage11_5, stage11_6, stage11_7, stage11_8, stage11_9,
	stage12_0, stage12_1, stage12_2, stage12_3, stage12_4, stage12_5, stage12_6, stage12_7, stage12_8, stage12_9,
	stage13_0, stage13_1, stage13_2, stage13_3, stage13_4, stage13_5, stage13_6, stage13_7, stage13_8, stage13_9,
	stage14_0, stage14_1, stage14_2, stage14_3, stage14_4, stage14_5, stage14_6, stage14_7, stage14_8, stage14_9,
	stage15_0, stage15_1, stage15_2, stage15_3, stage15_4, stage15_5, stage15_6, stage15_7, stage15_8, stage15_9,
	stage16_0, stage16_1, stage16_2, stage16_3, stage16_4, stage16_5, stage16_6, stage16_7, stage16_8, stage16_9,
	stage17_0, stage17_1, stage17_2, stage17_3, stage17_4, stage17_5, stage17_6, stage17_7, stage17_8, stage17_9,
	stage18_0, stage18_1, stage18_2, stage18_3, stage18_4, stage18_5, stage18_6, stage18_7, stage18_8, stage18_9,
	stage19_0, stage19_1, stage19_2, stage19_3, stage19_4, stage19_5, stage19_6, stage19_7, stage19_8, stage19_9,
	stage20_0, stage20_1, stage20_2, stage20_3, stage20_4, stage20_5, stage20_6, stage20_7, stage20_8, stage20_9,
	stage21_0, stage21_1, stage21_2, stage21_3, stage21_4, stage21_5, stage21_6, stage21_7, stage21_8, stage21_9,
	stage22_0, stage22_1, stage22_2, stage22_3, stage22_4, stage22_5, stage22_6, stage22_7, stage22_8, stage22_9,
	stage23_0, stage23_1, stage23_2, stage23_3, stage23_4, stage23_5, stage23_6, stage23_7, stage23_8, stage23_9,
	stage24_0, stage24_1, stage24_2, stage24_3, stage24_4, stage24_5, stage24_6, stage24_7, stage24_8, stage24_9,
	stage25_0, stage25_1, stage25_2, stage25_3, stage25_4, stage25_5, stage25_6, stage25_7, stage25_8, stage25_9,
	stage26_0, stage26_1, stage26_2, stage26_3, stage26_4, stage26_5, stage26_6, stage26_7, stage26_8, stage26_9,
	stage27_0, stage27_1, stage27_2, stage27_3, stage27_4, stage27_5, stage27_6, stage27_7, stage27_8, stage27_9,
	stage28_0, stage28_1, stage28_2, stage28_3, stage28_4, stage28_5, stage28_6, stage28_7, stage28_8, stage28_9,
	stage29_0, stage29_1, stage29_2, stage29_3, stage29_4, stage29_5, stage29_6, stage29_7, stage29_8, stage29_9,
	stage30_0, stage30_1, stage30_2, stage30_3, stage30_4, stage30_5, stage30_6, stage30_7, stage30_8, stage30_9,
	stage31_0, stage31_1, stage31_2, stage31_3, stage31_4, stage31_5, stage31_6, stage31_7, stage31_8, stage31_9,
	stage32_0, stage32_1, stage32_2, stage32_3, stage32_4, stage32_5, stage32_6, stage32_7, stage32_8, stage32_9,
	stage33_0, stage33_1, stage33_2, stage33_3, stage33_4, stage33_5, stage33_6, stage33_7, stage33_8, stage33_9,
	stage34_0, stage34_1, stage34_2, stage34_3, stage34_4, stage34_5, stage34_6, stage34_7, stage34_8, stage34_9,
	stage35_0, stage35_1, stage35_2, stage35_3, stage35_4, stage35_5, stage35_6, stage35_7, stage35_8, stage35_9,
	stage36_0, stage36_1, stage36_2, stage36_3, stage36_4, stage36_5, stage36_6, stage36_7, stage36_8, stage36_9,
	stage37_0, stage37_1, stage37_2, stage37_3, stage37_4, stage37_5, stage37_6, stage37_7, stage37_8, stage37_9,
	stage38_0, stage38_1, stage38_2, stage38_3, stage38_4, stage38_5, stage38_6, stage38_7, stage38_8, stage38_9,
	stage39_0, stage39_1, stage39_2, stage39_3, stage39_4, stage39_5, stage39_6, stage39_7, stage39_8, stage39_9,
	stage40_0, stage40_1, stage40_2, stage40_3, stage40_4, stage40_5, stage40_6, stage40_7, stage40_8, stage40_9,
	stage41_0, stage41_1, stage41_2, stage41_3, stage41_4, stage41_5, stage41_6, stage41_7, stage41_8, stage41_9,
	stage42_0, stage42_1, stage42_2, stage42_3, stage42_4, stage42_5, stage42_6, stage42_7, stage42_8, stage42_9,
	stage43_0, stage43_1, stage43_2, stage43_3, stage43_4, stage43_5, stage43_6, stage43_7, stage43_8, stage43_9,
	stage44_0, stage44_1, stage44_2, stage44_3, stage44_4, stage44_5, stage44_6, stage44_7, stage44_8, stage44_9,
	stage45_0, stage45_1, stage45_2, stage45_3, stage45_4, stage45_5, stage45_6, stage45_7, stage45_8, stage45_9,
	stage46_0, stage46_1, stage46_2, stage46_3, stage46_4, stage46_5, stage46_6, stage46_7, stage46_8, stage46_9,
	stage47_0, stage47_1, stage47_2, stage47_3, stage47_4, stage47_5, stage47_6, stage47_7, stage47_8, stage47_9,
	stage48_0, stage48_1, stage48_2, stage48_3, stage48_4, stage48_5, stage48_6, stage48_7, stage48_8, stage48_9;
#pragma HLS DATAFLOW
	jacobi9d_soda(in0, in1, in2, in3, in4, in5, in6, in7, in8, in9, stage0_0, stage0_1, stage0_2, stage0_3, stage0_4, stage0_5, stage0_6, stage0_7, stage0_8, stage0_9);
	jacobi9d_soda(stage0_0, stage0_1, stage0_2, stage0_3, stage0_4, stage0_5, stage0_6, stage0_7, stage0_8, stage0_9, stage1_0, stage1_1, stage1_2, stage1_3, stage1_4, stage1_5, stage1_6, stage1_7, stage1_8, stage1_9);
	jacobi9d_soda(stage1_0, stage1_1, stage1_2, stage1_3, stage1_4, stage1_5, stage1_6, stage1_7, stage1_8, stage1_9, stage2_0, stage2_1, stage2_2, stage2_3, stage2_4, stage2_5, stage2_6, stage2_7, stage2_8, stage2_9);
	jacobi9d_soda(stage2_0, stage2_1, stage2_2, stage2_3, stage2_4, stage2_5, stage2_6, stage2_7, stage2_8, stage2_9, stage3_0, stage3_1, stage3_2, stage3_3, stage3_4, stage3_5, stage3_6, stage3_7, stage3_8, stage3_9);
	jacobi9d_soda(stage3_0, stage3_1, stage3_2, stage3_3, stage3_4, stage3_5, stage3_6, stage3_7, stage3_8, stage3_9, stage4_0, stage4_1, stage4_2, stage4_3, stage4_4, stage4_5, stage4_6, stage4_7, stage4_8, stage4_9);
	jacobi9d_soda(stage4_0, stage4_1, stage4_2, stage4_3, stage4_4, stage4_5, stage4_6, stage4_7, stage4_8, stage4_9, stage5_0, stage5_1, stage5_2, stage5_3, stage5_4, stage5_5, stage5_6, stage5_7, stage5_8, stage5_9);
	jacobi9d_soda(stage5_0, stage5_1, stage5_2, stage5_3, stage5_4, stage5_5, stage5_6, stage5_7, stage5_8, stage5_9, stage6_0, stage6_1, stage6_2, stage6_3, stage6_4, stage6_5, stage6_6, stage6_7, stage6_8, stage6_9);
	jacobi9d_soda(stage6_0, stage6_1, stage6_2, stage6_3, stage6_4, stage6_5, stage6_6, stage6_7, stage6_8, stage6_9, stage7_0, stage7_1, stage7_2, stage7_3, stage7_4, stage7_5, stage7_6, stage7_7, stage7_8, stage7_9);
	jacobi9d_soda(stage7_0, stage7_1, stage7_2, stage7_3, stage7_4, stage7_5, stage7_6, stage7_7, stage7_8, stage7_9, stage8_0, stage8_1, stage8_2, stage8_3, stage8_4, stage8_5, stage8_6, stage8_7, stage8_8, stage8_9);
	jacobi9d_soda(stage8_0, stage8_1, stage8_2, stage8_3, stage8_4, stage8_5, stage8_6, stage8_7, stage8_8, stage8_9, stage9_0, stage9_1, stage9_2, stage9_3, stage9_4, stage9_5, stage9_6, stage9_7, stage9_8, stage9_9);
	jacobi9d_soda(stage9_0, stage9_1, stage9_2, stage9_3, stage9_4, stage9_5, stage9_6, stage9_7, stage9_8, stage9_9, stage10_0, stage10_1, stage10_2, stage10_3, stage10_4, stage10_5, stage10_6, stage10_7, stage10_8, stage10_9);
	jacobi9d_soda(stage10_0, stage10_1, stage10_2, stage10_3, stage10_4, stage10_5, stage10_6, stage10_7, stage10_8, stage10_9, stage11_0, stage11_1, stage11_2, stage11_3, stage11_4, stage11_5, stage11_6, stage11_7, stage11_8, stage11_9);
	jacobi9d_soda(stage11_0, stage11_1, stage11_2, stage11_3, stage11_4, stage11_5, stage11_6, stage11_7, stage11_8, stage11_9, stage12_0, stage12_1, stage12_2, stage12_3, stage12_4, stage12_5, stage12_6, stage12_7, stage12_8, stage12_9);
	jacobi9d_soda(stage12_0, stage12_1, stage12_2, stage12_3, stage12_4, stage12_5, stage12_6, stage12_7, stage12_8, stage12_9, stage13_0, stage13_1, stage13_2, stage13_3, stage13_4, stage13_5, stage13_6, stage13_7, stage13_8, stage13_9);
	jacobi9d_soda(stage13_0, stage13_1, stage13_2, stage13_3, stage13_4, stage13_5, stage13_6, stage13_7, stage13_8, stage13_9, stage14_0, stage14_1, stage14_2, stage14_3, stage14_4, stage14_5, stage14_6, stage14_7, stage14_8, stage14_9);
	jacobi9d_soda(stage14_0, stage14_1, stage14_2, stage14_3, stage14_4, stage14_5, stage14_6, stage14_7, stage14_8, stage14_9, stage15_0, stage15_1, stage15_2, stage15_3, stage15_4, stage15_5, stage15_6, stage15_7, stage15_8, stage15_9);
	jacobi9d_soda(stage15_0, stage15_1, stage15_2, stage15_3, stage15_4, stage15_5, stage15_6, stage15_7, stage15_8, stage15_9, stage16_0, stage16_1, stage16_2, stage16_3, stage16_4, stage16_5, stage16_6, stage16_7, stage16_8, stage16_9);
	jacobi9d_soda(stage16_0, stage16_1, stage16_2, stage16_3, stage16_4, stage16_5, stage16_6, stage16_7, stage16_8, stage16_9, stage17_0, stage17_1, stage17_2, stage17_3, stage17_4, stage17_5, stage17_6, stage17_7, stage17_8, stage17_9);
	jacobi9d_soda(stage17_0, stage17_1, stage17_2, stage17_3, stage17_4, stage17_5, stage17_6, stage17_7, stage17_8, stage17_9, stage18_0, stage18_1, stage18_2, stage18_3, stage18_4, stage18_5, stage18_6, stage18_7, stage18_8, stage18_9);
	jacobi9d_soda(stage18_0, stage18_1, stage18_2, stage18_3, stage18_4, stage18_5, stage18_6, stage18_7, stage18_8, stage18_9, stage19_0, stage19_1, stage19_2, stage19_3, stage19_4, stage19_5, stage19_6, stage19_7, stage19_8, stage19_9);
	jacobi9d_soda(stage19_0, stage19_1, stage19_2, stage19_3, stage19_4, stage19_5, stage19_6, stage19_7, stage19_8, stage19_9, stage20_0, stage20_1, stage20_2, stage20_3, stage20_4, stage20_5, stage20_6, stage20_7, stage20_8, stage20_9);
	jacobi9d_soda(stage20_0, stage20_1, stage20_2, stage20_3, stage20_4, stage20_5, stage20_6, stage20_7, stage20_8, stage20_9, stage21_0, stage21_1, stage21_2, stage21_3, stage21_4, stage21_5, stage21_6, stage21_7, stage21_8, stage21_9);
	jacobi9d_soda(stage21_0, stage21_1, stage21_2, stage21_3, stage21_4, stage21_5, stage21_6, stage21_7, stage21_8, stage21_9, stage22_0, stage22_1, stage22_2, stage22_3, stage22_4, stage22_5, stage22_6, stage22_7, stage22_8, stage22_9);
	jacobi9d_soda(stage22_0, stage22_1, stage22_2, stage22_3, stage22_4, stage22_5, stage22_6, stage22_7, stage22_8, stage22_9, stage23_0, stage23_1, stage23_2, stage23_3, stage23_4, stage23_5, stage23_6, stage23_7, stage23_8, stage23_9);
	jacobi9d_soda(stage23_0, stage23_1, stage23_2, stage23_3, stage23_4, stage23_5, stage23_6, stage23_7, stage23_8, stage23_9, stage24_0, stage24_1, stage24_2, stage24_3, stage24_4, stage24_5, stage24_6, stage24_7, stage24_8, stage24_9);
	jacobi9d_soda(stage24_0, stage24_1, stage24_2, stage24_3, stage24_4, stage24_5, stage24_6, stage24_7, stage24_8, stage24_9, stage25_0, stage25_1, stage25_2, stage25_3, stage25_4, stage25_5, stage25_6, stage25_7, stage25_8, stage25_9);
	jacobi9d_soda(stage25_0, stage25_1, stage25_2, stage25_3, stage25_4, stage25_5, stage25_6, stage25_7, stage25_8, stage25_9, stage26_0, stage26_1, stage26_2, stage26_3, stage26_4, stage26_5, stage26_6, stage26_7, stage26_8, stage26_9);
	jacobi9d_soda(stage26_0, stage26_1, stage26_2, stage26_3, stage26_4, stage26_5, stage26_6, stage26_7, stage26_8, stage26_9, stage27_0, stage27_1, stage27_2, stage27_3, stage27_4, stage27_5, stage27_6, stage27_7, stage27_8, stage27_9);
	jacobi9d_soda(stage27_0, stage27_1, stage27_2, stage27_3, stage27_4, stage27_5, stage27_6, stage27_7, stage27_8, stage27_9, stage28_0, stage28_1, stage28_2, stage28_3, stage28_4, stage28_5, stage28_6, stage28_7, stage28_8, stage28_9);
	jacobi9d_soda(stage28_0, stage28_1, stage28_2, stage28_3, stage28_4, stage28_5, stage28_6, stage28_7, stage28_8, stage28_9, stage29_0, stage29_1, stage29_2, stage29_3, stage29_4, stage29_5, stage29_6, stage29_7, stage29_8, stage29_9);
	jacobi9d_soda(stage29_0, stage29_1, stage29_2, stage29_3, stage29_4, stage29_5, stage29_6, stage29_7, stage29_8, stage29_9, stage30_0, stage30_1, stage30_2, stage30_3, stage30_4, stage30_5, stage30_6, stage30_7, stage30_8, stage30_9);
	jacobi9d_soda(stage30_0, stage30_1, stage30_2, stage30_3, stage30_4, stage30_5, stage30_6, stage30_7, stage30_8, stage30_9, stage31_0, stage31_1, stage31_2, stage31_3, stage31_4, stage31_5, stage31_6, stage31_7, stage31_8, stage31_9);
	jacobi9d_soda(stage31_0, stage31_1, stage31_2, stage31_3, stage31_4, stage31_5, stage31_6, stage31_7, stage31_8, stage31_9, stage32_0, stage32_1, stage32_2, stage32_3, stage32_4, stage32_5, stage32_6, stage32_7, stage32_8, stage32_9);
	jacobi9d_soda(stage32_0, stage32_1, stage32_2, stage32_3, stage32_4, stage32_5, stage32_6, stage32_7, stage32_8, stage32_9, stage33_0, stage33_1, stage33_2, stage33_3, stage33_4, stage33_5, stage33_6, stage33_7, stage33_8, stage33_9);
	jacobi9d_soda(stage33_0, stage33_1, stage33_2, stage33_3, stage33_4, stage33_5, stage33_6, stage33_7, stage33_8, stage33_9, stage34_0, stage34_1, stage34_2, stage34_3, stage34_4, stage34_5, stage34_6, stage34_7, stage34_8, stage34_9);
	jacobi9d_soda(stage34_0, stage34_1, stage34_2, stage34_3, stage34_4, stage34_5, stage34_6, stage34_7, stage34_8, stage34_9, stage35_0, stage35_1, stage35_2, stage35_3, stage35_4, stage35_5, stage35_6, stage35_7, stage35_8, stage35_9);
	jacobi9d_soda(stage35_0, stage35_1, stage35_2, stage35_3, stage35_4, stage35_5, stage35_6, stage35_7, stage35_8, stage35_9, stage36_0, stage36_1, stage36_2, stage36_3, stage36_4, stage36_5, stage36_6, stage36_7, stage36_8, stage36_9);
	jacobi9d_soda(stage36_0, stage36_1, stage36_2, stage36_3, stage36_4, stage36_5, stage36_6, stage36_7, stage36_8, stage36_9, stage37_0, stage37_1, stage37_2, stage37_3, stage37_4, stage37_5, stage37_6, stage37_7, stage37_8, stage37_9);
	jacobi9d_soda(stage37_0, stage37_1, stage37_2, stage37_3, stage37_4, stage37_5, stage37_6, stage37_7, stage37_8, stage37_9, stage38_0, stage38_1, stage38_2, stage38_3, stage38_4, stage38_5, stage38_6, stage38_7, stage38_8, stage38_9);
	jacobi9d_soda(stage38_0, stage38_1, stage38_2, stage38_3, stage38_4, stage38_5, stage38_6, stage38_7, stage38_8, stage38_9, stage39_0, stage39_1, stage39_2, stage39_3, stage39_4, stage39_5, stage39_6, stage39_7, stage39_8, stage39_9);
	jacobi9d_soda(stage39_0, stage39_1, stage39_2, stage39_3, stage39_4, stage39_5, stage39_6, stage39_7, stage39_8, stage39_9, stage40_0, stage40_1, stage40_2, stage40_3, stage40_4, stage40_5, stage40_6, stage40_7, stage40_8, stage40_9);
	jacobi9d_soda(stage40_0, stage40_1, stage40_2, stage40_3, stage40_4, stage40_5, stage40_6, stage40_7, stage40_8, stage40_9, stage41_0, stage41_1, stage41_2, stage41_3, stage41_4, stage41_5, stage41_6, stage41_7, stage41_8, stage41_9);
	jacobi9d_soda(stage41_0, stage41_1, stage41_2, stage41_3, stage41_4, stage41_5, stage41_6, stage41_7, stage41_8, stage41_9, stage42_0, stage42_1, stage42_2, stage42_3, stage42_4, stage42_5, stage42_6, stage42_7, stage42_8, stage42_9);
	jacobi9d_soda(stage42_0, stage42_1, stage42_2, stage42_3, stage42_4, stage42_5, stage42_6, stage42_7, stage42_8, stage42_9, stage43_0, stage43_1, stage43_2, stage43_3, stage43_4, stage43_5, stage43_6, stage43_7, stage43_8, stage43_9);
	jacobi9d_soda(stage43_0, stage43_1, stage43_2, stage43_3, stage43_4, stage43_5, stage43_6, stage43_7, stage43_8, stage43_9, stage44_0, stage44_1, stage44_2, stage44_3, stage44_4, stage44_5, stage44_6, stage44_7, stage44_8, stage44_9);
	jacobi9d_soda(stage44_0, stage44_1, stage44_2, stage44_3, stage44_4, stage44_5, stage44_6, stage44_7, stage44_8, stage44_9, stage45_0, stage45_1, stage45_2, stage45_3, stage45_4, stage45_5, stage45_6, stage45_7, stage45_8, stage45_9);
	jacobi9d_soda(stage45_0, stage45_1, stage45_2, stage45_3, stage45_4, stage45_5, stage45_6, stage45_7, stage45_8, stage45_9, stage46_0, stage46_1, stage46_2, stage46_3, stage46_4, stage46_5, stage46_6, stage46_7, stage46_8, stage46_9);
	jacobi9d_soda(stage46_0, stage46_1, stage46_2, stage46_3, stage46_4, stage46_5, stage46_6, stage46_7, stage46_8, stage46_9, stage47_0, stage47_1, stage47_2, stage47_3, stage47_4, stage47_5, stage47_6, stage47_7, stage47_8, stage47_9);
	jacobi9d_soda(stage47_0, stage47_1, stage47_2, stage47_3, stage47_4, stage47_5, stage47_6, stage47_7, stage47_8, stage47_9, stage48_0, stage48_1, stage48_2, stage48_3, stage48_4, stage48_5, stage48_6, stage48_7, stage48_8, stage48_9);
	jacobi9d_soda(stage48_0, stage48_1, stage48_2, stage48_3, stage48_4, stage48_5, stage48_6, stage48_7, stage48_8, stage48_9, out0, out1, out2, out3, out4, out5, out6, out7, out8, out9);
}
