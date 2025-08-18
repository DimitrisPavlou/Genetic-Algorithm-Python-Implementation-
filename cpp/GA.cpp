// Fixed GA.cpp
#include "bits/stdc++.h"
#include "GA.hpp" 
#include "Matrix.hpp"
#include <algorithm>  

static thread_local std::mt19937 rng(std::random_device{}());

double random_0_to_1() {
    static thread_local std::mt19937 gen(std::random_device{}());
    static std::uniform_real_distribution<double> dis(0.0, 1.0);
    return dis(gen);
}

int random_int(int a, int b) {
    static thread_local std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dis(a, b);
    return dis(gen);
}

std::vector<int> random_indices_without_replacement(int n, int k) {
    if (n <= 0 || k < 0 || k > n) throw std::invalid_argument("bad arguments");
    std::vector<int> pool(n);
    for (int i = 0; i < n; ++i) pool[i] = i;

    for (int i = 0; i < k; ++i) {
        std::uniform_int_distribution<int> dist(i, n - 1);
        int j = dist(rng);
        std::swap(pool[i], pool[j]);
    }

    pool.resize(k);
    return pool;
}

Matrix crossover(int population_size, Matrix& Parents, float p_crossover, int num_variables) {
    Matrix children(population_size, num_variables);
    int N = population_size - (population_size % 2);

    for (int i = 0; i < N; i += 2) {
        Matrix parent1 = Parents.get_row(i);
        Matrix parent2 = Parents.get_row(i + 1);
        Matrix child1 = parent1;
        Matrix child2 = parent2;

        if (random_0_to_1() < p_crossover) {
            int cp = random_int(0, num_variables);
            for (int j = 0; j < num_variables; ++j) {
                if (j < cp) {
                    child1[0][j] = parent1[0][j];
                    child2[0][j] = parent2[0][j];
                } else {
                    child1[0][j] = parent2[0][j];
                    child2[0][j] = parent1[0][j];
                }
            }
        }

        children[i] = child1[0];
        children[i + 1] = child2[0];
    }

    if (population_size % 2 == 1) {
        children[population_size - 1] = Parents[population_size - 1];
    }

    return children;
}

void mutation(Matrix& children, int population_size, int num_variables, 
              float mutation_rate, int generation, int max_generations, int num_elites) {
    static thread_local std::mt19937 rng(std::random_device{}());

    const double initial_variance = 3.0;
    double fraction = 0.0;
    if (max_generations > 0) {
        fraction = static_cast<double>(generation) / static_cast<double>(max_generations);
    }
    //double variance_decay = initial_variance * (1.0 - fraction);
    //variance_decay = std::max(variance_decay, 0.7);

    std::uniform_real_distribution<double> uni(0.0, 1.0);
    std::normal_distribution<double> norm(0.0,1);// std::sqrt(variance_decay));

    if (num_elites < 0) num_elites = 0;
    if (num_elites > population_size) num_elites = population_size;

    for (int i = num_elites; i < population_size; ++i) {
        for (int j = 0; j < num_variables; ++j) {
            if (uni(rng) < mutation_rate) {
                children[i][j] += norm(rng);
            }
        }
    }
}

Matrix tournament_selection(Matrix& population, int population_size, 
                          std::vector<float>& fitness, int num_elites = 0, int k = 10) {
    std::pair<int, int> dims = population.size();
    Matrix parents(dims.first, dims.second);

    int num_parents = population_size;
    for (int i = 0; i < num_parents; i++) {
        auto rand_indices = random_indices_without_replacement(population_size, k);
        
        // Find best individual in tournament
        int best_index = rand_indices[0];
        float best_value = fitness[rand_indices[0]];
        
        for (int idx : rand_indices) {
            if (fitness[idx] < best_value) { // minimize
                best_value = fitness[idx];
                best_index = idx;
            }
        }
        
        parents[i] = population[best_index];
    }
    return parents;
}

std::pair<std::vector<double>, float> GA(
    ObjectiveFunction objective, 
    int population_size, 
    int max_generations, 
    int num_variables,
    const std::vector<double>& lb, 
    const std::vector<double>& ub,
    float p_crossover, 
    float mutation_rate,
    int num_elites, 
    int print_every
) {
    Matrix population = random_population_uniform_per_variable(population_size, num_variables, lb, ub);
    
    std::vector<double> best_sol;
    float best_fitness = std::numeric_limits<float>::max();
    
    for (int j = 1; j <= max_generations; j++) {
        // Calculate fitness for current population
        std::vector<float> fitness;
        fitness.reserve(population_size);
        
        for (int i = 0; i < population_size; i++) {
            fitness.push_back(objective(population[i]));
        }

        // Find best solution in current generation
        auto min_it = std::min_element(fitness.begin(), fitness.end());
        int best_index = std::distance(fitness.begin(), min_it);
        float current_best_fitness = *min_it;
        
        if (current_best_fitness < best_fitness) {
            best_fitness = current_best_fitness;
            best_sol = population[best_index];
        }

        // Print progress
        if (j % print_every == 0) {
            std::cout << "Generation: " << j << " | Best Fitness= " << best_fitness 
                      << " | Best Solution: [ ";
            for (size_t i = 0; i < best_sol.size(); i++) {
                std::cout << best_sol[i] << " ";
            }
            std::cout << "]" << std::endl;
        }

        // If not last generation, create next generation
        if (j < max_generations) {
            Matrix parents = tournament_selection(population, population_size, fitness, num_elites, 30);
            Matrix children = crossover(population_size, parents, p_crossover, num_variables);
            mutation(children, population_size, num_variables, mutation_rate, j, max_generations, num_elites);
            population = children;
        }
    }

    return std::make_pair(best_sol, best_fitness);
}