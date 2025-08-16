import numpy as np 
from Selection import tournament_selection , roulette_wheel_selection
from Crossover import crossover
from Mutation import bitstring_mutation


def classic_ga(objective_function , population_size , n_bits, max_generations, p_crossover=0.7 , mutation_rate=0.001 , 
            selection_algorithm = "tournament" ,num_elites = 0, verbose = False): 
    
    gens_needed = 0
    flag = False
    
    isRoulette = False
    if selection_algorithm == "roulette" : 
        isRoulette = True
    #initialize population
    population = np.array([np.random.randint(0 , 2 , n_bits) for _ in range(population_size)])
    best_solution , best_fitness = 0 , objective_function(population[0])
    
    for gen in range(max_generations) : 
        #calculate fitness
        fitness = np.array([objective_function(individual) for individual in population]).astype(np.float32)

        for i in range(population_size) : 
            if fitness[i] < best_fitness : 
                best_solution , best_fitness = population[i] , fitness[i]
        #get parents
        if isRoulette :
            parents = roulette_wheel_selection(population , population_size , fitness)
        else :  
            parents = tournament_selection(population , population_size , fitness, num_elites, k = 20)
        #get children by performing crossover
        children = crossover(population_size , parents , p_crossover , n_bits)
        #mutate
        bitstring_mutation(children , mutation_rate)
        #update popoluation
        population = children
        # if the best fitness is found then break
        if best_fitness == 0 : 
            gens_needed = gen
            flag = True
        if verbose : 
            if gen % 50 == 0 : 
                print(f"Generation : {gen} , Best Fitness : {best_fitness}")
        if flag : 
            break

    return best_solution , best_fitness , gens_needed


