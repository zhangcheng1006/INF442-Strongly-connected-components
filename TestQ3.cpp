#include "Graphe.hpp"
#include "mpi.h"
#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>
#include <cmath>
#include <time.h>
#include "Vertex.hpp"

using namespace std;

int main(int argc, char ** argv){
    MPI_Init(&argc, &argv);
    
    Graphe g;
    g.randGraphe_MPI(100,0.02);
    g.printGraphe();
    
    MPI_Finalize();
    
    return 0;
}

