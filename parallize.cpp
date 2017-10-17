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

void print(vector<long int> *v){
    for(int i=0;i<v->size();i++){
        cout<<v->at(i)<<" ";
    }
    cout<<endl;
}

void merge(vector<long int> *pred, vector<long int> *succ, vector<long int> *scc, vector<long int> *s2, vector<long int> *s3, vector<long int> *s4){
    sort(pred->begin(),pred->end());
    sort(succ->begin(), succ->end());
    sort(s4->begin(), s4->end());
    long int i = 0, j = 0, k = 0;
    while (i < pred->size() && j < succ->size()){
        if (pred->at(i) > succ->at(j)){
            s2->push_back(succ->at(j));
            while(s4->at(k)!=succ->at(j)){
                k++;
            }
            s4->erase(s4->begin()+k);
            j++;
        } 
        else if (pred->at(i) < succ->at(j)){
            s3->push_back(pred->at(i));
            while(s4->at(k)!=pred->at(i)){
                k++;
            }
            s4->erase(s4->begin()+k);
            i++;
        }
        else{
            scc->push_back(pred->at(i));
            while(s4->at(k)!=succ->at(j)){
                k++;
            }
            s4->erase(s4->begin()+k);
            i++;
            j++;
        } 
    }
    while (i < pred->size()){
        s3->push_back(pred->at(i));
            while(s4->at(k)!=pred->at(i)){
                k++;
            }
            s4->erase(s4->begin()+k);
            i++;
    }
    while (j < succ->size()){
        s2->push_back(succ->at(j));
            while(s4->at(k)!=succ->at(j)){
                k++;
            }
            s4->erase(s4->begin()+k);
            j++;
    }
}

Graphe sousGraphe(Graphe g, vector<long int> s){
    Graphe sg;
    for(int i=0;i<s.size();i++){
        sg.addVertex(s.at(i));
        for(int j=i+1;j<s.size();j++)
        {
            if(g.hasEdge(s.at(i),s.at(j)))
               sg.addEdge(s.at(i),s.at(j));
            if(g.hasEdge(s.at(j),s.at(i)))
               sg.addEdge(s.at(j),s.at(i));
        }
    }
    return sg;
}

void toArray(vector< vector<long int> > * result, long int * arr,long int *size){
     long int k=0;
     for(long int i=0; i<result->size(); i++){
         for(long int j=0; j<(*result)[i].size();j++){
             arr[k]=(*result)[i][j];
             k++;
         }
         arr[k]=-1;
         k++;
     }
     *size=k;
}

void toVector(vector< vector<long int> > * result, long int* arr, long int n){
    vector<long int> v;
    for(int i=0;i<n;i++){
        if(arr[i]!=-1){
            v.push_back(arr[i]);
        }else{
        result->push_back(v);
        v.clear();}
    }
}

void strongconnect_MPI(Graphe g){
    int rank, nprocs;
    MPI_Status status;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    
    if (rank == 0){
        g.printGraphe();
    }

    long int v = (long int) g.m_vertices->size()*((double)rand()/(double)RAND_MAX);
    vector<long int> *succ = new vector<long int>;
    g.getSucc(v, succ);
    vector<long int> *pred = new vector<long int>;
    g.getPred(v, pred);
    vector<vector<long int> > *result = new vector<vector<long int> >;
    vector<long int> *scc = new vector<long int>;
    vector<long int> *s2 = new vector<long int>;
    vector<long int> *s3 = new vector<long int>;
    vector<long int> *s4 = new vector<long int>;
    map<long int, vector<long int> > *m = g.m_vertices;
    for (map<long int, vector<long int> >::iterator it = m->begin(); it != m->end(); ++it){
        s4->push_back(it->first);
    }
    merge(pred, succ, scc, s2, s3, s4);
    /*
    if (rank == 0){
       cout << v << endl;
       print(scc);
       print(s2);
       print(s3);
       print(s4);
    }
    */
    long int * arr=new long int[1000000];
    long int size=0;
    if(rank == 0)
        result->push_back(*scc);
    if (rank == 1) {
        Graphe sg2 = sousGraphe(g, *s2);
        tarjan(sg2, result);;
        toArray(result,arr,&size);
    }
    if (rank == 2) {
        Graphe sg3 = sousGraphe(g, *s3);
        tarjan(sg3, result);
        toArray(result,arr,&size);
    }
    if (rank == 3){
        Graphe sg4 = sousGraphe(g, *s4);
        tarjan(sg4, result);
        toArray(result,arr,&size);
    }

    if(rank == 0){
        long int local_size=0;
        for (int i = 1; i < 4; i++){
            MPI_Recv(&local_size, 1, MPI_LONG, i, i, MPI_COMM_WORLD,&status);
            long int * arr= new long int[local_size];
            MPI_Recv(arr, local_size,MPI_LONG, i, i, MPI_COMM_WORLD,&status);
            vector<vector<long int> > *v_local=new vector<vector<long int> >;
            toVector(v_local,arr,local_size);
            for(int i=0;i<v_local->size();i++){
                result->push_back(v_local->at(i));
            }
        }
        for (long int i = 0; i < result->size(); i++){
        cout << "SCC" << i <<": ";
        for (long int j = 0; j < (*result)[i].size(); j++){
            cout << (*result)[i][j] << " ";
        }
        cout << endl;
    }
    }else{
        MPI_Send(&size,1,MPI_LONG,0,rank,MPI_COMM_WORLD);
        MPI_Send(arr,size,MPI_LONG,0,rank,MPI_COMM_WORLD);

    }
}


