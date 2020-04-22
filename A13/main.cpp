#include <bits/stdc++.h>

using namespace std;

int N, M;

struct coord {
    int x;
    int y;

    coord(int xx, int yy) {
        x = xx;
        y = yy;
    }

    bool has(string direction) {
        if (direction == "left" && y > 0) return true;
        else if (direction == "right" && y < M-1) return true;
        else if (direction == "up" && x > 0) return true;
        else if (direction == "down" && x < N-1) return true;
        else return false;
    }

    coord getNeighbor(string direction) {
        if (direction == "left" && y > 0) return coord(x,y-1);
        else if (direction == "right" && y < M-1) return coord(x,y+1);
        else if (direction == "up" && x > 0) return coord(x-1,y);
        else if (direction == "down" && x < N-1) return coord(x+1,y);
        else return coord(N,M);
    }
};

int main() {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> M;

    const int UNVISITED = INT_MAX;

    vector< vector<char> > city(N, vector<char>(M));
    vector< vector<int> > dist(N, vector<int>(M,UNVISITED));

    queue<coord> Q;

    for(int n=0; n < N; n++) {
        for (int m=0; m < M; m++) {
            cin >> city[n][m];
            if (city[n][m] == 'H') {
                Q.emplace(n, m);
                dist[n][m] = 0;
            }
        }
    }
    
    vector<string> directions = {"left", "right", "up", "down"};
    
    while(!Q.empty()) {
        coord u = Q.front(); Q.pop();

        for (string direction: directions) {
            if (u.has(direction)) {
                coord neighbor = u.getNeighbor(direction);
                if (dist[neighbor.x][neighbor.y] == UNVISITED) {
                    dist[neighbor.x][neighbor.y] = dist[u.x][u.y] + 1;
                    Q.push(neighbor);
                }
            }    
        }
    }

    for(int n=0; n < N; n++) {
        for (int m=0; m < M; m++) {
            cout << dist[n][m] << " ";
        }
        cout << endl;
    }

    return 0;
}