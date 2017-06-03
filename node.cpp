#include <string>
#include <iostream>
#include "node.h"
#include <vector>
#include <math.h>
#include <fstream>


using namespace std;
float delta = 1.0;

node::node(string rna, string str, float x1, float x2, float y1, float y2) {
    this->rna = rna;
    this->str = str;
    this->x1 = x1;
    this->x2 = x2;
    this->y1 = y1;
    this->y2 = y2;
    this->tronc1 = vector<string>();
    this->tronc2 = vector<string>();
    this->circle = vector<int>();
    this->sons = vector<node>();
    int i = 0;
    int j = rna.length() - 1;
    while (true) {
        if (str.substr(i, 1) == "(" and str.substr(j, 1) == ")") {
            tronc1.push_back(rna.substr(i, 1));
            tronc2.push_back(rna.substr(j, 1));
        }
        else { break; }//normalement quand on sort on doit pas avoir décrémenté
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
            altitude++;
        }
        if (altitude == 0) {
            circle.push_back(index);
        }
        if (str.substr(index, 1) == "(") {
            altitude--;
        }
        index++;
    }
    index = i;
    int numero_dans_le_cercle = 0;
    int altitude_cercle = 0;
    while (true) {
        if (index == j) { break;}

        if (str.substr(index, 1) == ")") {
            altitude_cercle ++;
        }

        if(altitude_cercle == 0){
            numero_dans_le_cercle ++;
        }
        if (str.substr(index, 1) == "(") {
            altitude_cercle --;
        }

        if (altitude_cercle==-1 and str.substr(index, 1) == "(") {
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

                    float delta_x = (y1-y2)*delta/(sqrt(pow((y1-y2),2) + pow((x1-x2),2)));
                    float delta_y = -(x1-x2)*delta/(sqrt(pow((y1-y2),2) + pow((x1-x2),2)));
                    float current_x = 0.0;
                    float current_y = 0.0;
                    float current_x2 = 0.0;
                    float current_y2 = 0.0;
                    float centre_x;
                    float centre_y;

                    centre_x = (x1+x2)/2 + (tronc1.size()-1)*delta_x + (circle.size()+2)*delta*delta_x/(2*3.1416);
                    centre_y = (y1+y2)/2 + (tronc1.size()-1)*delta_y + (circle.size()+2)*delta*delta_y/(2*3.1416);

                    current_x = x1+ (tronc1.size()-1)*delta_x - centre_x;
                    current_y = y1+ (tronc1.size()-1)*delta_y - centre_y;


                    float stock_x;
                    float stock_y;
                    float alpha = (2*3.1416/(circle.size()+2));

                    stock_x = current_x;
                    stock_y = current_y;
                    current_x = cos(numero_dans_le_cercle*alpha) * stock_x + sin(numero_dans_le_cercle*alpha)*stock_y;
                    current_y = cos(numero_dans_le_cercle*alpha) * stock_y - sin(numero_dans_le_cercle*alpha)*stock_x;
                    current_x += centre_x;
                    current_y += centre_y;

                    numero_dans_le_cercle++;

                    current_x2 = cos(numero_dans_le_cercle*alpha) * stock_x + sin(numero_dans_le_cercle*alpha)*stock_y;
                    current_y2 = cos(numero_dans_le_cercle*alpha) * stock_y - sin(numero_dans_le_cercle*alpha)*stock_x;
                    current_x2 += centre_x;
                    current_y2 += centre_y;

                    numero_dans_le_cercle--;

                    sons.push_back(node(rna.substr(index,compteur+1),str.substr(index,compteur+1),current_x,current_x2,current_y,current_y2));
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
    cout<<"node number: ";
    for (int u = 0; u<roots.size(); u++){
        cout<<roots[u]<<".";
    }
    cout<<endl;
    cout<<"tronc: "<<endl;
    for (int u = 0; u<tronc1.size(); u++){
        cout<<tronc1[u]<<"-";
    }
    cout<<endl;
    for (int u = 0; u<tronc2.size(); u++){
        cout<<tronc2[u]<<"-";
    }
    cout<<endl;

    cout<<"circle"<<endl;

    for (int u = 0; u<circle.size(); u++){
        if(circle[u+1]!=circle[u]+1 or u == circle.size()-1){
            cout<<rna[circle[u]]<<"| |";
        }
        else{
            cout<<rna[circle[u]]<<"-";
        }
    }
    cout<<endl;

    for (int u = 0; u<sons.size(); u++){
        vector<int> sons_roots = roots;
        sons_roots.push_back(u+1);
        sons[u].display(sons_roots);
    }

    //partie enregistrement de coordonnées
    float delta_x = (y1-y2)*delta/(sqrt(pow((y1-y2),2) + pow((x1-x2),2)));
    float delta_y = -(x1-x2)*delta/(sqrt(pow((y1-y2),2) + pow((x1-x2),2)));
    float current_x = 0.0;
    float current_y = 0.0;
    float centre_x;
    float centre_y;

    ofstream myfile ("letters.txt",ios::out | ios::app);
    for (int u = 0; u<tronc1.size(); u++){
        current_x = x1 + u*delta_x;
        current_y = y1 + u*delta_y;


        myfile <<tronc1[u]<<"\n";
        myfile <<current_x<<"\n";
        myfile <<current_y<<"\n";
    }
    for (int u = 0; u<tronc2.size(); u++){
        current_x = x2 + u*delta_x;
        current_y = y2 + u*delta_y;
        myfile <<tronc2[u]<<"\n";
        myfile <<current_x<<"\n";
        myfile <<current_y<<"\n";
    }

    centre_x = (x1+x2)/2 + (tronc1.size()-1)*delta_x + (circle.size()+2)*delta*delta_x/(2*3.1416);
    centre_y = (y1+y2)/2 + (tronc1.size()-1)*delta_y + (circle.size()+2)*delta*delta_y/(2*3.1416);

    current_x = x1+ (tronc1.size()-1)*delta_x - centre_x;
    current_y = y1+ (tronc1.size()-1)*delta_y - centre_y;

    float stock_x = current_x;
    float stock_y = current_y;
    float alpha = (2*3.1416/(circle.size()+2));
    for (int u = 0; u<circle.size(); u++) {
        current_x = cos((u+1)*alpha) * stock_x + sin((u+1)*alpha)*stock_y;
        current_y = cos((u+1)*alpha) * stock_y - sin((u+1)*alpha)*stock_x;
        myfile <<rna[circle[u]]<<"\n";
        myfile <<current_x+centre_x<<"\n";
        myfile <<current_y+centre_y<<"\n";
    }

    myfile.close();

    }



