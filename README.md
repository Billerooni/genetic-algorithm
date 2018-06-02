# genetic-algorithm
A C++ genetic algorithm I made for fun that learns to work out simple linear equations. If you want to modify anything, feel free to but just read the license first. There are a lot of possibilities like changing the type of equation, amount of node layers, the natural selection process: like I said feel free to play around with the code.

## Customisation
There are various constants that you can customise inside of the main file:

### TESTS
The amount of equations that each creature has to attempt. Increasing this constant will make it take more generations for the creatures to reach a higher fitness since they have to gain a set of genes that works across the board.

### NODE_AMOUNT
The amount of "nodes" that the creatures uses to calculate the answer (akin to neurons).

### CREATURES
The amount of creatures created for each generation.

### GENERATIONS
The amount of generations the algorithm runs through before it reaches its final answer.

### STEP
The rate at which generational results are printed. For example, at the default rate of 1000: Generation 0, then Generation 1000, then Generation 2000, etc. will be printed.

### MUTATION_RATE
The chance that a gene (node or node weight) will change into a completely new one. The default 0.05 means a 5% chance for each gene.
