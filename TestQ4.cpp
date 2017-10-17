#include "Graphe.hpp"
#include "Vertex.hpp"
#include "mpi.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <time.h>
#include "strongconnect.hpp"
#include "parallize.hpp"

using namespace std;

int main(int argc, char ** argv){
    srand(time(NULL));
    MPI_Init(&argc, &argv);
    
    Graphe g;
    g.randGraphe(100,0.025);
    strongconnect_MPI(g);
    
    MPI_Finalize();

    return 0;
}

