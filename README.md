## 🧬 Overview

This repository provides an **optimized implementation of the Genetic Algorithm (GA)** for both **discrete** and **continuous** function optimization.  

In addition, it includes an implementation of the **Grey Wolf Optimizer (GWO)**, a nature-inspired metaheuristic that often achieves **better and more stable results** with **fewer generations** compared to the basic GA.  

Both algorithms are flexible, easy to adapt, and can be applied to a wide range of optimization problems.

## 🧬 What is a Genetic Algorithm?

A **Genetic Algorithm (GA)** is an optimization method inspired by the process of natural selection and evolution.  
Instead of directly searching for the best solution, a GA **evolves a population of candidate solutions** over multiple generations, combining exploration (searching new areas) and exploitation (refining good solutions).  

---

## ⚙️ Basic Functionality

1. **Initialization**  
   A population of candidate solutions (often represented as vectors, strings, or chromosomes) is generated randomly or heuristically.  

2. **Evaluation (Fitness Function)**  
   Each candidate solution is evaluated using a *fitness function*, which measures how well it solves the optimization problem.  

3. **Selection**  
   Fitter solutions are more likely to be chosen as parents.  
   Common methods include *roulette wheel selection*, *tournament selection*, and *rank-based selection*.  

4. **Crossover (Recombination)**  
   Two parent solutions are combined to produce offspring.  
   The idea is to mix good traits from different parents to form potentially better solutions.  

5. **Mutation**  
   Small random changes are applied to some individuals to maintain diversity and avoid premature convergence.  

6. **Replacement**  
   The new offspring replace some or all of the old population, creating a new generation.  

7. **Termination**  
   The algorithm repeats steps 2–6 until a stopping condition is met  
   (e.g., maximum generations, convergence, or reaching a target fitness).  

---

## 🔑 Key Features

- Works for both **discrete** (combinatorial) and **continuous** optimization problems  
- Does not require gradients or other problem-specific knowledge  
- Balances *exploration* (searching broadly) and *exploitation* (refining good solutions)  
- Stochastic in nature – results may vary across runs  
