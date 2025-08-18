#include "objectives.hpp" 
#include "bits/stdc++.h"

float sphere(const std::vector<double>& x){

    float result = 0; 
    for(int i=0; i<x.size(); i++){
        result += x[i]*x[i]; 
    }
    return result; 
}

float banana(const std::vector<double>& x){
    return 100 * std::pow((x[1] - std::pow(x[0], 2)), 2) + std::pow(1 - x[0], 2);
}


float powel(const std::vector<double>& x){
    return std::pow(x[0] + 10*x[1], 2) + 5*std::pow(x[2]- x[3], 2) + std::pow(x[1] - 2*x[2], 2) + 10*std::pow(x[0]-x[3],2);
}