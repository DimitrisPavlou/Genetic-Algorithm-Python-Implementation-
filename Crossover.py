import numpy as np


def crossover(population_size , parents , p_crossover , num_variables) : 
    #initialize children array
    children = np.zeros((population_size , num_variables))
    
    for i in range(0, population_size, 2):
        child1 = parents[i].copy()
        child2 = parents[i+1].copy()
        #if crossover happens
        if np.random.rand() < p_crossover:
            #randomly choose crossover point
            crossover_point = np.random.randint(0, num_variables)
            #perform crossover
            child1 = np.concatenate((parents[i][:crossover_point], parents[i+1][crossover_point:]))
            child2 = np.concatenate((parents[i+1][:crossover_point], parents[i][crossover_point:]))

        children[i] = child1 
        children[i+1] = child2
    
    return children
