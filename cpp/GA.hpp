#pragma once 
#include <bits/stdc++.h>
#include "Matrix.hpp"
#include "objectives.hpp"

Matrix crossover(int population_size, Matrix& Parents, float p_crossover, int num_variables); 

void mutation(Matrix& Children, int population_size, int num_variables, float mutation_rate, int generation, int max_generations, int num_elites);

Matrix tournament_selection(Matrix& population, int population_size, std::vector<float>& fitness, int num_elites, int k); 

std::pair<std::vector<double>, float> GA(ObjectiveFunction objective, int population_size, int max_generations, int num_variables, const std::vector<double>& lb, const std::vector<double>& ub,
                            float p_crossover, float mutation_rate, int num_elites, int print_every);



