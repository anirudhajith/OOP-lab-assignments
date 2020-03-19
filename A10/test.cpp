#include <vector>
#include <iostream>
#include <unordered_map>
#include <set>
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

    const bool operator < (const semiedge &e) const {
        return (endpoint < e.endpoint) || (edgeType < e.edgeType);
    }
};

int main() {
    set<semiedge> S;
    S.insert(semiedge(5,6));

    return 0;
}