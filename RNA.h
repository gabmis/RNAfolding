#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#endif //DOUBLELINKEDLIST_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/* Linked list structure */
class RNA {
    public:
    string rna;
    vector< vector<int> > maxPairs;
    vector< vector< vector<string> > > structures;
    RNA(string rna);
    void display();
};



