#include "Graphe.hpp"
#include "Vertex.hpp"
#include "mpi.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <time.h>
#include "strongconnect.hpp"

using namespace std;

void print(vector<long int> *v);

void merge(vector<long int> *pred, vector<long int> *succ, vector<long int>
*scc, vector<long int> *s2, vector<long int> *s3, vector<long int> *s4);

Graphe sousGraphe(Graphe g, vector<long int> s);

void toArray(vector< vector<long int> > * result, long int * arr,long int
*size);

void toVector(vector< vector<long int> > * result, long int* arr, long int n);

void strongconnect_MPI(Graphe g);

