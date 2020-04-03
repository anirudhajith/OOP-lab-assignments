#include <bits/stdc++.h>

using namespace std;

long long dfsCalculateSubtreeSizes(long long root, vector<long long> &subtreeSizes, vector< vector<long long> > &adjList, vector<long long> &visitStatus, vector<long long> &numTriplets, vector<long long> &depths, vector<long long> &parents) {
    if (visitStatus[root] == 2) {
        return subtreeSizes[root];
    } else {
        visitStatus[root] = 1;
        vector<long long> subSizes;
        long long totalSize = 1;
        for(long long neighbor: adjList[root]) {
            if (visitStatus[neighbor] == 0) {
                parents[neighbor] = root;
                depths[neighbor] = depths[root] + 1;
                subSizes.push_back(dfsCalculateSubtreeSizes(neighbor, subtreeSizes, adjList, visitStatus, numTriplets, depths, parents));
                totalSize += subSizes.back();
            }
        }
        subtreeSizes[root] = totalSize;
        subSizes.push_back((adjList.size()-1) - subtreeSizes[root]);
        
        for(long long i = 0; i < subSizes.size(); i++) {
            for(long long j=i+1; j < subSizes.size(); j++) {
                numTriplets[root] += subSizes[i] * subSizes[j];
            }
        }
        numTriplets[root] *= 2;
        visitStatus[root] = 2;
        return totalSize;
    }
}

void calculateNumTripletsTree(vector< vector<long long> > &adjList, vector<long long> &numTriplets, vector<long long> &subtreeSizes, vector<long long> &visitStatus, vector<long long> &depths, vector<long long> &parents) {
    long long root = 1;
    depths[root] = 1;
    dfsCalculateSubtreeSizes(root, subtreeSizes, adjList, visitStatus, numTriplets, depths, parents);
}

long long getComponent(vector<long long> &parents, long long i) {
    while (parents[i] != i) {
        parents[i] = parents[parents[i]];
        i = parents[i];
    }
    return i;
}

void onion(vector<long long> &parents, vector<long long> &sizes, long long A, long long B) {      // union is a key word
    long long rootA = getComponent(parents, A);
    long long rootB = getComponent(parents, B);
    if(sizes[rootA] < sizes[rootB]) {
        parents[rootA] = parents[rootB];
        sizes[rootB] += sizes[rootA];
    } else {
        parents[rootB] = parents[rootA];
        sizes[rootA] += sizes[rootB];
    }
}

bool find(vector<long long> &parents, long long A, long long B) {
    return (getComponent(parents, A) == getComponent(parents, B));
}


int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    long long n, m, a, b;
    cin >> n;       // number of vertices
    vector< vector<long long> > adjList(n+1);
    for(long long i=0; i < n - 1; i++) {
        cin >> a    // veterx 1
            >> b;   // vertex 2
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }

    vector<long long> subtreeSizes(adjList.size(), 0);
    vector<long long> visitStatus(adjList.size(), 0);
    vector<long long> numTriplets(n+1, 0);
    vector<long long> depths(n+1, 0);
    vector<long long> parent(n+1, 0);
    calculateNumTripletsTree(adjList, numTriplets, subtreeSizes, visitStatus, depths, parent);

    long long totalNumTriplets = 0;
    for(long long i=1; i<=n; i++) {
        totalNumTriplets += numTriplets[i];
    }
    cout << totalNumTriplets << endl;

    cin >> m;
    vector<long long> sizes(n+1, 1);
    vector<long long> component(n+1);
    for(long long i=1; i<=n; i++) {
        component[i] = i;
    }

    for(long long i=0; i < m; i++) {
        cin >> a >> b;

        a = getComponent(component, a);
        b = getComponent(component, b);
        
        while (a != b) {
            if (depths[a] < depths[b]) {            // traverses all vertices upto LCA
                a = a + b;
                b = a - b;
                a = a - b;
            }
            long long pa = getComponent(component, parent[a]);
            totalNumTriplets +=   (sizes[a] * (numTriplets[pa] - subtreeSizes[a] * 2 * (n - (subtreeSizes[a] + sizes[pa]))))
                                + (sizes[pa] * sizes[a] * (2*n - (sizes[a] + sizes[pa]) - 2))
                                + (sizes[pa] * (numTriplets[a] - 2 * (n - subtreeSizes[a]) * (subtreeSizes[a] - sizes[a])));
                                
            numTriplets[pa] += 2*sizes[a]*sizes[pa] + numTriplets[a] + 2*subtreeSizes[a]*(subtreeSizes[a] - n);
            sizes[pa] = sizes[a] + sizes[pa];
            component[a] = pa;
            a = component[a];
        }

        cout << totalNumTriplets << endl;


    }

    







    return 0;
}