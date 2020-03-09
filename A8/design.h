#ifndef __DESIGN_H__
#define __DESIGN_H__
#include <bits/stdc++.h>
#define MAX_STUDENTS

using namespace std;

class Student {                 // student
    public:                     // public
    Student(int i, int a, char g, string m, int c); // constructor
    int id;                     // id of student
    int age;                    // age of student
    char gender;                // gender of student
    string motherTongue;        // mother tongue of student
    int CGPA;                   // CGPA of student
};

bool canBeTogether(Student &s1, Student &s2);   // checks if two students can both be chosen
void initializeGraph(vector<Student> &students);// initializes graph

vector<Student> students;                       // list of all students such student of id x is stored at position x
bool graph[MAX_STUDENTS + 1][MAX_STUDENTS + 1]; // adjacency matrix


#endif