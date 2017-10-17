#include "Vertex.hpp"
 using namespace std;

 Vertex::Vertex(long int n){
     this->name = n;
     this->index = -1;
     this->lowlink = -1;
     this->onStack = false;
     this->successeurs = new vector<Vertex* >;
 }

 void Vertex::addSuccesseurs(Vertex* v){
     this->successeurs->push_back(v);
 }

 Vertex::~Vertex(){}
 
 
