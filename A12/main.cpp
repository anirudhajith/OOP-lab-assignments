#include <bits/stdc++.h>

using namespace std;

void initialiseLPS(string V, vector<int> &LPS) {
    int M = V.length();
    int firstPossibleMismatch = 0;
    int i = 1;
    while (i < M) {
        if (V[i] == V[firstPossibleMismatch]) {
            LPS[i] = ++firstPossibleMismatch;
            i++;
        } else if (V[i] != V[firstPossibleMismatch]) {
            if (firstPossibleMismatch == 0) {
                LPS[i] = 0;
                i++;
            } else {
                firstPossibleMismatch = LPS[firstPossibleMismatch - 1];
            }
        }
    }
}

int countNumberOfOccurences(string X, string V, vector<int> &LPS) {
    int numOccurences = 0;
    int M = V.length(), N = X.length();
    int i = 0, j = 0;

    while(i < N) {
        if (X[i] == V[j]) {
            i++; j++;
            if (j == M) {
                numOccurences++;
                j = LPS[j-1];
            }
        } else if (i < N && X[i] != V[j]){
            if (j > 0) {
                j = LPS[j-1];
            } else {
                i++;
            }
        }
    }
    
   return numOccurences;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int T;
    cin >> T;               // number of testcases

    for(int t=0; t < T; t++) {
        int K, N, M;
        string X, V;
        cin >> X            // DNA sequence
            >> V            // medicine
            >> K;           // minimum number of matches
        N = X.length();     // length of virus genome
        M = V.length();     // length of medicine
        
        vector<int> differences(N-1);
        for(int i=0; i < N-1; i++) {
            differences[i] = (X[i+1] - X[i] + 26) % 26;
        }

        vector<int> LPS(M);
        initialiseLPS(V, LPS);

        int numOccurences = countNumberOfOccurences(X, V, LPS);
        cout << (numOccurences >= K?"YES":"NO") << endl
             << numOccurences << endl;

        int Q, L, R, S;
        char firstChar = X[0];
        cin >> Q;
        for(int i=1; i <= Q; i++) {
            cin >> L >> R >> S;
            
            if (L == 1) firstChar = (((((firstChar - 'A') + S) % 26) + 26) % 26) + 'A';
            else        differences[L-2] = (((differences[L-2] + S) % 26) + 26) % 26;
            
            differences[R-1] = (((differences[R-1] - S) % 26) + 26) % 26;
        }

        string newX(N,'_');
        newX[0] = firstChar;
        for(int i=1; i<N; i++) {
            newX[i] = ((newX[i-1] - 'A' + differences[i-1] + 26) % 26) + 'A';
        }
        cout << newX << endl;

        numOccurences = countNumberOfOccurences(newX, V, LPS);
        cout << (numOccurences >= K?"YES":"NO") << endl
             << numOccurences << endl;

    }
}