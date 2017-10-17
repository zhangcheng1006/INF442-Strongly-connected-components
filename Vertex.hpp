#ifndef Vertex_hpp
#define Vertex_hpp

#include <stdio.h>
#include <vector>
using namespace std;

class Vertex{
public:
    long int name;
    long int index;
    long int lowlink;
    bool onStack;
    vector<Vertex* > *successeurs;
    
    Vertex(long int n);
    void addSuccesseurs(Vertex *v);
    ~Vertex();
    
};

#endif /* Vertex_hpp */


