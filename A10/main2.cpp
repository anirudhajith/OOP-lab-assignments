#include<bits/stdc++.h>

using namespace std;

// semiedges are pairs where
// first == endpoint
// second == edgeType

// BFS utility function to discover all components created by type 2 edges
void BFS(int startVertex, vector< set< pair<int,int> > > &originalGraph, vector<int> &components, unordered_set<int> &remainingVertices) {
    queue<int> Q;
    vector<int> visitStatus(originalGraph.size(), 0);

    Q.push(startVertex);
    visitStatus[startVertex] = 1;
    int startComponent = components[startVertex];
    remainingVertices.erase(startVertex);

    while(!Q.empty()) {
        int toExplore = Q.front(); Q.pop();
        visitStatus[toExplore] = 2;

        for(auto neighbor = originalGraph[toExplore].begin(); neighbor != originalGraph[toExplore].end(); neighbor++) {
            if(neighbor->second == 2 && visitStatus[neighbor->first] == 0) {
                Q.push(neighbor->first);
                visitStatus[neighbor->first] = 1;
                components[neighbor->first] = startComponent;
                remainingVertices.erase(neighbor->first);
            }
        }
    }
}

// returns components of each vertex among those created by type 2 edges
vector<int> getComponents(vector< set< pair<int, int> > > &originalGraph) {
    int vertexCount = originalGraph.size();

    unordered_set <int> remainingVertices;
    vector<int> components(vertexCount, 0);
    for(int v=0; v < vertexCount; v++) {
        remainingVertices.insert(v);
        components[v] = v;
    }
    
    while (!remainingVertices.empty()) {
        int startVertex = *remainingVertices.begin();
        
        BFS(startVertex, originalGraph, components, remainingVertices);
    }

    return components;
}

// returns a graph where every type 2 component is represented by as single vertex and the original edge set has been mapped
vector< set< pair<int, int> > > getComponentGraph(vector< set< pair<int, int> > > &originalGraph, vector<int> &components) {
    int vertexCount = originalGraph.size();

    unordered_map<int, int> componentAlias;
    for (vector<int>:: iterator c = components.begin(); c != components.end(); c++) {
        if (componentAlias.count(*c) == 0) {
            componentAlias[*c] = componentAlias.size();
        }
    }

    vector< set< pair<int, int> > > componentGraph(componentAlias.size());
    
    for (int v = 0; v < vertexCount; v++) {
        for(auto e = originalGraph[v].begin(); e != originalGraph[v].end(); e++) {
            if (components[v] != components[e->first]) {

                pair<int, int> P = make_pair(componentAlias[components[e->first]], e->second);
                componentGraph[componentAlias[components[v]]].insert(P);
            }
        }
    }
    return componentGraph;
}

// checks if resultant component graph is connected
bool isConnected(vector< set< pair<int, int> > > &componentGraph) {
    queue<int> Q;
    vector<int> visitStatus(componentGraph.size(), 0);
    
    Q.push(0);
    visitStatus[0] = 1;
    int visitedCount = 1;

    while(!Q.empty()) {
        int toExplore = Q.front(); Q.pop();
        visitStatus[toExplore] = 2;

        for(auto neighbor = componentGraph[toExplore].begin(); neighbor != componentGraph[toExplore].end(); neighbor++) {
            if(visitStatus[neighbor->first] == 0 &&
                (neighbor->second == 0 && componentGraph[toExplore].count(make_pair(neighbor->first, 1)) > 0 || 
                neighbor->second == 1 && componentGraph[toExplore].count(make_pair(neighbor->first, 0)) > 0)) {
                
                Q.push(neighbor->first);
                visitStatus[neighbor->first] = 1;
                visitedCount++;
            }
        }
    }

    return (visitedCount == componentGraph.size());
}


int main() {
    int N, M, u, v, e;
    cin >> N >> M;

    // adjacency list representation of original graph
    vector< set< pair<int, int> > > originalGraph(N);


    for(int m=0; m < M; m++) {
        cin >> u >> v >> e;
        originalGraph[u].emplace(v, e);
        originalGraph[v].emplace(u, e);
    }

    vector<int> components = getComponents(originalGraph);

    vector< set< pair<int, int> > > componentGraph = getComponentGraph(originalGraph, components);
    //cout << componentGraph.size() << endl;

    if (isConnected(componentGraph)) {
        int numEdges = N + componentGraph.size() - 2;
        cout << M - numEdges << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}