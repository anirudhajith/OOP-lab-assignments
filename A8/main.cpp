#include <bits/stdc++.h>
#define MAX_STUDENTS

using namespace std;

class Student {                 // student
    private:
    static int numStudents;
    
    public:                     // public
    Student(int a, char g, string m, int c) { // constructor
        id = ++numStudents;
        age = a;
        gender = g;
        motherTongue = m;
        CGPA = c;
    }
    
    int id;                     // id of student
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
        }
    }
}


int main() {
    int T, N, age;
    char gender;
    string motherTongue;
    int cgpa;
    
    cin >> T;
    for(int t=0; t<T; t++) {
        Student::numStudents = 0;
        vector<Student> males;        // list of all male students
        vector<Student> females;        // list of all female students
        
        cin >> N;
        for(int n=0; n < N; n++) {
            cin >> age
                >> gender
                >> motherTongue
                >> cgpa;
            if (G == 'M') {
                males.emplace_back(age, gender, motherTongue, cgpa);
            } else if (G == 'F') {
                females.emplace_back(age, gender, motherTongue, cgpa);
            }
        }
        
        vector< vector<bool> > bipAdjMat(males.size(), vector<bool>(false, females.size()));
        initializeGraph(males, females, bipAdjMat);
        
        
        
        
    }
    
    
}