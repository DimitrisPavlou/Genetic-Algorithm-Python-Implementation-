import numpy as np


# elitism 
def elitism(population , fitness , num_elites) : 
    #keep the num_elites best of the population for the next generation
    sorted_indices = np.argsort(fitness)
    elite_indices = sorted_indices[:num_elites]
    elites = population[elite_indices]

    return elites


def tournament_selection(population, population_size, fitness, num_elites=0, k=10):
    
    parents = np.empty((population_size, population.shape[1]))
    #if elitism is applied 
    if num_elites > 0:
        elites = elitism(population, fitness, num_elites)
        parents[:num_elites] = elites
        num_parents = population_size - num_elites
    else:
        num_parents = population_size
 
    # Select the remaining parents using tournament selection
    for i in range(num_parents):
        #randomly choose k individuals
        tournament_indices = np.random.choice(population_size, size=k, replace=False)
        #find the best of the k individuals
        best_index = tournament_indices[np.argmin(fitness[tournament_indices])]
        #append to parents array
        parents[num_elites + i] = population[best_index]

    return parents

#roulette wheel selection
def roulette_wheel_selection(population , population_size , fitness, num_elites = 0) : 
    #transform fitness values for minimization problem
    fitness_new = 1 / (1 + fitness)
    #calculate probabilities
    probabilities = fitness_new/np.sum(fitness_new)
    
    parents = []
    #if elitism is applied
    if num_elites > 0 :
        elites = elitism(population , fitness , num_elites)
        parents.extend(elites)

    # Select the remaining parents using roulette wheel selection
    for i in range(0 , population_size-num_elites , 2) : 
        #sample from the popoulation based on the calculated probabilities
        parent_indices = np.random.choice(range(population_size) , size = 2 , replace = False , p = probabilities)
        #append to parents array
        parents.extend(population[parent_indices])
        
    return np.array(parents)
