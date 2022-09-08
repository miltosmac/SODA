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
		hls::stream <mat> &out0,
		hls::stream <mat> &out1,
		hls::stream <mat> &out2,
		hls::stream <mat> &out3,
		hls::stream <mat> &out4
){
	const mat coeff=1.0f/9.0f;
	int FIFO_WIDTH=WIDTH/k; //Should be a perfect division
	hls::stream<mat> fifo_inter_a0("fifo_inter_a0"), fifo_inter_a1("fifo_inter_a1"),fifo_inter_b0("fifo_inter_b0"), fifo_inter_b1("fifo_inter_b1"),fifo_inter_c0("fifo_inter_c0"), fifo_inter_c1("fifo_inter_c1");;
	hls::stream<mat> fifo_edge_k0 ("fifo_k0"), fifo_edge_k1 ("fifo_k1"), fifo_edge_00 ("fifo_00"), fifo_edge_01 ("fifo_k1");
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_inter_a0)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_inter_a1)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_inter_b0)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_inter_b1)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_inter_c0)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_inter_c1)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_edge_k0)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_edge_k1)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_edge_00)
	DO_PRAGMA(HLS stream depth=FIFO_DEPTH variable=fifo_edge_01)
	mat ff_edge_0[5],ff_edge_k[5],start[k],ff_inter_a[5],ff_inter_b[5],ff_inter_c[5],result[k]; //={0}
#pragma HLS ARRAY_PARTITION variable=ff_edge_0 complete dim=1
#pragma HLS ARRAY_PARTITION variable=ff_edge_k complete dim=1
#pragma HLS ARRAY_PARTITION variable=start complete dim=1
#pragma HLS ARRAY_PARTITION variable=ff_inter_a complete dim=1
#pragma HLS ARRAY_PARTITION variable=result complete dim=1
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
						in4.read(start[k-1]);
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

			result[4]=coeff*(start[0]+ff_edge_0[1]+ff_edge_0[3]+ff_inter_c[0]+ff_inter_c[2]+ff_inter_c[4]+start[4]+ff_edge_k[1]+ff_edge_k[3]);

			result[0]=coeff*(start[4]+ff_edge_k[1]+ff_edge_k[3]+start[1]+ff_inter_a[1]+ff_inter_a[3]+start[0]+ff_edge_0[1]+ff_edge_0[3]);

			result[1]=coeff*(start[0]+ff_edge_0[1]+ff_edge_0[3]+start[1]+ff_inter_a[1]+ff_inter_a[3]+start[2]+ff_inter_b[1]+ff_inter_b[3]);

			result[2]=coeff*(start[3]+ff_inter_c[1]+ff_inter_c[3]+start[1]+ff_inter_a[1]+ff_inter_a[3]+start[2]+ff_inter_b[1]+ff_inter_b[3]);

			result[3]=coeff*(start[4]+ff_edge_k[1]+ff_edge_k[3]+ff_inter_c[0]+ff_inter_c[2]+ff_inter_c[4]+ff_inter_b[0]+ff_inter_b[2]+ff_inter_b[4]);

			if (i==0){ //HALO First Line
				if (j==-1){
					out4.write(ff_edge_k[1]);
					out0.write(ff_edge_0[1]);
					out1.write(ff_inter_a[1]);
					out2.write(ff_inter_b[1]);
					//out3.write_nb(ff_inter_c[1]);
				}
				else {
					out4.write(ff_edge_k[1]);
					out0.write(ff_edge_0[1]);
					out1.write(ff_inter_a[1]);
					out2.write(ff_inter_b[1]);
					out3.write(ff_inter_c[2]);
				}
			}
			else if(i==HEIGHT-1){//HALO Last Line
				out1.write(ff_inter_a[1]);
				out2.write(ff_inter_b[1]);
				out3.write(ff_inter_c[2]);
				out4.write(ff_edge_k[1]);
				out0.write(ff_edge_0[1]);
			}
			else if (i>0){
				if (j==-1){//HALO elements
					//if(i>1){ //For i==1 the HALO(i-1,j=WIDTH-2) was already written to out1
						out3.write(ff_inter_c[2]);//HALO(i-1,j=WIDTH-2)
					//}
					out4.write(ff_edge_k[1]);//HALO (i,j=-1)
					out0.write(result[0]);
					out1.write(result[1]);
					out2.write(result[2]);
				}
				else{
					out3.write(result[3]);
					out4.write(result[4]);
					out0.write(result[0]);
					out1.write(result[1]);
					out2.write(result[2]);
				}
			}
		}
	}
	out3.write(ff_inter_c[1]);
}

