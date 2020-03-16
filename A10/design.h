#ifndef __DESIGN_H__
#define __DESIGN_H__
#include <bits/stdc++.h>

using namespace std;

class semiedge {
    public:

    int endpoint;                   // destination of edge
    int edgeType;                   // type 1 / type 2 / type 3
    semiedge(int end, int eType);   // constructor
};

// BFS utility funtion to discover all components created by type 2 edges
void BFS(vector< vector<semiedge> > &originalGraph, vector<int> &components, unordered_set<int> &remainingVertices);

// returns components of each vertex among those created by type 2 edges
vector<int> getComponents(vector< vector<semiedge> > &originalGraph);

// returns a graph where every type 2 component is represented by as single vertex and the original edge set has been mapped
vector< vector<semiedge> > getComponentGraph(vector< vector<semiedge> > &originalGraph, vector<int> &components);

// checks if resultant component graph is connected
bool isConnected(vector< vector<semiedge> > &componentGraph);

// adjacency list representation of original graph
vector< vector<semiedge> > originalGraph;

// adjacency list representation of component graph
vector< vector<semiedge> > componentGraph;

#endif