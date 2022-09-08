/************************
9-Point Jacobi 2-D SODA
K=3: Three Reuse Chains
*************************/
#include "SODA_Jacobi.h"

#define PRAGMA_SUB(x) _Pragma (#x)
#define DO_PRAGMA(x) PRAGMA_SUB(x)

void jacobi9d_soda(
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
){
	const mat coeff=1.0f/9.0f;
	int FIFO_WIDTH=WIDTH/k; //Should be a perfect division
	hls::stream<mat> fifo_inter_a0("fifo_inter_a0"), fifo_inter_a1("fifo_inter_a1"),
			fifo_inter_b0("fifo_inter_b0"),fifo_inter_b1("fifo_inter_b1"),
			fifo_inter_c0("fifo_inter_c0"),fifo_inter_c1("fifo_inter_c1"),
			fifo_inter_d0("fifo_inter_d0"),fifo_inter_d1("fifo_inter_d1"),
			fifo_inter_e0("fifo_inter_e0"),fifo_inter_e1("fifo_inter_e1"),
			fifo_inter_f0("fifo_inter_f0"),fifo_inter_f1("fifo_inter_f1"),
			fifo_inter_g0("fifo_inter_g0"),fifo_inter_g1("fifo_inter_g1"),
			fifo_inter_h0("fifo_inter_h0"),fifo_inter_h1("fifo_inter_h1");
	hls::stream<mat> fifo_edge_k0 ("fifo_k0"), fifo_edge_k1 ("fifo_k1"), fifo_edge_00 ("fifo_00"), fifo_edge_01 ("fifo_k1");
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_inter_a0)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_inter_a1)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_inter_b0)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_inter_b1)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_inter_c0)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_inter_c1)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_inter_d0)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_inter_d1)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_inter_e0)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_inter_e1)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_inter_f0)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_inter_f1)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_inter_g0)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_inter_g1)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_inter_h0)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_inter_h1)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_edge_k0)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_edge_k1)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_edge_00)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_edge_01)
	mat ff_edge_0[5],ff_edge_k[5],start[k],ff_inter_a[5],ff_inter_b[5],ff_inter_c[5],ff_inter_d[5],ff_inter_e[5],ff_inter_f[5],ff_inter_g[5],ff_inter_h[5],result[k]; //={0}
