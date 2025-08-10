# Using Genetic Algorithm to Solve the Traveling Salesman Problem

## A project written in C++ that implements a genetic algorithm for finding the optimal path

This project includes two modules, the first module is a for generating the traveling salesman problem, and the second module is a genetic algorithm that searches for the optimal path. The traveling salesman problem is represented as a set of coordinates (x, y) and a matrix of distances between these points. The genetic algorithm finds the optimal path that passes through all the points and returns to the starting point. The project includes two parts:

* The traveling salesman problem is a set of points with coordinates (x, y) and a matrix of distances between these points.
* A genetic algorithm that finds an optimal solution as a sequence of points.

## How to install this C++ Project

1. install visual studio 2022
2. clone this repsitory
3. start the project
4. the program prints the distance matrix, then prints Gen i, this means that the program has processed the i generation
5. the last entry that the program prints is the length of the path for the optimal solution found
6. the coordinates of the points are specified in the data.csv file, and the found solution in the decision.csv file
7. to generate new points, you can change the arguments of the t_com object - the first argument instead of zero, you need to specify the number of points, and the second argument
8. Task_Kom class method - print_coords will print new coordinates
9. the Task_Kom class method - create_data will save new data to the data.csv file
10. if there is a ready distance matrix, you can save it in the variable matrx_dist, and it must be of the type vector<vector<double>>
11. if the number of points is not equal to ten, then for better convergence it is worth changing the second argument of the gen object to the number 10 * number of points, it denotes the number of individuals in a population
12. to improve convergence, you can also increase the argument of the run_gen_algoritm method, it means the number of generations
