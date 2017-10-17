#include "Graphe.hpp"
#include "Vertex.hpp"
#include <vector>
#include <iostream>
#include <time.h>

using namespace std;

void strongconnect(Vertex *v, vector<vector<long int> > *result);

void tarjan(Graphe g, vector<vector<long int> > *result);

