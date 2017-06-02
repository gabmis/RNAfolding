//
// Created by raph on 02/06/17.
//
#include <string>
#include <iostream>
#include "node.h"
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;
float delta2 = 1.0;

int main() {
    ofstream myfile1 ("letters.txt", ios::trunc);
    myfile1.close();

    //l'exemple que nous utilisions pour débugger notre programme
    //string rna_test = "XAAAAXBBBBBBBBBBBTTTTTTTTUUUUUUUZZZZZOOOOOOOOZZZZZUUUUUUUUUTTTTTTTTBBBBBBBBBBBBBBBSSSSSEEESSSSSBBBBBBBBBBBBBBBBBBBBAAAAX";
    //string str_test = "(((((............((((((((.......(((((........))))).........))))))))...............(((((...)))))....................)))))";

    string rna_test = "UUCUAUAGCUCAGUUGGUAGGCGAGCGCACCCUUGGUAAGGGUGAGGUCGGCAGUUCCAAUCUGCCUAUCAGCACCACAA";
    string str_test = "(((((.(.((.))))(((.....(((((((((((...)))))))(..)))((((((..)).)))))))((.).)))))))";


    vector<int> roots_test;
    roots_test.push_back(1);
    node test = node(rna_test, str_test, 0.0, delta2, 0.0, 0.0);
    test.display(roots_test);

    string command = "python3 print_tree.py";
    system(command.c_str());

    return 0;
}



