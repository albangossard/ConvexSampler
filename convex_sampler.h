#include <iostream>
#include <fstream>
#include <cmath>
#include <Python.h>
#include <omp.h>

void is_in_cvx(double* hull_eq, int size_hull_eq, int P, double* T, int size_T, short int* tokeep, int nT);
