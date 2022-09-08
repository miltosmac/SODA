#include <iostream>
#include <math.h>
#include <fstream>
#include "SODA_Jacobi.h"

using namespace std;

int main(int argc, char **argv)
{
	const mat coeff=1.0f/9.0f;
	mat temp;
	int err_cnt = 0;
	mat mult;
	int modulo;

	auto A=new mat[HEIGHT][WIDTH];
	auto sw_result = new mat[HEIGHT][WIDTH];

	hls::stream<mat> testream_in_0("instream_0"),testream_in_1("instream_1"),testream_in_2("instream_2"),testream_in_3("instream_3"),testream_in_4("instream_4");
	hls::stream<mat> testream_out_0("outstream_0"),testream_out_1("outstream_1"),testream_out_2("outstream_2"),testream_out_3("outstream_3"),testream_out_4("outstream_4");
	ofstream txtfile;
	txtfile.open ("input_mat.txt");
	ofstream mytxt;
	mytxt.open("out_mat.txt");
	for (int i=0; i<HEIGHT;i++){
		for(int j=0; j<WIDTH; j++){
			//mult=mat(rand());
			A[i][j]= mat(rand())/mat(RAND_MAX/100.0f); //Initialize A matrix as random floats
			//A[i][j] = static_cast <mat>(i * WIDTH + j);
			txtfile << A[i][j]<<"  ";
			modulo = ((j-1)%k +k)%k;
			if(modulo==2){
				testream_in_2.write(A[i][j]);
			}
			else if(modulo==1){
				testream_in_1.write(A[i][j]);
			}
			else {
				testream_in_0.write(A[i][j]);
			}
		}
		txtfile <<"\n";
	}
	txtfile.close();
	//Generate the expected results
	//Iterate over the rows of the 2D input matrix
	for (int t=0; t<ts; t++){
		for (int i=0; i<HEIGHT; i++){
			//Iterate the columns of the 2D input matrix
			for (int j=0; j<WIDTH; j++){
				if (i>0 && i < HEIGHT-1 && j>0 && j < WIDTH-1){
					temp= A[i-1][j-1]+A[i-1][j]+A[i-1][j+1]+ // First Line
						A[i][j-1]+A[i][j]+A[i][j+1]+      // Second Line
						A[i+1][j-1]+A[i+1][j]+A[i+1][j+1];   // Third Line
					sw_result[i][j]=coeff*temp; //Create SW result*//
				}else {
					sw_result[i][j]=A[i][j]; //Results for the HALO
				}
			}
		}
		for (int i=0; i<HEIGHT; i++){
			for (int j=0; j<WIDTH; j++){
				A[i][j]=sw_result[i][j];
			}
		}
	}
	delete []A;
	auto hw_result = new mat[HEIGHT][WIDTH];
	// Calculate TCAD Result
	temporal(testream_in_0,testream_in_1,testream_in_2,testream_out_0,testream_out_1,testream_out_2);
	for (int i=0; i<HEIGHT; i++){
		for (int j=0; j<WIDTH; j++){
		// Check HW result against SW
			//if (i>0 && i<HEIGHT-1 && j>0 && j<WIDTH-1){
			modulo = ((j-1)%k +k)%k;
			if(modulo==2){//Values read from stream and into the HW result variable for checking
				testream_out_2.read(hw_result[i][j]);
				}
			else if(modulo==1){
				testream_out_1.read(hw_result[i][j]);
				}
			else {
				testream_out_0.read(hw_result[i][j]);
				}
			mytxt << hw_result[i][j]<<" ";
			if (fabs(float(hw_result[i][j] - sw_result[i][j]))>1e-2f) { //Just checking the Kernel results not the full size matrix with the HALO
				cout << "At iteration i:" << i << " and j:" <<j << endl;
				err_cnt++;
			}
		}
		mytxt <<"\n";
	}
	mytxt.close();
	txtfile.close();
	delete []hw_result;
	delete []sw_result;

	if (err_cnt){
		cout << "ERROR: " << err_cnt << " mismatches detected!" << endl;
	}else{
		cout << "Test passes." << endl;
	}

}
