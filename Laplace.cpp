#include <iostream>
using namespace std;
#include <math.h>
#include <cstring>
#include<cmath>
#include <fstream>

int main() 
{

	streamsize ss = std::cout.precision();	
	
	
	int nx,ny;
	float Lx,Ly,del_x, del_y;
	float  TB, BB, LB, RB;
	int count_J, count_GS;
	float e1_norm_J, e1_norm_GS,tol;
	
	ofstream GS_output,J_output,points;
	
	//define grid size
	nx = 600;
	ny = 600;
	Lx = 1;
	Ly = 1;
	
	//Define boundary conditions
	
	TB = 1;//Top Boundary
	BB = 1;//Bottom Boundary
	LB = 0;//Left Boundary
	RB = 0;//Right Boundary
	
	//Define tolerence
	
	tol = 1e-6; // Change according to BC values
	
	
	float A[nx][ny];	
	
	del_x = Lx/nx;
	del_y = Ly/ny;
	
	//Initialize starting array
	
	for(int i = 0; i<nx; i++){
		for(int j = 0; j<ny; j++){
			if(i==0){
				A[i][j] = TB;
			}
			else if(i==nx-1){
				A[i][j] = BB;
			}
			else{
				if(j==0){
					A[i][j] = LB;
				}
				else if(j==ny-1){
					A[i][j] = RB;
				}
				else{
					A[i][j] = 1;//set inital guess
				}
			}
		}
	}
	
	//Jacobian Iteration
	
	float A_J[nx][ny],temp_J[nx][ny];
	
	count_J=0; // set iterative counter
	
	memcpy(A_J, A, sizeof(A_J)); // copy inital conidtion to new array
	memcpy(temp_J, A, sizeof(temp_J)); // copy inital conidtion to new array

	e1_norm_J = 1;// set 1st error norm to 1. The program runs while the error norm is >10e-6
	while(e1_norm_J>=tol){ // setting error to be less than e-6 
		e1_norm_J = 0;// reset error norm for this loop
		for(int i = 1; i<nx-1; i++){
			for(int j = 1; j<ny-1; j++){
				temp_J[i][j] = (pow(del_x,2)*(A_J[i-1][j] + A_J[i+1][j]) + pow(del_y,2)*(A_J[i][j-1] + A_J[i][j+1]))/(2*(pow(del_x,2)+pow(del_y,2)));
				e1_norm_J = e1_norm_J + abs(A_J[i][j]-temp_J[i][j]);
			}
		}
		e1_norm_J = e1_norm_J/((nx-2)*(ny-2)); //normalizing the norm by the number of elements
		memcpy(A_J, temp_J, sizeof(A_J));
		count_J++;
		cout<<count_J<<" "<<e1_norm_J<<endl; 
	}
	
	J_output << scientific;
	J_output.precision(5);
 	J_output.open ("J_output.txt");
	
	J_output << scientific;
	J_output.precision(5);
	for(int i = 0; i<nx; i++){
		for(int j = 0; j<nx; j++){
			J_output <<A_J[i][j]<<" ";
		}
		J_output <<endl;
	}

 	J_output.close();
	
 	J_output.open ("Jacobian Solution.txt");
	J_output<<"Results using Jacobian iteration :"<<endl;
	J_output<<"Number of iterations :"<<count_J<<endl;
	J_output<<"1st Error Norm :"<<e1_norm_J<<endl;
	J_output<<"The result is:"<<endl;
	
	J_output << scientific;
	J_output.precision(5);
	for(int i = 0; i<nx; i++){
		for(int j = 0; j<nx; j++){
			J_output <<A_J[i][j]<<" ";
		}
		J_output <<endl;
	}

 	J_output.close();
	
	
	
	//Gauss-Seidel Iteration
	
	float A_GS[nx][ny],temp_GS;
	
	count_GS=0; // set iterative counter
	
	memcpy(A_GS, A, sizeof(A_GS)); // copy inital conidtion to new array

	e1_norm_GS = 1;// set 1st error norm to 1. The program runs while the error norm is >10e-6
	while(e1_norm_GS>=tol){ // setting error to be less than e-6 
		e1_norm_GS = 0;// reset error norm for this loop
		for(int i = 1; i<nx-1; i++){
			for(int j = 1; j<ny-1; j++){
				temp_GS = A_GS[i][j];
				A_GS[i][j] = (pow(del_x,2)*(A_GS[i-1][j] + A_GS[i+1][j]) + pow(del_y,2)*(A_GS[i][j-1] + A_GS[i][j+1]))/(2*(pow(del_x,2)+pow(del_y,2)));
				e1_norm_GS = e1_norm_GS + abs(A_GS[i][j]-temp_GS);
			}
		}
		e1_norm_GS = e1_norm_GS/((nx-2)*(ny-2)); //normalizing the norm by the number of elements
		count_GS++;
		cout<<count_GS<<" "<<e1_norm_GS<<endl;
	}
	
	GS_output << scientific;
	GS_output.precision(5);
 	GS_output.open ("GS_output.txt");
	for(int i = 0; i<nx; i++){
		for(int j = 0; j<nx; j++){
			GS_output <<A_GS[i][j]<<" ";
		}
		GS_output <<endl;
	}

 	GS_output.close();
 	
 	GS_output << scientific;
	GS_output.precision(5);
 	GS_output.open ("Gauss-Seidel Solution.txt");
	GS_output<<"Results using Gauss-Seidel iteration :"<<endl;
	GS_output<<"Number of iterations :"<<count_GS<<endl;
	GS_output<<"1st Error Norm :"<<e1_norm_GS<<endl;
	GS_output<<"The result is:"<<endl;
	for(int i = 0; i<nx; i++){
	for(int j = 0; j<nx; j++){
			GS_output <<A_GS[i][j]<<" ";
		}
		GS_output <<endl;
	}

 	GS_output.close();
 	
 	points.open("points.txt");
 	points<<nx<<endl;
 	points<<ny<<endl;
 	points.close();
 	


}
