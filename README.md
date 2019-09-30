# genetic-algorithm
A C++ genetic algorithm I made for fun that learns to work out simple linear equations. If you want to modify anything, feel free to.

## Constants

### TESTS
The amount of equations that each creature has to attempt. Increasing this constant will make it take more generations for the creatures to reach a higher fitness since they have to gain a set of genes that works across the board.

### NODE_AMOUNT
The amount of nodes in the single hidden layer.

### CREATURES
The amount of creatures created for each generation.

### GENERATIONS
The amount of generations the algorithm runs through before it reaches its final answer.

### STEP
The rate at which generational results are printed. For example, at the default rate of 1000: Generation 0, then Generation 1000, then Generation 2000, etc. will be printed.

### MUTATION_RATE
The chance that a gene (node or node weight) will change into a completely new one. The default 0.05 means a 5% chance for each gene.
