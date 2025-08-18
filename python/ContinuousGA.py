import numpy as np
from Selection import tournament_selection , roulette_wheel_selection
from Crossover import crossover
from Mutation import continuous_mutation


def continuous_ga(objective_function, init_point, population_size=100, max_generations=100, p_crossover = 0.7, mutation_rate=0.001,
                  selection_algorithm = "tournament", num_elites = 0, print_every = 100):
    
    #the length of the initial point gives the number of dimensions
    num_variables = len(init_point)
    isRoulette = False
    if selection_algorithm == "roulette" : 
        isRoulette = True

    #initiliaze population at the init point
    population = init_point*np.ones((population_size , num_variables))

    convergence_curve = np.zeros(max_generations)
    for generation in range(max_generations):
        # Evaluate fitness of each individual in the population
        fitness = np.array([objective_function(individual) for individual in population])
        
        #get parents by selection
        if isRoulette :
            parents = roulette_wheel_selection(population , population_size , fitness)
        else :  
            parents = tournament_selection(population, population_size , fitness, num_elites, k = 30)
        
        #get children by crossover
        children = crossover(population_size , parents , p_crossover , num_variables)
        
        #mutation
        continuous_mutation(children , population_size , num_variables , mutation_rate, generation, max_generations, num_elites)
        
        # Replace population with offspring
        population = children
        #find best solution of the generation
        best_index = np.argmin(fitness)
        best_solution = population[best_index]
        best_fitness = objective_function(best_solution)

        convergence_curve[generation] = best_fitness
        if generation % print_every == 0 : 
            print(f"Generation : {generation} , Best solution : {best_solution} , Best Fitness : {best_fitness}")
        
    return best_solution, best_fitness , convergence_curve
