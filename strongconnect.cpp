#include "Graphe.hpp"
#include "Vertex.hpp"
#include <vector>
#include <iostream>
#include <time.h>

using namespace std;

long int idx = 0;
vector<Vertex *> stack;

void strongconnect(Vertex *v, vector<vector<long int> > *result){
    v->index = idx;
    v->lowlink = idx;
    idx++;
    stack.push_back(v);
    v->onStack = true;

    vector<Vertex* > *suc = v->successeurs;
    for (vector<Vertex* >::iterator it = suc->begin(); it != suc->end(); ++it){
        if ((*it)->index == -1){
            strongconnect(*it, result);
            if ((*it)->lowlink < v->lowlink) v->lowlink = (*it)->lowlink;
        }
        else if ((*it)->onStack) {
            if ((*it)->index < v->lowlink) v->lowlink = (*it)->index;
        }
    }

    
    if (v->lowlink == v->index) {
        vector<long int> *ssc=new vector<long int>;
        Vertex* w = NULL;
        do {
            w = stack.back();
            stack.pop_back();
            w->onStack = false;
            ssc->push_back(w->name);
        } while (w->name != v->name);
        result->push_back(*ssc);
    }
}

void tarjan(Graphe g, vector<vector<long int> > *result){
    vector<Vertex* > *bg=new vector<Vertex* >;
    g.bigGraphe(bg);
    for (vector<Vertex* >::iterator it = bg->begin(); it != bg->end(); ++it){
        if ((*it)->index == -1){
            strongconnect(*it, result);
        }
    }
}

