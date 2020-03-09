#ifndef __DESIGN_H__
#define __DESIGN_H__

class Student {
    public:
    long long id;                               // id
    vector<long long> marks;                    // 5-membered vector of marks
    long long skillValue;                       // skill value
    long long subtreeSize;                      // stores size of subtree rooted at this
    long long height;
    Student* left;                              // pointer to left subtree
    Student* right;                             // pointer to right subtree
    Student* parent;                            // pointer to parent

    Student(long long i, vector<long long> m, long long sk);
};

class avlTree {                                 // augmented AVL tree which stores sizes of subtrees rooted at nodes
    private:
    unordered_map<long long, vector<long long> > id2marks;  // hashtable mapping from id to mark vector
    Student* root;                              // pointer to root node

    public:
    void insert(Student s);                     // inserts new Student into AVL tree
    long long find(long long id1, long id2);    // returns difference in ranks
    long long count(long long i, long long d);  // implement the required count operation
    void print();                               // print avl tree in inorder traversal order
    avlTree();                                  // constructor
};

#endif