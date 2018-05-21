/*	A simple genetic algorithm to solve linear equations in the form
	ax + b = c. */

#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <vector>
#include <string>

// Amount of equations for the creatures to be tested on
const int TESTS = 1;
// Amount of nodes the creatures uses for calculation
const int NODE_AMOUNT = 3;
// Amount of creatures in the population
const int CREATURES = 100;
// Amount of generations for the simulation to run for
const int GENERATIONS = 100;
// The rate at which to print generations
const int STEP = 10;
// Chance of a gene mutating when it is passed on
const double MUTATION_RATE = 0.05;

// Creature
#include "creature.h"

// Main function
int main () {
	srand(time(NULL));

	// Add random tests
	std::vector<std::vector<double>> tests;
	printf("TESTS\n");
	for (unsigned i = 0; i < TESTS; i++) {
		// Uses random floats from -100 to 100 as the a, b, c values
		std::vector<double> tmp_test = {
			(2*rand()/(RAND_MAX + 1.0))*100,
			(2*rand()/(RAND_MAX + 1.0))*100,
			(2*rand()/(RAND_MAX + 1.0))*100
		};
		tests.push_back(tmp_test);

		printf("%fx + %f = %f\n", tmp_test[0], tmp_test[1], tmp_test[2]);
	}
	printf("\n");

	// Initialise the population
	std::vector<Creature> population = {};
	population.resize(CREATURES);

	std::vector<double> fitnesses = {};
	fitnesses.resize(CREATURES);

	// Loop through each generation
	for (unsigned gen = 0; gen < GENERATIONS; gen++) {
		// Loop through each creature
		for (unsigned cr = 0; cr < CREATURES; cr++) {
			// Seed the first population
			if (gen == 0)
				population[cr].seed();

			// Set the fitness to the mean fitness of each test
			fitnesses[cr] = population[cr].get_avg_fitness(tests);
		}

		// Get the highest and mean fitness of the generation
		double sumFitness = 0;
		double hFit = 0;

		for (unsigned cr = 0; cr < CREATURES; cr++) {
			// Get the current highest fitness
			if (fitnesses[cr] > fitnesses[hFit])
				hFit = cr;

			// Add to the fitness sum, used to work out the mean
			sumFitness += fitnesses[cr];
		}

		// Print information
		if (!(gen % STEP) || gen == GENERATIONS-1) {
			printf("GENERATION %u\n", gen);
			printf("Mean fitness: %f\n", sumFitness/fitnesses.size());
			printf("Highest fitness: %f (Parents: %s)\n\n",
				fitnesses[hFit], population[hFit].get_parents().c_str());
		}

		// Breed and create the next generation
		for (unsigned j = 0; j < CREATURES; j++) {
			/*	Loop through each creature to see which pair will
				breed the current new creature. Fitter creatures have
				a higher chance of breeding. */

			// First parent
			unsigned p1;
			double sumFit = 0;
			double pSeed = rand()/(RAND_MAX + 1.0);

			for (unsigned cr = 0; cr < CREATURES; cr++) {
				/*	Gets a random creature to breed with, weighted by
					its fitness. */
				if (pSeed * sumFitness - sumFit < fitnesses[cr]) {
					p1 = cr;
					break;
				}
				sumFit += fitnesses[cr];
			}

			// Second parent
			unsigned p2;
			do {
				sumFit = 0;
				pSeed = rand()/(RAND_MAX + 1.0);

				for (unsigned cr = 0; cr < CREATURES; cr++) {
					/*	Gets a random creature to breed with, weighted
						by its fitness. This cannot be the same as the
						first parent. */
					if (pSeed * sumFitness - sumFit < fitnesses[cr]) {
						p2 = cr;
						break;
					}
					sumFit += fitnesses[cr];
				}
			} while	(p1 == p2);

			// TODO: Breeding
			population[p1].breed(gen, p1, p2, population[p2]);
		}
	}

	return 0;
}
