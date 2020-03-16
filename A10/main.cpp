#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;


class semiedge {
    public:

    int endpoint;                   // destination of edge
    int edgeType;                   // type 1 / type 2 / type 3
    semiedge(int end, int eType) {  // constructor
        endpoint = end;
        edgeType = eType;
    }

    const bool operator==(const semiedge &e) const {
        return (endpoint == e.endpoint) && (edgeType == e.edgeType);
    }
};

class MyHashFunction { 
public: 
    const size_t operator()(const semiedge& s) const { 
        return (s.endpoint * s.edgeType) + 1;
    } 
}; 

// BFS utility funtion to discover all components created by type 2 edges
void BFS(int startVertex, vector< unordered_set<semiedge, MyHashFunction> > &originalGraph, vector<int> &components, unordered_set<int> &remainingVertices) {
    queue<int> Q;
    vector<int> visitStatus(originalGraph.size(), 0);

    Q.push(startVertex);
    visitStatus[startVertex] = 1;
    int startComponent = components[startVertex];
    remainingVertices.erase(startVertex);

    while(!Q.empty()) {
        int toExplore = Q.front(); Q.pop();
        visitStatus[toExplore] = 2;

        for(unordered_set<semiedge, MyHashFunction>::iterator neighbor = originalGraph[toExplore].begin(); neighbor != originalGraph[toExplore].end(); neighbor++) {
            if(neighbor->edgeType == 2 && visitStatus[neighbor->endpoint] == 0) {
                Q.push(neighbor->endpoint);
                visitStatus[neighbor->endpoint] = 1;
                components[neighbor->endpoint] = startComponent;
                remainingVertices.erase(neighbor->endpoint);
            }
        }
    }
}

// returns components of each vertex among those created by type 2 edges
vector<int> getComponents(vector< unordered_set<semiedge, MyHashFunction> > &originalGraph) {
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
vector< unordered_set<semiedge, MyHashFunction> > getComponentGraph(vector< unordered_set<semiedge, MyHashFunction> > &originalGraph, vector<int> &components) {
    int vertexCount = originalGraph.size();

    unordered_map<int, int> componentAlias;
    for (vector<int>:: iterator c = components.begin(); c != components.end(); c++) {
        if (componentAlias.count(*c) == 0) {
            componentAlias[*c] = componentAlias.size()-1;
        }
    }
    
    /*
    for(unordered_map<int, int>::iterator j = componentAlias.begin(); j != componentAlias.end(); j++) {
        cout << "(" << j->first << ", " << j->second << ")" << endl;
    }
    */
    cout << "joafjowe" << endl;

    vector< unordered_set<semiedge, MyHashFunction> > componentGraph(componentAlias.size());
    
    for (int v = 0; v < vertexCount; v++) {
        for(unordered_set<semiedge, MyHashFunction>::iterator e = originalGraph[v].begin(); e != originalGraph[v].end(); e++) {
            if (components[v] != components[e->endpoint]) {
                cout << "inserting " << e->endpoint << " " << v << " " << e->edgeType << endl;
                cout << "numBuckets: " << componentGraph[componentAlias[components[v]]].bucket_count() << endl;
                componentGraph[componentAlias[components[v]]].emplace(componentAlias[components[e->endpoint]], e->edgeType);
                cout << "finished inserting " << e->endpoint << " " << v << " " << e->edgeType << endl;
            }
        }
    }
    cout << "Finished init" << endl;
    return componentGraph;
}

// checks if resultant component graph is connected
bool isConnected(vector< unordered_set<semiedge, MyHashFunction> > &componentGraph) {
    queue<int> Q;
    vector<int> visitStatus(componentGraph.size(), 0);
    
    Q.push(0);
    visitStatus[0] = 1;
    int visitedCount = 1;

    while(!Q.empty()) {
        int toExplore = Q.front(); Q.pop();
        visitStatus[toExplore] = 2;

        for(unordered_set<semiedge, MyHashFunction>::iterator neighbor = componentGraph[toExplore].begin(); neighbor != componentGraph[toExplore].end(); neighbor++) {
            if((neighbor->edgeType == 0 && componentGraph[toExplore].count(semiedge(1, neighbor->endpoint)) > 0 || 
                neighbor->edgeType == 1 && componentGraph[toExplore].count(semiedge(0, neighbor->endpoint)) > 0) &&
                visitStatus[neighbor->endpoint] == 0) {
                
                Q.push(neighbor->endpoint);
                visitStatus[neighbor->endpoint] = 1;
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
    vector< unordered_set<semiedge, MyHashFunction> > originalGraph(N);


    for(int m=0; m < M; m++) {
        cin >> u >> v >> e;
        originalGraph[u].emplace(v, e);
        originalGraph[v].emplace(u, e);
    }

    cout << "Finished taking input" << endl;

    vector<int> components = getComponents(originalGraph);
    
    cout << "Got components" << endl;

    vector< unordered_set<semiedge, MyHashFunction> > componentGraph = getComponentGraph(originalGraph, components);

    cout << "Got componentGraph" << endl;
/*
    for(int i=0; i<componentGraph.size(); i++) {
        for(unordered_set<semiedge, MyHashFunction>::iterator j = componentGraph[i].begin(); j != componentGraph[i].end(); j++) {
            cout << "(" << i << ", " << j->endpoint << ")" << endl;
        }
    }
*/
    if (isConnected(componentGraph)) {
        int numEdges = N + componentGraph.size() - 2;
        cout << M - numEdges << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}