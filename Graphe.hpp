//
//  Graphe.hpp
//  INF442
//
//  Created by 沈路易 on 2017/5/16.
//  Copyright © 2017年 沈路易. All rights reserved.
//

#ifndef Graphe_hpp
#define Graphe_hpp

#include <stdio.h>
#include <map>
#include <vector>
#include "Vertex.hpp"
using namespace std;
class Graphe{
public:
    map<long int,vector<long int> > *m_vertices;
    map<long int, vector<long int> > *m_predecessors;
    
    Graphe();
    void randGraphe(long int n, double p);
    void randGraphe_MPI(long int n, double p);
    void addVertex(long int v);
    bool hasVertex(long int v);
    void addEdge(long int src,long int dst);
    bool hasEdge(long int src,long int dst);
    void removeEdge(long int src,long int dst);
    void printGraphe();
    long int getSize();
    void bigGraphe(vector<Vertex* > *bg);
    vector<long int> getVoisin(long int v);
    vector<long int> getPrevoisin(long int v);
    void getSucc(long int v, vector<long int> *succ);
    void getPred(long int v, vector<long int> *pred);
    ~Graphe();
    
};

bool contains(vector<long int> *v, long int p);

#endif /* Graphe_hpp */
