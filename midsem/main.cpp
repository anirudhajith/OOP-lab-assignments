#include <bits/stdc++.h>
#define INF 10000000000
using namespace std;

class Student {
    public:
    long long id;                               // id
    vector<long long> marks;                    // 5-membered vector of marks
    long long skillValue;                       // skill value
    
    Student(long long i, vector<long long> m, long long sk) {
        id = i;
        marks = m;
        skillValue = sk;
    }
    Student() {
        marks.resize(5);
        skillValue = -INF;
    }
};


bool betterRank (const Student& s1, const Student& s2) {
    return !lexicographical_compare(s1.marks.begin(), s1.marks.end(), s2.marks.begin(), s2.marks.end());
}


bool compareStudentsBySkill (const Student& s1, const Student& s2) {
    return (s1.skillValue > s2.skillValue);
}


long long totalSpecialCount;

void merge(vector<Student> &A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    vector<Student> L(n1 + 2);
    vector<Student> R(n2 + 2);
    for(int i=1; i <= n1; i++) L[i] = A[p + i - 1];
    for(int i=1; i <= n2; i++) R[i] = A[q + i];
    L[n1 + 1] = Student();
    R[n2 + 1] = Student();
    int i=1, j = 1;
    cout << "Commencing merge: " << p << " " << q << " " << r << endl;
    for(int k=p; k<=r; k++) {
        if(compareStudentsBySkill(L[i], R[j])) {
            A[k] = L[i++];
        } else {
            totalSpecialCount += (n1 - i + 1);
            cout << "t: " << totalSpecialCount << endl;
            A[k] = R[j++];
        }
    }

}

void mergeSort(vector<Student> &A, int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        mergeSort(A, p, q);
        mergeSort(A, q+1, r);
        merge(A, p, q, r);
    }

}


int main() {
    

    int n;        // number of students
    cin >> n;
    vector<Student> allStudents(n+1);
    unordered_map<long long, long long> skillLevels;
    for(int i=1; i <= n; i++) {
        for(int m = 0; m < 5; m++) {
            cin >> allStudents[i].marks[m];
        }
        cin >> allStudents[i].skillValue;
        if (skillLevels.count(allStudents[i].skillValue) > 0) {
            skillLevels[allStudents[i].skillValue]++;
        } else {
            skillLevels[allStudents[i].skillValue] = 1;
        }
    }
    
    sort(allStudents.begin()+1, allStudents.end(), betterRank);
    
    for(int i=1; i <= n; i++) {
        cout << allStudents[i].skillValue << " ";
    }
    cout << endl;
    
    totalSpecialCount = 0;
    mergeSort(allStudents, 1, n);
    for(auto it = skillLevels.begin(); it != skillLevels.end(); it++) {
        totalSpecialCount -= (it->second * (it->second - 1)) / 2;
        cout << "t: " << totalSpecialCount << endl;
    }
    
    cout << totalSpecialCount << endl;
    
    
    
    
    return 0;
}