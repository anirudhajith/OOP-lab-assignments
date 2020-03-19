#include <iostream> 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
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
    Student() {}
};

struct compareStudentsByRank {
    bool operator() (const Student& s1, const Student& s2) const {
        return !lexicographical_compare(s1.marks.begin(), s1.marks.end(), s2.marks.begin(), s2.marks.end());
    }
};

struct compareStudentsBySkill {
    bool operator() (const Student& s1, const Student& s2) const {
        return (s1.skillValue < s2.skillValue);
    }
};

int main() {
    unordered_map<long long, Student> id2student;
    tree <Student, null_type, compareStudentsByRank, rb_tree_tag, tree_order_statistics_node_update> studentsByRank;
    tree <Student, null_type, compareStudentsBySkill, rb_tree_tag, tree_order_statistics_node_update> studentsBySkill;

    string line, opCode;
    vector<long long> marks(5);
    long long skillValue, dValue, sID1, sID2;

    while (getline(cin, line)) {
        istringstream input(line);
        string opCode;

        input >> opCode;
        if (opCode == "ADD") {
            input >> sID1 >> marks[0] >> marks[1] >> marks[2] >> marks[3] >> marks[4] >> skillValue;
            Student newStudent(sID1, marks, skillValue);
            id2student[sID1] = newStudent;
            studentsByRank.insert(newStudent);
            studentsBySkill.insert(newStudent);
        } else if (opCode == "FIND") {
            input >> sID1 >> sID2;
            Student s1 = id2student[sID1];
            Student s2 = id2student[sID2];
            cout << llabs(studentsByRank.order_of_key(s1) - studentsByRank.order_of_key(s2)) << endl;
        } else if (opCode == "COUNT") {
            input >> sID1 >> dValue;
            skillValue = studentsBySkill.find(id2student[sID1])->skillValue;
            vector<long long> v(5);
            long long lIndex = studentsBySkill.order_of_key(Student(0, v, skillValue - dValue));
            long long rIndex = studentsBySkill.order_of_key(Student(0, v, skillValue + dValue));
            //cout << "l: " << lIndex << ", r: " << rIndex << " " << studentsBySkill.size() << endl;
            //cout << skillValue - dValue << " " << skillValue + dValue << endl;
            //cout << studentsBySkill.lower_bound(Student(0, v, skillValue - dValue))->skillValue << endl << studentsBySkill.lower_bound(Student(0, v, skillValue + dValue))->skillValue << endl;

            cout << studentsBySkill.size() - (rIndex - lIndex) << endl;
        } else if (opCode == "PRINT") {
            for(auto it = studentsByRank.begin(); it != studentsByRank.end(); it++) {
                cout << it->id << " ";
            }
            cout << endl;
        }
    }



    return 0;
}