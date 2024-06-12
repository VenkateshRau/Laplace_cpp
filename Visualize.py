import numpy as np
import matplotlib.pyplot as plt

# Read solution data from file
u_J = np.loadtxt('J_output.txt')
u_GS = np.loadtxt('GS_output.txt')

#Read number of points from file
points = open("points.txt","r")
Nx = int(points.readline())
Ny = int(points.readline())
points.close()

# Generate x and y coordinates for the grid
x = np.linspace(0, 1, Nx)
y = np.linspace(0, 1, Ny)

# Create a meshgrid for plotting
X, Y = np.meshgrid(x, y)

# Plot the heatmap for Jacobian iteration
plt.figure(figsize=(8, 6))
plt.contourf(X, Y, u_J, cmap='coolwarm')
plt.colorbar(label='u')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Solution of Laplace Equation Using Jacobian Iteration')
plt.savefig('J_heatmap.png')  # Save the heatmap as an image


# Plot the heatmap for Gauss-Seidel iteration
plt.figure(figsize=(8, 6))
plt.contourf(X, Y, u_GS, cmap='coolwarm')
plt.colorbar(label='u')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Solution of Laplace Equation Using Gauss-Seidel Iteration')
plt.savefig('GS_heatmap.png')  # Save the heatmap as an image

