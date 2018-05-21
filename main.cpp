/*	A simple genetic algorithm to solve linear equations in the form
	ax + b = c.
*/

#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <vector>

// Constants
const int NODE_AMOUNT = 3;
const int CREATURES = 100;
const int GENERATIONS = 100;
const double MUTATION_RATE = 0.05;

// Creature
class Creature {
	// Takes in the inputs of a, b, c
	double input[3];
	// Weights (genes)
	double node_weights[NODE_AMOUNT*3];
	double output_weights[NODE_AMOUNT];
	// Hidden nodes
	double nodes[NODE_AMOUNT];
	// Outputs x
	double output = 0;

public:
	void seed () {
		for (unsigned i = 0; i < sizeof(node_weights)/sizeof(double); i++)
			node_weights[i] = 2*rand()/(RAND_MAX + 1.0);
		for (unsigned i = 0; i < sizeof(output_weights)/sizeof(double); i++)
			output_weights[i] = 2*rand()/(RAND_MAX + 1.0);
	}

	// Input values
	void set_input (double a, double b, double c) {
		input[0] = a;
		input[1] = b;
		input[2] = c;
	}

	// Get the output from the genes and input
	double get_output () {
		// Each node is equal to the three weighted inputs summed
		for (unsigned i = 0; i < sizeof(nodes)/sizeof(double); i++) {
			nodes[i] =
				input[0] * node_weights[i] +
				input[1] * node_weights[NODE_AMOUNT+i] +
				input[2] * node_weights[NODE_AMOUNT*2+i];
		}

		output = 0;
		// The output is equal to the weighted nodes summed
		for (unsigned i = 0; i < sizeof(nodes)/sizeof(double); i++)
			output += nodes[i] * output_weights[i];

		return output;
	}

	// Get fitness
	double get_fitness () {
		double x = get_output();
		double real_x = (input[2] - input[1]) / input[0];
		return (1 / std::abs(real_x - x));
	}

	// Get average fitness for several tests
	double get_avg_fitness (std::vector<std::vector<double>> t) {
		double total_fitness = 0;

		for (unsigned i = 0; i < t.size(); i++) {
			set_input(t[i][0], t[i][1], t[i][2]);
			total_fitness += get_fitness();
		}

		return total_fitness / t.size();
	}

	// Breed with another creature
	Creature breed (Creature c) {
		return Creature();
	}
};

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

	// Loop through each generation
	for (unsigned gen = 0; gen < GENERATIONS; gen++) {
		// Initialise the population
		std::vector<Creature> population = {};
		population.resize(CREATURES);

		std::vector<double> fitnesses = {};
		fitnesses.resize(CREATURES);

		// Loop through each creature
		for (unsigned j = 0; j < population.size(); j++) {
			// TODO: Seeds new creatures
			population[j].seed();

			// Set the fitness to the mean fitness of each test
			fitnesses[j] = population[j].get_avg_fitness(tests);
		}

		// Get the highest and mean fitness of the generation
		double sumFitness = 0;
		double highestFitness = 0;

		for (unsigned j = 0; j < fitnesses.size(); j++) {
			// Get the current highest fitness
			if (fitnesses[j] > highestFitness)
				highestFitness = fitnesses[j];

			// Add to the fitness sum, used to work out the mean
			sumFitness += fitnesses[j];
		}

		// Print information
		if (!(gen % 10) || gen == GENERATIONS-1) {
			printf("GENERATION %u\n", gen);
			printf("Mean fitness: %f\n", sumFitness/fitnesses.size());
			printf("Highest fitness: %f\n\n", highestFitness);
		}

		// TODO: Work out which creatures will be parents for the next generation

	}

	return 0;
}
