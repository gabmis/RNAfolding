//
// Created by raph on 02/06/17.
//
#include <string>
#include <iostream>
#include "node.h"
#include <vector>

using namespace std;

node::node(string rna, string str, float x1, float x2, float y1, float y2) {

    this->rna = rna;
    this->str = str;
    this->x1 = x1;
    this->x2 = x2;
    this->y1 = y1;
    this->y2 = y2;
    this->tronc1 = new vector<string>;
    this->tronc2 = new vector<string>;
    this->circle = new vector<int>;
    this->sons = new vector<node>;
    int i = 0;
    int j = rna.length() - 1;
    while (true) {
        if (str.substr(i, 1) == "(" and str.substr(j, 1)) {
            tronc1.push_back(rna.substr(i, 1));
            tronc2.push_back(rna.substr(j, 1));
        } else { break; }//normalement quand on sort on doit pas avoir décrémenté
        j--;
        i++;
    }
    int altitude = 0;
    int index = i;
    while (true) {
        if (index == j + 1) {
            break;
        }
        if (str.substr(index, 1) == ")") {
            altidude++;
        }
        if (altitude == 0) {
            circle.push_back(index);
        }
        if (str.substr(index, 1) == "(") {
            altidude--;
        }
        index++;
    }
    index = i;
    while (true) {
        if (index == j) { break; }

        if (str.substr(index, 1) == "(") {
            altitude = -1;
            int compteur = 1;
            while (true) {
                if (str.substr(index + compteur, 1) == ")") {
                    altitude++;
                }
                if (str.substr(index + compteur, 1) == "(") {
                    altitude--;
                }
                if (altitude == 0) {
                    sons.push_back(new node(rna.substr(index,index+compteur),str.substr(index,index+compteur),1.0,1.0,1.0,1.0));
                    break;
                }
                compteur++;
            }
        }
        index++;
    }
}

void node::display(vector<int> roots) {
    cout<<endl;
    cout<<endl;
    for (int u = 0; u<roots.size(); u++){
        cout<<"node number: "<<roots[i]<<".";
    }
    cout<<endl;
    cout<<"tronc: "<<endl;
    for (int u = 0; u<tronc1.size(); u++){
        cout<<tronc1[i]<<"-";
    }
    cout<<endl;
    for (int u = 0; u<tronc2.size(); u++){
        cout<<tronc2[i]<<"-";
    }
    cout<<endl;

    cout<<"circle"<<endl;

    for (int u = 0; u<circle.size(); u++){
        if(circle[u+1]!=circle[u]+1 or u == circle.size()-1){
            cout<<str[circle[u]]<<"| |";
        }
        else{
            cout<<str[i]<<"-";
        }
    }
    cout<<endl;

    for (int u = 0; u<sons.size(); u++){
        vector<int> sons_roots = roots;
        sons_roots.push_back(u+1);
        sons[u].display(sons_roots);
    }


}
