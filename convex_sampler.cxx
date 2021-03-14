#include "convex_sampler.h"

const int num_procs = omp_get_num_procs();

void is_in_cvx(double* hull_eq, int size_hull_eq, int P, double* T, int size_T, short int* tokeep, int nT){
    int nface = size_hull_eq/(P+1);
    // std::cout<<"P="<<P<<std::endl;
    // std::cout<<"nT="<<nT<<std::endl;
    // std::cout<<"nface="<<nface<<std::endl;

    #pragma omp parallel for
    for (int e=0; e<nT; ++e){
        int f=0;
        bool ok = true;
        double tot;
        while (f<nface && ok){
            tot = hull_eq[f*(P+1)+P];
            for (int p=0; p<P; ++p){
                tot += hull_eq[f*(P+1)+p]*T[e*P+p];
            }
            if (tot>0){
                ok = false;
                tokeep[e] = 0;
            }
            ++f;
        }
    }
}
