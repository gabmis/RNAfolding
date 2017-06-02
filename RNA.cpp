#include "RNA.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//TODO:PROPER DISPLAY
//Constructor that allows to initiate correctly the vectors that we will use in Nussinov
RNA::RNA(string rna) {

    this->rna = rna;

    int n = (int) rna.length();

    for (int i = 0; i < n; i++){
        vector<int> row1;
        vector< vector<string> > row2;
        for (int j = 0; j < n; j++){
            row1.push_back(0);
            vector<string> component;
            if (i == j){
                component.push_back(".");
            }
            if (i == j - 1){
                component.push_back("..");
            }
            row2.push_back(component);
        }
        maxPairs.push_back(row1);
        structures.push_back(row2);
    }
}

void RNA::display() {
    cout << rna << endl;
    vector<string> res = structures[0][rna.length() - 1];
    sort(res.begin(), res.end());
    res.erase(unique(res.begin(), res.end()), res.end());
    /*for(string s : res){
        cout << s << endl;
    }*/
    cout << "Maximum number of pairs : " << maxPairs[0][(int)rna.size() - 1] << endl;
    cout << "Number of optimal solutions : " << res.size() << endl;
}



