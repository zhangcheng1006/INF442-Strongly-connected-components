# INF442-Strongly-connected-components
Finding the strongly connected components in a graph of data.

Introduction
-----------------------
The most basic way of partitioning a graph is splitting it up into its connected components. 
Still, the fundamental question of connected components often comes up, in
particular when analyzing the basic computational capabilities of a network, as connectivity is a necessary
condition for many tasks and services. The question gets even more interesting for directed graphs
(digraphs) since many real-life networks such as social influence graphs and wireless communication
networks are inherently directed. Also, one has to distinguish between weak and strong connectivity.
From a computational point of view, oftentimes strong connectivity is the right generalization from
undirected to directed graphs.

A digraph G = (V,E) is strongly connected if it contains a path from u to v for all nodes u, v.
A sub-digraph of G is a strongly connected component of G if it is strongly connected and maximal
with this property. Any digraph has a unique decomposition into strongly connected components, which
partitions the set of nodes.

Objectif
---------------------
Implement the sequential algorithm which is invented by Tarjan to find the strongly connected components 
and then use MPI to implement the parallel algorithm.

Please refer to 'project-scc.pdf' and 'rapport final.pdf' for more details.
