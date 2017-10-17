#include "Graphe.hpp"
#include "Vertex.hpp"
#include "strongconnect.hpp"
#include <vector>
#include <iostream>
#include <time.h>
#include "mpi.h"

using namespace std;

int main(int argc, char ** argv){
    srand(time(NULL));

    MPI_Init(&argc, &argv);
    
    vector<vector<long int> > *result = new vector<vector<long int> >;
    Graphe g;
    g.randGraphe(100,0.02);
    g.printGraphe();
    tarjan(g, result);
    for (long int i = 0; i < result->size(); i++){
        cout << "SCC" << i <<": ";
        for (long int j = 0; j < (*result)[i].size(); j++){
            cout << (*result)[i][j] << " ";
        }
        cout << endl;
    }
    
    MPI_Finalize();
    return 0;
}
