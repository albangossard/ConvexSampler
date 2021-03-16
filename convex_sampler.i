%module convex_sampler
%{
#define SWIG_FILE_WITH_INIT
#include "convex_sampler.h"
%}

%include "numpy.i"


%init %{
    import_array();
%}

%apply (double* IN_ARRAY1, int DIM1) {(double* hull_eq, int size_hull_eq)}
%apply (double* IN_ARRAY1, int DIM1) {(double* T, int size_T)}
%apply (short int* IN_ARRAY1, int DIM1) {(short int* tokeep, int size_tokeep)}
%apply (int* IN_ARRAY1, int DIM1) {(int* nT, int P)}
%apply (double* IN_ARRAY1, int DIM1) {(double* grid, int size_grid)}

%include "convex_sampler.h"