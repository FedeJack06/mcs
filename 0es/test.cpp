#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Vector3.h"

bool comparison(Vector3 a, Vector3 b){ //definisce la comparazione di sort
    return a.module()>b.module();
}

int main(){
    std::ifstream input("punti.dat");
    double x,y,z;
    std::vector<Vector3> vector;
    while (input >> x >> y >> z){
        //Vector3 v(x,y,z);
        vector.push_back(Vector3(x,y,z)); //meglio che creare prima l'oggetto v
    }
    std::sort(vector.begin(),vector.end(), comparison);  //or using default comparison (operator <) only 2 parameters

    for(int i=0; i<vector.size(); i++){  //output vector from greater module
        std::cout << vector[i] << std::endl;
    }

    Vector3 SUM; //costruttore -> (0,0,0)
    for(auto s:vector){ //range-based for loop [attr(optional) for ( init-statement(optional) range-declaration : range-expression )]
        SUM = SUM + s; //problem
    }
    std::cout << "vettore somma " << SUM << std::endl;
    return 0;
}