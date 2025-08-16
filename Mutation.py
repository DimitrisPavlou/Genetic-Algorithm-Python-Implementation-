import numpy as np


def continuous_mutation(children , population_size , num_variables, mutation_rate,generation, max_generations, num_elites = 0) : 
    initial_variance = 3  # Starting variance for Gaussian noise
    variance_decay = initial_variance * (1 - (generation / max_generations))  # Decay variance over generations
    variance_decay = max(variance_decay, 0.7) #if variance < 0.7 set it equal to 0.7, else leave it as is
    
    for i in range(num_elites, population_size):
        for j in range(num_variables):
            #if mutation happens
            if np.random.rand() < mutation_rate:
                #add gaussian noise to the variables
                children[i][j] += np.random.normal(loc = 0 , scale = np.sqrt(variance_decay))



def bitstring_mutation(population , mutation_rate) : 

    for bitstring in population : 
        for i in range(len(bitstring)) : 
            #if mutation happens
            if np.random.rand() < mutation_rate: 
                #flip bit
                bitstring[i] = 1 - bitstring[i]
