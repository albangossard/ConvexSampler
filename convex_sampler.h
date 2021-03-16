#include <iostream>
#include <fstream>
#include <cmath>
#include <Python.h>
#include <omp.h>

void is_in_cvx(double* hull_eq, int size_hull_eq, int P, double* T, int size_T, short int* tokeep, int size_tokeep);
void is_in_cvx_grid(double* hull_eq, int size_hull_eq, double* grid, int size_grid, double* T, int size_T, short int* tokeep, int size_tokeep, int* nT, int P);