#pragma HLS ARRAY_PARTITION variable=ff_edge_0 complete dim=1
#pragma HLS ARRAY_PARTITION variable=ff_edge_k complete dim=1
#pragma HLS ARRAY_PARTITION variable=start complete dim=1
#pragma HLS ARRAY_PARTITION variable=ff_inter_a complete dim=1
#pragma HLS ARRAY_PARTITION variable=ff_inter_b complete dim=1
#pragma HLS ARRAY_PARTITION variable=ff_inter_d complete dim=1
#pragma HLS ARRAY_PARTITION variable=ff_inter_e complete dim=1
#pragma HLS ARRAY_PARTITION variable=ff_inter_f complete dim=1
#pragma HLS ARRAY_PARTITION variable=ff_inter_g complete dim=1
#pragma HLS ARRAY_PARTITION variable=ff_inter_h complete dim=1
	Row: for (int i=-1; i<HEIGHT; i++){
		Col: for (int j=-1; j<WIDTH-1; j+=k){
#pragma HLS PIPELINE
			ReChain: for (int v=0;v<k;v++){//Iterate with step=k
#pragma HLS UNROLL
			//REUSE CHAIN k-1 (v=0 ||v=k)
				//The First and Last Reuse Chain have a different layout than the rest
				if (v==1){ // Intermediate values: mod==k-3
					ff_edge_0[4]=ff_edge_0[3];
					if((i+1)*WIDTH+j+1>2*WIDTH-1){ //Only read when full
						fifo_edge_01.read(ff_edge_0[3]);
					}
					if((i+1)*WIDTH+j+1>WIDTH+k && (i+1)*WIDTH+j+1<HEIGHT*WIDTH+2*k){
						fifo_edge_01.write(ff_edge_0[2]);
					}
					ff_edge_0[2]=ff_edge_0[1];
					if((i+1)*WIDTH+j+1>WIDTH-1){ //Only read when full
						fifo_edge_00.read(ff_edge_0[1]);
					}
					if((i+1)*WIDTH+j+1>k && (i+1)*WIDTH+j+1<HEIGHT*WIDTH+2*k){
						fifo_edge_00.write(ff_edge_0[0]);
					}
					ff_edge_0[0]=start[v-1];
					if (i<HEIGHT-1){
						in0.read(start[v-1]);
					}
				}
					//REUSE CHAIN k-1 (v=-1 || v=k-1)
				else if (v==0){ // Intermediate values: mod==k-1
					ff_edge_k[4]=ff_edge_k[3];
					if((i+1)*WIDTH+j+1>2*WIDTH-1){
						fifo_edge_k1.read(ff_edge_k[3]);
					}
					if((i+1)*WIDTH+j+1>WIDTH+k && (i+1)*WIDTH+j+1<HEIGHT*WIDTH+2*k){
						fifo_edge_k1.write(ff_edge_k[2]);
					}
					ff_edge_k[2]=ff_edge_k[1];
					if((i+1)*WIDTH+j+1>WIDTH-1){
						fifo_edge_k0.read(ff_edge_k[1]);
					}
					if((i+1)*WIDTH+j+1>k && (i+1)*WIDTH+j+1<HEIGHT*WIDTH+2*k){
						fifo_edge_k0.write(ff_edge_k[0]);
					}
					ff_edge_k[0]=start[k-1];
					if (i<HEIGHT-1){
						in9.read(start[k-1]);
					}
				}
				else if (v==9){ // // Intermediate values: mod==k-2
					ff_inter_h[4]=ff_inter_h[3];
					//SECOND FIFO
					if((i+1)*WIDTH+j+1>2*WIDTH-1){
						fifo_inter_h1.read(ff_inter_h[3]);
					}
					if((i+1)*WIDTH+j+1>WIDTH+k && (i+1)*WIDTH+j+1<HEIGHT*WIDTH+2*k){
						fifo_inter_h1.write(ff_inter_h[2]);
					}
					//INTERMEDIATE REUSE CHAINS (FIRST FIFO)
					ff_inter_h[2]=ff_inter_h[1];
					if((i+1)*WIDTH+j+1>WIDTH-1){
						fifo_inter_h0.read(ff_inter_h[1]); //For the Intermediate Reuse Chains
					}
					if((i+1)*WIDTH+j+1>k && (i+1)*WIDTH+j+1<HEIGHT*WIDTH+2*k){
						fifo_inter_h0.write(ff_inter_h[0]);
					}
					ff_inter_h[0]=start[v-1];
					if (i<HEIGHT-1){
						in8.read(start[v-1]);
					}
				}
				else if (v==8){ // // Intermediate values: mod==k-2
					ff_inter_g[4]=ff_inter_g[3];
					//SECOND FIFO
					if((i+1)*WIDTH+j+1>2*WIDTH-1){
						fifo_inter_g1.read(ff_inter_g[3]);
					}
					if((i+1)*WIDTH+j+1>WIDTH+k && (i+1)*WIDTH+j+1<HEIGHT*WIDTH+2*k){
						fifo_inter_g1.write(ff_inter_g[2]);
					}
					//INTERMEDIATE REUSE CHAINS (FIRST FIFO)
					ff_inter_g[2]=ff_inter_g[1];
					if((i+1)*WIDTH+j+1>WIDTH-1){
						fifo_inter_g0.read(ff_inter_g[1]); //For the Intermediate Reuse Chains
					}
					if((i+1)*WIDTH+j+1>k && (i+1)*WIDTH+j+1<HEIGHT*WIDTH+2*k){
						fifo_inter_g0.write(ff_inter_g[0]);
					}
					ff_inter_g[0]=start[v-1];
					if (i<HEIGHT-1){
						in7.read(start[v-1]);
					}
				}
				else if (v==7){ // // Intermediate values: mod==k-2
					ff_inter_f[4]=ff_inter_f[3];
					//SECOND FIFO
					if((i+1)*WIDTH+j+1>2*WIDTH-1){
						fifo_inter_f1.read(ff_inter_f[3]);
					}
					if((i+1)*WIDTH+j+1>WIDTH+k && (i+1)*WIDTH+j+1<HEIGHT*WIDTH+2*k){
						fifo_inter_f1.write(ff_inter_f[2]);
					}
					//INTERMEDIATE REUSE CHAINS (FIRST FIFO)
					ff_inter_f[2]=ff_inter_f[1];
					if((i+1)*WIDTH+j+1>WIDTH-1){
						fifo_inter_f0.read(ff_inter_f[1]); //For the Intermediate Reuse Chains
					}
					if((i+1)*WIDTH+j+1>k && (i+1)*WIDTH+j+1<HEIGHT*WIDTH+2*k){
						fifo_inter_f0.write(ff_inter_f[0]);
					}
					ff_inter_f[0]=start[v-1];
					if (i<HEIGHT-1){
						in6.read(start[v-1]);
					}
				}
				else if (v==6){ // // Intermediate values: mod==k-2
					ff_inter_e[4]=ff_inter_e[3];
					//SECOND FIFO
					if((i+1)*WIDTH+j+1>2*WIDTH-1){
						fifo_inter_e1.read(ff_inter_e[3]);
					}
					if((i+1)*WIDTH+j+1>WIDTH+k && (i+1)*WIDTH+j+1<HEIGHT*WIDTH+2*k){
						fifo_inter_e1.write(ff_inter_e[2]);
					}
					//INTERMEDIATE REUSE CHAINS (FIRST FIFO)
					ff_inter_e[2]=ff_inter_e[1];
					if((i+1)*WIDTH+j+1>WIDTH-1){
						fifo_inter_e0.read(ff_inter_e[1]); //For the Intermediate Reuse Chains
					}
					if((i+1)*WIDTH+j+1>k && (i+1)*WIDTH+j+1<HEIGHT*WIDTH+2*k){
						fifo_inter_e0.write(ff_inter_e[0]);
					}
					ff_inter_e[0]=start[v-1];
					if (i<HEIGHT-1){
						in5.read(start[v-1]);
					}
				}
				else if (v==5){ // // Intermediate values: mod==k-2
					ff_inter_d[4]=ff_inter_d[3];
					//SECOND FIFO
					if((i+1)*WIDTH+j+1>2*WIDTH-1){
						fifo_inter_d1.read(ff_inter_d[3]);
					}
					if((i+1)*WIDTH+j+1>WIDTH+k && (i+1)*WIDTH+j+1<HEIGHT*WIDTH+2*k){
						fifo_inter_d1.write(ff_inter_d[2]);
					}
					//INTERMEDIATE REUSE CHAINS (FIRST FIFO)
					ff_inter_d[2]=ff_inter_d[1];
					if((i+1)*WIDTH+j+1>WIDTH-1){
						fifo_inter_d0.read(ff_inter_d[1]); //For the Intermediate Reuse Chains
					}
					if((i+1)*WIDTH+j+1>k && (i+1)*WIDTH+j+1<HEIGHT*WIDTH+2*k){
						fifo_inter_d0.write(ff_inter_d[0]);
					}
					ff_inter_d[0]=start[v-1];
					if (i<HEIGHT-1){
						in4.read(start[v-1]);
					}
				}
				else if (v==4){ // // Intermediate values: mod==k-2
					ff_inter_c[4]=ff_inter_c[3];
					//SECOND FIFO
					if((i+1)*WIDTH+j+1>2*WIDTH-1){
						fifo_inter_c1.read(ff_inter_c[3]);
					}
					if((i+1)*WIDTH+j+1>WIDTH+k && (i+1)*WIDTH+j+1<HEIGHT*WIDTH+2*k){
						fifo_inter_c1.write(ff_inter_c[2]);
					}
					//INTERMEDIATE REUSE CHAINS (FIRST FIFO)
					ff_inter_c[2]=ff_inter_c[1];
					if((i+1)*WIDTH+j+1>WIDTH-1){
						fifo_inter_c0.read(ff_inter_c[1]); //For the Intermediate Reuse Chains
					}
					if((i+1)*WIDTH+j+1>k && (i+1)*WIDTH+j+1<HEIGHT*WIDTH+2*k){
						fifo_inter_c0.write(ff_inter_c[0]);
					}
					ff_inter_c[0]=start[v-1];
					if (i<HEIGHT-1){
						in3.read(start[v-1]);
					}
				}
				else if (v==3){ // Intermediate values: mod==k-3
					ff_inter_b[4]=ff_inter_b[3];
					//SECOND FIFO
					if((i+1)*WIDTH+j+1>2*WIDTH-1){
						fifo_inter_b1.read(ff_inter_b[3]);
					}
					if((i+1)*WIDTH+j+1>WIDTH+k && (i+1)*WIDTH+j+1<HEIGHT*WIDTH+2*k){
						fifo_inter_b1.write(ff_inter_b[2]);
					}
					//INTERMEDIATE REUSE CHAINS (FIRST FIFO)
					ff_inter_b[2]=ff_inter_b[1];
					if((i+1)*WIDTH+j+1>WIDTH-1){
						fifo_inter_b0.read(ff_inter_b[1]); //For the Intermediate Reuse Chains
					}
					if((i+1)*WIDTH+j+1>k && (i+1)*WIDTH+j+1<HEIGHT*WIDTH+2*k){
						fifo_inter_b0.write(ff_inter_b[0]);
					}
					ff_inter_b[0]=start[v-1];
					if (i<HEIGHT-1){
						in2.read(start[v-1]);
					}
				}
				else { // Intermediate values: 0<modulo<(k-1)
					ff_inter_a[4]=ff_inter_a[3];
					//SECOND FIFO
					if((i+1)*WIDTH+j+1>2*WIDTH-1){
						fifo_inter_a1.read(ff_inter_a[3]);
					}
					if((i+1)*WIDTH+j+1>WIDTH+k && (i+1)*WIDTH+j+1<HEIGHT*WIDTH+2*k){
						fifo_inter_a1.write(ff_inter_a[2]);
					}
					//INTERMEDIATE REUSE CHAINS (FIRST FIFO)
					ff_inter_a[2]=ff_inter_a[1];
					if((i+1)*WIDTH+j+1>WIDTH-1){
						fifo_inter_a0.read(ff_inter_a[1]); //For the Intermediate Reuse Chains
					}
					//if(i*WIDTH+j>-WIDTH+k+1 && i*WIDTH+j<(HEIGHT-1)*(WIDTH-1)+2*k+1){
					if((i+1)*WIDTH+j+1>k && (i+1)*WIDTH+j+1<HEIGHT*WIDTH+2*k){
						fifo_inter_a0.write(ff_inter_a[0]);
					}
					ff_inter_a[0]=start[v-1];
					if (i<HEIGHT-1){
						in1.read(start[v-1]);
					}
				}
			}
			result[9]=coeff*(start[0]+ff_edge_0[1]+ff_edge_0[3]+ff_inter_h[0]+ff_inter_h[2]+ff_inter_h[4]+start[9]+ff_edge_k[1]+ff_edge_k[3]);
			result[0]=coeff*(start[9]+ff_edge_k[1]+ff_edge_k[3]+start[1]+ff_inter_a[1]+ff_inter_a[3]+start[0]+ff_edge_0[1]+ff_edge_0[3]);
			result[1]=coeff*(start[0]+ff_edge_0[1]+ff_edge_0[3]+start[1]+ff_inter_a[1]+ff_inter_a[3]+start[2]+ff_inter_b[1]+ff_inter_b[3]);
			result[2]=coeff*(start[3]+ff_inter_c[1]+ff_inter_c[3]+start[1]+ff_inter_a[1]+ff_inter_a[3]+start[2]+ff_inter_b[1]+ff_inter_b[3]);
			result[3]=coeff*(start[3]+ff_inter_c[1]+ff_inter_c[3]+start[4]+ff_inter_d[1]+ff_inter_d[3]+start[2]+ff_inter_b[1]+ff_inter_b[3]);
			result[4]=coeff*(start[3]+ff_inter_c[1]+ff_inter_c[3]+start[4]+ff_inter_d[1]+ff_inter_d[3]+start[5]+ff_inter_e[1]+ff_inter_e[3]);
			result[5]=coeff*(start[6]+ff_inter_f[1]+ff_inter_f[3]+start[4]+ff_inter_d[1]+ff_inter_d[3]+start[5]+ff_inter_e[1]+ff_inter_e[3]);
			result[6]=coeff*(start[6]+ff_inter_f[1]+ff_inter_f[3]+start[7]+ff_inter_g[1]+ff_inter_g[3]+start[5]+ff_inter_e[1]+ff_inter_e[3]);
			result[7]=coeff*(start[6]+ff_inter_f[1]+ff_inter_f[3]+start[7]+ff_inter_g[1]+ff_inter_g[3]+start[8]+ff_inter_h[1]+ff_inter_h[3]);
			result[8]=coeff*(ff_inter_g[0]+ff_inter_g[2]+ff_inter_g[4]+ff_inter_h[0]+ff_inter_h[2]+ff_inter_h[4]+start[9]+ff_edge_k[1]+ff_edge_k[3]);
			if (i==0){ //HALO First Line
				if (j==-1){
					out9.write(ff_edge_k[1]);
					out0.write(ff_edge_0[1]);
					out1.write(ff_inter_a[1]);
					out2.write(ff_inter_b[1]);
					out3.write(ff_inter_c[1]);
					out4.write(ff_inter_d[1]);
					out5.write(ff_inter_e[1]);
					out6.write(ff_inter_f[1]);
					out7.write(ff_inter_g[1]);
					//out8.write_nb(ff_inter_h[1]);
				}
				else {
					out1.write(ff_inter_a[1]);
					out2.write(ff_inter_b[1]);
					out3.write(ff_inter_c[1]);
					out4.write(ff_inter_d[1]);
					out5.write(ff_inter_e[1]);
					out6.write(ff_inter_f[1]);
					out7.write(ff_inter_g[1]);
					out8.write(ff_inter_h[2]);
					out9.write(ff_edge_k[1]);
					out0.write(ff_edge_0[1]);
				}
			}
			else if(i==HEIGHT-1){//HALO Last Line
				out1.write(ff_inter_a[1]);
				out2.write(ff_inter_b[1]);
				out3.write(ff_inter_c[1]);
				out4.write(ff_inter_d[1]);
				out5.write(ff_inter_e[1]);
				out6.write(ff_inter_f[1]);
				out7.write(ff_inter_g[1]);
				out8.write(ff_inter_h[2]);
				out9.write(ff_edge_k[1]);
				out0.write(ff_edge_0[1]);
			}
			else if (i>0){
				if (j==-1){//HALO elements
					//if(i>1){ //For i==1 the HALO(i-1,j=WIDTH-2) was already written to out1
					out8.write(ff_inter_h[2]);//HALO(i-1,j=WIDTH-2)
					//}
					out9.write(ff_edge_k[1]);//HALO (i,j=-1)
					out0.write(result[0]);
					out1.write(result[1]);
					out2.write(result[2]);
					out3.write(result[3]);
					out4.write(result[4]);
					out5.write(result[5]);
					out6.write(result[6]);
					out7.write(result[7]);
				}
				else{
					out8.write(result[8]);
					out9.write(result[9]);
					out0.write(result[0]);
					out1.write(result[1]);
					out2.write(result[2]);
					out3.write(result[3]);
					out4.write(result[4]);
					out5.write(result[5]);
					out6.write(result[6]);
					out7.write(result[7]);
				}
			}
		}
	}
	out8.write(ff_inter_h[1]);
}

