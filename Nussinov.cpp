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
void Nussinov(string rna, vector<vector<int> >& E){
    int n = rna.length();
    //M[i][j] est le nombre maximal de paires pour
    // la sous-séquence [i;j]

    //on remplit cette matrice en utilisant la récurrence de l'algo de Nussinov

    //initialisation
    for (int p = 0; p < n; p++){
        if (p != n-1){
            E[p][p] = E[p][p+1] = 0;
        }else{
            E[p][p] = 0;
        }
    }

    int cas1;
    int cas2;
    int cas3;
    int cas4;
    int maximum;

    //induction

    for (int i = n - 3; i > -1; i--){
        for(int j = i + 2; j < n; j++){
            maximum = 0;
            //on calcule les différents cas possibles
            //on essaye d'apparier i et j
            cas1 = E[i + 1][j - 1] + match(rna.substr(i, 1), rna.substr(j, 1));
            //on recalcule le max
            maximum = fmax(maximum, cas1);
            //i est ajouté sans etre apparié
            cas2 = E[i + 1][j];
            //on recalcule le max
            maximum = fmax(maximum, cas2);
            //j est ajouté sans être apparié
            cas3 = E[i][j - 1];
            //on recalcule le max
            maximum = fmax(maximum, cas3);
            //on bifurque
            cas4 = 0;
            for (int k = i + 1; k < j - 1; k++){
                if(E[i][k] + E[k + 1][j] > cas4) {
                    cas4 = E[i][k] + E[k + 1][j];
                }
            }
            //on garde le max
            E[i][j] = fmax(maximum, cas4);
        }
    }
}
//Etant donné la matrice du nombre maximal de paire cette fonction renvoie
// l'ensemble des solutions parenthésées sous forme d'un vecteur de string
void traceBack(string rna, vector< vector<int> > M, int i, int j,
               vector < vector< vector< string > > >  &expressions, bool one_solution = false){
    int n = rna.length();
    if(i < j){
        if(!one_solution) {
            // on a rajouté i et j
            if (M[i][j] == M[i + 1][j - 1] + match(rna.substr(i, 1), rna.substr(j, 1))) {
                traceBack(rna, M, i + 1, j - 1, expressions, one_solution);
                //sans appariement
                if (match(rna.substr(i, 1), rna.substr(j, 1)) == 0) {
                    //on rajoute des points
                    keepOne(expressions[i + 1][j - 1]);
                    for (string str : expressions[i + 1][j - 1]) {
                        expressions[i][j].push_back("." + str + ".");
                    }
                //avec appariement
                } else {
                    keepOne(expressions[i + 1][j - 1]);
                    for (string str : expressions[i + 1][j - 1]) {
                        expressions[i][j].push_back("(" + str + ")");
                    }
                }
            }

            //on a rajouté i sans appariement
            if (M[i][j] == M[i + 1][j]) {
                traceBack(rna, M, i + 1, j, expressions, one_solution);
                // on rajoute un point à gauche
                keepOne(expressions[i + 1][j]);
                for (string str : expressions[i + 1][j]) {
                    expressions[i][j].push_back("." + str);
                }
            }

            //on a rajouté j sans appariement
            if (M[i][j] == M[i][j - 1]) {
                traceBack(rna, M, i, j - 1, expressions, one_solution);
                //on rajoute un point à droite
                keepOne(expressions[i][j - 1]);
                for (string str : expressions[i][j - 1]) {
                    expressions[i][j].push_back(str + ".");
                }
            }

            //on a uni deux structures
            for (int k = i + 1; k < j - 1; k++) {
                if (M[i][j] == M[i][k] + M[k + 1][j]) {
                    traceBack(rna, M, i, k, expressions, one_solution);
                    traceBack(rna, M, k + 1, j, expressions, one_solution);
                    keepOne(expressions[i][k]);
                    keepOne(expressions[k + 1][j]);
                    for (string str1 : expressions[i][k]) {
                        for (string str2 : expressions[k + 1][j]) {
                            expressions[i][j].push_back(str1 + str2);
                        }
                    }
                }
            }

        //dans le cas où le string est trop volumineux on cherche une solution arbitraire
        }else{
            // on a rajouté i et j
            if (M[i][j] == M[i + 1][j - 1] + match(rna.substr(i, 1), rna.substr(j, 1))) {
                traceBack(rna, M, i + 1, j - 1, expressions, one_solution);
                //sans appariement
                if (match(rna.substr(i, 1), rna.substr(j, 1)) == 0) {
                    //on rajoute des points
                    expressions[i][j].push_back("." + expressions[i + 1][j - 1][0] + ".");
                    cout << 1.1;
                //avec appariement
                } else {
                    expressions[i][j].push_back("(" + expressions[i + 1][j - 1][0] + ")");
                    cout << 1.2;
                }
            }

            //on a rajouté i sans appariement
            else if (M[i][j] == M[i + 1][j]) {
                traceBack(rna, M, i + 1, j, expressions, one_solution);
                // on rajoute un point à gauche
                expressions[i][j].push_back("." + expressions[i + 1][j][0]);
                cout << 2;
            }

            //on a rajouté j sans appariement
            else if (M[i][j] == M[i][j - 1]) {
                traceBack(rna, M, i, j - 1, expressions, one_solution);
                //on rajoute un point à droite
                expressions[i][j].push_back(expressions[i][j - 1][0] + ".");
                cout << 3;
            }

            //on a uni deux structures
            else {
                for (int k = i + 1; k < j - 1; k++) {
                    bool done;
                    if (M[i][j] == M[i][k] + M[k + 1][j] && !done) {
                        traceBack(rna, M, i, k, expressions, one_solution);
                        traceBack(rna, M, k + 1, j, expressions, one_solution);
                        expressions[i][j].push_back(expressions[i][k][0] + expressions[k + 1][j][0]);
                        cout << 4;
                        done = true;
                    }
                }
            }
        }
    }
}

int main(int argc, char **argv) {
    string rnaseq = argv[1];
    string yesno;
    cout << "Calculations might take some time with big sequences. "
            "Would you like to compute a unique arbitrary solution ? (type yes or no)" << endl;
    cin >> yesno;
    bool unique = yesno == "yes" ? true : false ;
    cout << unique << endl;
    RNA rna = RNA(rnaseq);
    Nussinov(rna.rna, rna.maxPairs);
    traceBack(rna.rna, rna.maxPairs, 0, (int)rna.rna.length() - 1, rna.structures, unique);
    rna.display();
}
