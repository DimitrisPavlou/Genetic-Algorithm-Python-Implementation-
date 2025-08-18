#include <bits/stdc++.h>
#include "Matrix.hpp"
#include "GA.hpp"
#include "objectives.hpp"

int main(){ 

    ObjectiveFunction obj = powel; 

    int population_size = 750; 
    int max_generations = 100;  
    int num_variables = 2; 
    const std::vector<double> lb = {-5.0, -5.0}; 
    const std::vector<double> ub = {5.0,5.0};
    float p_crossover = 0.8; 
    float mutation_rate = 0.01;
    int num_elites = 5; 
    int print_every = 1;
    std::pair<std::vector<double>, float> solution = GA(obj, population_size, max_generations, num_variables, lb, ub, p_crossover, mutation_rate, num_elites, print_every);
    
}