 2D Laplace equation is solved using FDM in c++. The second-order central difference approximation is used for both terms and the resulting system of linear equations is solved iteratively using the Jacobi Gauss-Seidel methods. No relaxation is used but can be eaily addded to the solution loops. The iteration number and L1 Error Norm is displayed on the screen. This can be diabled in the last line of the loop.

The domaain is a square of size 1 with follwing BCs - 
Top and bootm - u = 1
Left and Right - u = 0

The Grid points in xand y need to be set at the start of the program along with the tolerence at the Laplace.cpp file. 

The expoted files are read using Python to create the heatmap images using NumPy and Matplotlib.
