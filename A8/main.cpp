#include <bits/stdc++.h>
#define MAX_STUDENTS

using namespace std;

class Student {                 // student
    
    public:                     // public
    Student(int a, char g, string m, int c) { // constructor
        age = a;
        gender = g;
        motherTongue = m;
        CGPA = c;
    }
    int age;                    // age of student
    char gender;                // gender of student
    string motherTongue;        // mother tongue of student
    int CGPA;                   // CGPA of student
};

bool canBeTogether(Student &s1, Student &s2) {   // checks if two students can both be chosen
    if (abs(s1.age - s2.age) >= 3 ||
        s1.gender == s2.gender ||
        s1.motherTongue != s2.motherTongue ||
        s1.CGPA == s2.CGPA) return true;
    else return false;
}

void initializeGraph(vector<Student> &males, vector<Student> &females, vector< vector<bool> > &bipAdjMat) {
    for(int m=0; m < males.size(); m++) {
        for(int f=0; f < females.size(); f++) {
            bipAdjMat[m][f] = !canBeTogether(males[m], females[f]);
            //cout << m << f << endl;
        }
    }
}

bool canMatchMale(int m, vector<bool> &isMatchedFemale, vector<int> &getMatchedMale, vector< vector<bool> > &bipAdjMat) {
    for(int f = 0; f < isMatchedFemale.size(); f++) {
        if (bipAdjMat[m][f] && !isMatchedFemale[f]) {
            isMatchedFemale[f] = true;
            if (getMatchedMale[f] < 0 || canMatchMale(getMatchedMale[f], isMatchedFemale, getMatchedMale, bipAdjMat)) {
                getMatchedMale[f] = m;
                return true;
            }
        }
    }
    return false;
}

int getMaximumMatchCount(vector< vector<bool> > &bipAdjMat) {
    vector<int> getMatchedMale(bipAdjMat[0].size(), -1);
    int totalMatchings = 0;
    for (int m=0; m < bipAdjMat.size(); m++) {
        vector<bool> isMatchedFemale(bipAdjMat[0].size(), false);
        if (canMatchMale(m, isMatchedFemale, getMatchedMale, bipAdjMat)) {
            totalMatchings++;
        }
    }

    return totalMatchings;
}

int main() {
    int T, N, age;
    char gender;
    string motherTongue;
    int cgpa;
    
    cin >> T;
    for(int t=0; t<T; t++) {
        vector<Student> males;        // list of all male students
        vector<Student> females;        // list of all female students
        
        cin >> N;
        for(int n=0; n < N; n++) {
            cin >> age
                >> gender
                >> motherTongue
                >> cgpa;
            if (gender == 'M') {
                males.emplace_back(age, gender, motherTongue, cgpa);
            } else if (gender == 'F') {
                females.emplace_back(age, gender, motherTongue, cgpa);
            }
        }
        if (min(males.size(), females.size()) > 0) {
            vector< vector<bool> > bipAdjMat(males.size(), vector<bool>(females.size(), false));
            initializeGraph(males, females, bipAdjMat);
            int totalMatchCount = getMaximumMatchCount(bipAdjMat);
            cout << N - totalMatchCount << endl;
        } else {
            cout << max(males.size(), females.size()) << endl;
        }
    }
}