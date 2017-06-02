#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>
#include <math.h>
using namespace std;





//OVERLOADING OF OPERATOR << FOR VECTOR<T>,

//tested
template < class T >
inline ostream& operator << (ostream& os, const vector<T>& v)
{
    os << "[";
    for (typename vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << " " << *ii;
    }
    os << " ]";
    os << endl;
    return os;
}





//FONCTION QUI CRÉE L'ENSEMBLE DES PAIRES SOUS FORME DE VECTEURS DE PAIRES

//tested
vector< vector<int> > Pairs(string structure){
    if (structure.empty()){
        cout << "empty stucture" << endl;
    }
    vector< vector<int> > pairs;
    vector<int> stack;
    int i = 0;
    for (char c : structure){
        if(c == '('){
            stack.push_back(i);
        }
        else if(c == ')'){
            vector<int> pair;
            pair.push_back(stack.back());
            stack.pop_back();
            pair.push_back(i);
            pairs.push_back(pair);
        }
        i++;

    }
    return pairs;
}





//FONCTION QUI RETOURNE LA DIFFÉRENCE ENSEMBLISTE DES PAIRES

//tested
string difference(string A, string B){
    for(vector<int> pairA : Pairs(A)){
        for(vector<int> pairB : Pairs(B)){
            if(pairA == pairB){
                A[pairA[0]] = A[pairA[1]] = '.';
            }
        }
    }
    return A;
}





//FONCTION QUI RETOURNE L'ENSEMBLE DES PAIRES EN CONFLIT AVEC UNE PAIRE DONNÉE

//tested
vector< vector<int> > Conflit(int i, int j, string structure){
    vector< vector<int> > conflicts;
    for (vector<int> pair : Pairs(structure)){
        if((pair[0] <= i && i <= pair[1] && pair[1] <= j) || (i <= pair[0] && pair[0] <= j && j <= pair[1])){
            conflicts.push_back(pair);
        }
    }
    return conflicts;
}





//IMPLÉMENTATION DE L'ALGORITHME GLOUTON DE MORGANHIGGS

//tested
vector< string > MorganHiggs(string A, string B){
    assert(A.size() > 0 && B.size() > 0);
    vector< string > path;
    string S = A;
    string BS;
    vector< vector<int> > C;
    path.push_back(S);
    while (S != B){

        //ON CHERCHE LA PAIRE QUI MINIMISE LA TAILLE DE CONFLIT

        BS = difference(B, S);
        vector <int> min;
        min.clear();
        int sizemin = A.size();
        for (vector<int> pair : Pairs(BS)){
            if (Conflit(pair[0], pair[1], S).size() < sizemin){
                sizemin = C.size();
                min = pair;
            }
        }

        C = Conflit(min[0], min[1], S);

        //ON SUPPRIME LES PAIRES DE C DE A

        for (vector<int> pair : C){
            S[pair[0]] = S[pair[1]] = '.';
            path.push_back(S);
        }

        //ON AJOUTÉ LES PAIRES NON CONFLICTUELLES DE B - Sk ET ON LES ENLÈVE DE B-Sk

        BS = difference(B, S);
        for (vector<int> pair : Pairs(BS)){
            if (Conflit(pair[0], pair[1], S).size() == 0){
                S[pair[0]] = '(';
                S[pair[1]] = ')';
                path.push_back(S);
            }
        }
    }
    return path;
}





//RETOURNE LA MATRICE DES CHEMINS DIRECTS ENTRE STRUCTURES

//tested
vector< vector < vector< string > > > DirectPaths (vector< string > structures){
    assert(structures.size() > 0);
    vector< vector< vector< string > > > paths;
    int i = 0;
    int j = 0;
    for (string vi : structures){
        vector< vector< string > > row;
        for (string vj : structures){
            row.push_back(MorganHiggs(vi, vj));
            cout << i << " " << j << endl;
            j++;
        }
        i++;
        paths.push_back(row);
    }
    return paths;
}





