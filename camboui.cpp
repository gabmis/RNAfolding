//
// Created by raph on 02/06/17.
//
#include <string>
#include <iostream>
#include "node.h"
#include <vector>

using namespace std;

int main() {
    string rna_test = "AZERTYUIOPQSDFGHJKLMWXCVBN";
    string str_test = "(((((....(......)....)))))";
    vector<int> roots_test;
    roots_test.push_back(1);
    node test = node(rna_test, str_test, 1.0,1.0,1.0,1.0);
    test.display(roots_test);
    return 0;
}



