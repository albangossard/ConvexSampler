#include "convex_sampler.h"

const int num_procs = omp_get_num_procs();

void is_in_cvx(double* hull_eq, int size_hull_eq, int P, double* T, int size_T, short int* tokeep, int size_tokeep){
    int nface = size_hull_eq/(P+1);
    // std::cout<<"P="<<P<<std::endl;
    // std::cout<<"size_tokeep="<<size_tokeep<<std::endl;
    // std::cout<<"nface="<<nface<<std::endl;

    #pragma omp parallel for
    for (int e=0; e<size_tokeep; ++e){
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


void gen_T(int p, int P, double* block, int cpt_grid, int* cpt_T, int* nT, double* grid, double* T){
    if (p<P){
        for (int i=0; i<nT[p]; ++i){
            block[p] = grid[i+cpt_grid];
            gen_T(p+1, P, block, cpt_grid+nT[p], cpt_T, nT, grid, T);
        }
    }else{
        for (int pp=0; pp<P; ++pp){
            T[(*cpt_T)*P+pp] = block[pp];
        }
        *cpt_T += 1;
    }
}

void is_in_cvx_grid(double* hull_eq, int size_hull_eq, double* grid, int size_grid, double* T, int size_T, short int* tokeep, int size_tokeep, int* nT, int P){
    // size(nT) = P
    // size(grid) = sum_{p=1}^P nT(p)
    // size(T) = P x prod_{p=1}^P nT(p)
    double block[P];
    int cpt_T = 0;
    gen_T(0, P, block, 0, &cpt_T, nT, grid, T);

    is_in_cvx(hull_eq, size_hull_eq, P, T, size_T, tokeep, size_tokeep);
}
