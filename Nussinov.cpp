#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "RNA.h"
using namespace std;

//TODO OPTIMIZE TIME COMPLEXITY
void keepOne(vector<string>&  v){
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
}
//handy fucntion that says if two bases can be paired

int match(string a, string b){
    if( a == "C" && b == "G"){
        return 1;
    }
    else if( a == "G" && b == "C"){
        return 1;
    }
    else if( a == "A" && b == "U"){
        return 1;
    }
    else if( a == "U" && b == "A") {
        return 1;
    }
    else{
        return 0;
    }


}

//implementing the Nussinov algorithm
void Nussinov(string rna, vector<vector<int> >& M){
    int n = rna.length();
    //M[i][j] est le nombre maximal de paires pour
    // la sous-séquence [i;j]

    //on remplit cette matrice en utilisant la récurrence de l'algo de Nussinov

    //initialisation
    for (int p = 0; p < n; p++){
        if (p != n-1){
            M[p][p] = M[p][p+1] = 0;
        }else{
            M[p][p] = 0;
        }
    }

    // initialisation et induction
    int cas1;
    int cas2;
    int cas3;
    int cas4;
    int maximum;
    for (int i = n - 3; i > -1; i--){
        for(int j = i + 2; j < n; j++){
            maximum = 0;
            //on calcule les différents cas possibles
            //on essaye d'apparier i et j
            cas1 = M[i + 1][j - 1] + match(rna.substr(i, 1), rna.substr(j, 1));
            //on recalcule le max
            maximum = fmax(maximum, cas1);
            //i est ajouté sans etre apparié
            cas2 = M[i + 1][j];
            //on recalcule le max
            maximum = fmax(maximum, cas2);
            //j est ajouté sans être apparié
            cas3 = M[i][j - 1];
            //on recalcule le max
            maximum = fmax(maximum, cas3);
            //on bifurque
            cas4 = 0;
            for (int k = i + 1; k < j - 1; k++){
                if(M[i][k] + M[k + 1][j] > cas4) {
                    cas4 = M[i][k] + M[k + 1][j];
                }
            }
            //on garde le max
            M[i][j] = fmax(maximum, cas4);
        }
    }
}
//Etant donné la matrice du nombre maximal de paire cette fonction renvoie
// l'ensemble des solutions parenthésées sous forme d'un vecteur de string
void traceBack(string rna, vector<vector<int> > M, int i, int j, vector<vector<vector<string> > >& expressions){
    int n = rna.length();
    if (i < j){

        // on a rajouté i et j
        if (M[i][j] == M[i + 1][j - 1] + match(rna.substr(i, 1), rna.substr(j, 1))){
            traceBack(rna, M, i + 1, j - 1, expressions);
            //sans appariement
            if (match(rna.substr(i, 1), rna.substr(j, 1)) == 0){
                //on rajoute des points
                keepOne(expressions[i + 1][j - 1]);
                for (string str : expressions[i + 1][j - 1]){
                    expressions[i][j].push_back("." + str + ".");
                }
            }else{
                keepOne(expressions[i + 1][j - 1]);
                for (string str : expressions[i + 1][j - 1]){
                    expressions[i][j].push_back("(" + str + ")");
                }
            }
        }

        //on a rajouté i sans appariement
        if (M[i][j] == M[i + 1][j]){
            traceBack(rna, M, i + 1, j, expressions);
            // on rajoute un point à gauche
            keepOne(expressions[i + 1][j]);
            for (string str : expressions[i + 1][j]){
                expressions[i][j].push_back("." + str);
            }
        }
        //on a rajouté j sans appariement
        if (M[i][j] == M[i][j - 1]){
            traceBack(rna, M, i, j - 1, expressions);
            //on rajoute un point à droite
            keepOne(expressions[i][j - 1]);
            for (string str : expressions[i][j - 1]){
                expressions[i][j].push_back(str + ".");
            }
        }
        for (int k = i + 1; k < j - 1; k++){
            if(M[i][j] == M[i][k] + M[k + 1][j]){
                traceBack(rna, M, i, k, expressions);
                traceBack(rna, M, k + 1, j, expressions);
                keepOne(expressions[i][k]);
                keepOne(expressions[k + 1][j]);
                for (string str1 : expressions[i][k]){
                    for (string str2 : expressions[k + 1][j]) {
                        expressions[i][j].push_back(str1 + str2);
                    }
                }
            }
        }
    }
}

int main(int argc, char **argv) {
    string rnaseq = argv[1];
    RNA rna = RNA(rnaseq);
    Nussinov(rna.rna, rna.maxPairs);
    traceBack(rna.rna, rna.maxPairs, 0, (int)rna.rna.length() - 1, rna.structures);
    rna.display();
}
