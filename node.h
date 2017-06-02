//
// Created by raph on 02/06/17.
//

#ifndef RNA_2D_FOLDING_NODE_H
#define RNA_2D_FOLDING_NODE_H

#endif //RNA_2D_FOLDING_NODE_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/* Linked list structure */
class RNA {
public:
    string rna;
    string str;
    float x1;
    float x2;
    float y1;
    float y2;
    vector<string> tronc1;
    vector<string> tronc2;
    vector<int> circle;
    vector<node> sons;
    node(string rna, string str, float x1, float x2, float y1, float y2);
    void display();
}
;