//RETOURNE L'ÉNERGIE D'UNE STRUCTURE

//tested
double Energy (string structure, string rna){
    double energy = 0;
    for (vector<int> pair : Pairs(structure)){
        if(rna[pair[0]] == 'A' && rna[pair[1]] == 'U') {
            energy -= 0.25;
        }
        else if(rna[pair[0]] == 'U' && rna[pair[1]] == 'A') {
            energy -= 0.25;
        }
        else if(rna[pair[0]] == 'C' && rna[pair[1]] == 'G'){
            energy -= 1.4;
        }
        else if( rna[pair[0]] == 'G' && rna[pair[1]] == 'C'){
            energy -= 1.4;
        }
        else if(rna[pair[0]] == 'G' && rna[pair[1]] == 'U'){
            energy -= 0.1;
        }
        else if( rna[pair[0]] == 'U' && rna[pair[1]] == 'G'){
            energy -= 0.1;
        }
    }
    return energy;
}





//RETOURNE L'ÉNERGIE D'UN CHEMIN D'UNE STRUCTURE À UNE AUTRE

//tested
double PathEnergy (vector < string > path, string rna){
    double maxEnergy = -1.4 * rna.length();
    for (string structure : path){
        maxEnergy = fmax(maxEnergy, Energy(structure, rna));
    }
    return maxEnergy;
}




//RETOURNE LA MATRICE DES ENERGIES DES CHEMINS DE LA FERMETURE TRANSITIVE (CHEMINS DIRECTS OU INDIRECTS)

//TODO: A TESTER
vector< vector<double> > IndirectPaths (vector< vector < vector< string > > >& Paths, string rna,
                    bool display = 0){
    //TODO
    int n = Paths.size();
    vector< vector<double> > Energies(n, vector<double>(n, 0));

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            Energies[i][j] = PathEnergy(Paths[i][j], rna);
        }
    }

    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if ((Energies[i][k] < Energies[i][j] || Energies[k][j] < Energies[i][j])
                        && k != i && k != j){
                    Energies[i][j] = fmax(Energies[i][k], Energies[k][j]);
                    cout << "(" << i << ", " << k << ", " << j << ")" << endl;
                    if (display){
                        Paths[i][j].clear();
                        Paths[i][j].insert (Paths[i][j].begin(),
                                                   Paths[i][k].begin(), Paths[i][k].end());
                        Paths[i][j].insert (Paths[i][j].end(),
                                                   Paths[k][j].begin(), Paths[k][j].end());
                    }
                }
            }
        }
    }
    return Energies;
}





//FONCTION QUI PERMET DE GÉRER L'INPUT VIA UN FICHIER .TXT

//tested
vector<string> readFile(string filename){
    ifstream file(filename);
    vector<string> lines;
    string line;
    if (!file.is_open())
        perror("error while opening file");
    while(getline(file, line)) {
        lines.push_back(line);
    }
    if (file.bad())
        perror("error while reading file");
    return lines;
}





//RETOURNE LE STRING DONNÉ EN INPUT

//tested
string getRNA(vector<string> input){
    return input[0];
}





//RETOURNE LES STRUCTURES DONNÉES EN INPUT

//tested
vector< string > getStructures(vector<string> input){
    vector< string > structures;
    vector< string >::iterator it;
    for(it = input.begin() + 1; it != input.end(); ++it){
        structures.push_back(*it);
    }
    return structures;
}





int main(int argc, char **argv){
    string filename = argv[1];
    vector<string> input = readFile(filename);
    string rna = getRNA(input);
    vector< string > structures = getStructures(input);
    vector< vector < vector<string> > > paths = DirectPaths(structures);
    //cout << paths << endl;
    vector< vector<double> > energies = IndirectPaths (paths, rna, true);
    cout << energies << endl;
    //cout << paths << endl;
    return 0;
}
