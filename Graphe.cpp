//
//  Graphe.cpp
//  INF442
//
//  Created by 沈路易 on 2017/5/16.
//  Copyright © 2017年 沈路易. All rights reserved.
//

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

Graphe::Graphe(){
    map<long int,vector<long int> > *vertices=new map<long int,vector<long int> >();
    this->m_vertices=vertices;
    map<long int, vector<long int> > *pred=new map<long int, vector<long int> >();
    this->m_predecessors=pred;
}

void Graphe::randGraphe(long int n, double p){
    for (long int i = 0; i < n; i++){
        this->addVertex(i);
        for (long int j = i+1; j < n; j++){
            double r = random()/(double)RAND_MAX;
            if (r < p) this->addEdge(i, j);
            r = random()/(double)RAND_MAX;
            if (r < p) this->addEdge(j, i);
        }
    }
}

void Graphe::randGraphe_MPI(long int n, double p){
    int size=0;
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int id=0;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    srand((id+1)*time(NULL));
    
    for(long int i=id;i<n;i=i+size){
        vector<long int> temp;
        temp.push_back(i);
        for(long int j=0;j<n;j++ ){           
           double r=random()/(double)RAND_MAX;
           if((r<p)&&(j!=i)) temp.push_back(j);
        }
        int dim=temp.size();
        long int *edge=new long int[dim];
        for(int k=0;k<dim;k++){
           edge[k]=temp[k];
        }
        if(id!=0){
           MPI_Send(&dim,1,MPI_INT,0,id,MPI_COMM_WORLD);
           MPI_Send(edge,dim,MPI_LONG,0,id,MPI_COMM_WORLD);
        }
        if(id==0){
           for(int k=1;k<dim;k++){
              this->addEdge(edge[0],edge[k]);
           }
        }
    }
    if(id==0){
       for(long int i=0;i<n;i++){
           int src=i%size;
           if(src!=0){
              int l_dim=0;
              MPI_Status status_dim;
              MPI_Recv(&l_dim,1,MPI_INT,src,src,MPI_COMM_WORLD,&status_dim);
              long int l_edge[l_dim];
              MPI_Status status_edge;
              MPI_Recv(l_edge,l_dim,MPI_LONG,src,src,MPI_COMM_WORLD,&status_edge);
              for(int k=1;k<l_dim;k++){
                  this->addEdge(l_edge[0],l_edge[k]);
              }
           }   
       }
    }     
}


void Graphe::addVertex(long int v){
    if(!this->hasVertex(v)){
        vector<long int> vp;
        this->m_vertices->insert(pair<long int,vector<long int> >(v,vp));
        vector<long int> vpred;
        this->m_predecessors->insert(pair<long int,vector<long int> >(v,vpred));
    }
}

bool Graphe::hasVertex(long int v){
    if(this->m_vertices->find(v)==this->m_vertices->end()){
        return false;
    }else{
        return true;
    }
}

void Graphe::addEdge(long int src,long int dst){
    this->addVertex(src);
    this->addVertex(dst);
    if(!this->hasEdge(src, dst))
    {
        vector<long int> v=this->m_vertices->at(src);
        v.push_back(dst);
        this->m_vertices->at(src)=v;
        vector<long int> vp=this->m_predecessors->at(dst);
        vp.push_back(src);
        this->m_predecessors->at(dst)=vp;
    }
}

bool Graphe::hasEdge(long int src, long int dst){
    if(!this->hasVertex(src))
        return false;
    else
    {
        vector<long int > v=this->m_vertices->at(src);
        if(contains(&v,dst))
            return true;
        else
            return false;
    }
}

void Graphe::printGraphe(){
    map<long int,vector<long int> > *m=this->m_vertices;
    for(map<long int,vector<long int> >::iterator it=m->begin();it!=m->end();++it){
        cout<<it->first<<" => ";
        for(vector<long int>::iterator vit=it->second.begin();vit!=it->second.end();++vit)
            cout<<*vit<<" ";
        cout<<endl;
    }

    map<long int,vector<long int> > *mp=this->m_predecessors;
    for(map<long int,vector<long int> >::iterator it=mp->begin();it!=mp->end();++it){
        cout<<it->first<<" <= ";
        for(vector<long int>::iterator vit=it->second.begin();vit!=it->second.end();++vit)
            cout<<*vit<<" ";
        cout<<endl;
    }
}

long int Graphe::getSize(){
   return this->m_vertices->size();
}

void Graphe::bigGraphe(vector<Vertex* > *bg){
    map<long int,vector<long int> > *m=this->m_vertices;
    map<long int,Vertex* > dic;
    for(map<long int,vector<long int> >::iterator it=m->begin();it!=m->end();++it){
        Vertex *v = new Vertex(it->first);
        bg->push_back(v);
        dic.insert(pair<long int, Vertex* >(v->name, v));
    }
    for(map<long int,vector<long int> >::iterator it=m->begin();it!=m->end();++it){
        Vertex* v = dic.at(it->first);
        for(vector<long int>::iterator vit=it->second.begin();vit!=it->second.end();++vit){
            v->addSuccesseurs(dic.at(*vit));
        }
    }
}

vector<long int> Graphe::getVoisin(long int v){
    return this->m_vertices->at(v);
}

vector<long int> Graphe::getPrevoisin(long int v){
    return this->m_predecessors->at(v);
}

void Graphe::getSucc(long int v, vector<long int> *succ){
    succ->push_back(v);
    vector<long int> voisins = this->getVoisin(v);
    if (voisins.size() == 0){
        return;
    }
    for (vector<long int>::iterator it = voisins.begin(); it != voisins.end(); ++it){
        if (!contains(succ, *it)){
             getSucc(*it, succ);
        }
    }
}

void Graphe::getPred(long int v, vector<long int> *pred){

    pred->push_back(v);
    vector<long int> prevoisins = this->getPrevoisin(v);
    if (prevoisins.size() == 0){
        return;
    }
    for (vector<long int>::iterator it = prevoisins.begin(); it != prevoisins.end(); ++it){
        if (!contains(pred, *it)){
             getPred(*it, pred);
        }
    }
}

Graphe::~Graphe(){}

bool contains(vector<long int> *v,long int p){
    for(int i=0;i<v->size();i++){
        if(v->at(i)==p)
            return true;
    }
    return false;
    
}

