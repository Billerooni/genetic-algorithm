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
// Chance of a gene mutating when it is passed on
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

	/*	Parent 1 Index, Parent 1 Generation
		Parent 2 Index, Parent 2 Generation */
	int parents[4] = { -1, -1, -1, -1 };

public:
	// Initialise the creature with a seed (used for first generation only)
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

	// Parents
	void set_parents (int p[4]) {
		for (unsigned i = 0; i<4; i++)
			parents[i] = p[i];
	}
	std::string get_parents () {
		if (parents[0] < 0)
			return "N/A";
		return std::to_string(parents[0]) + "G" +
			std::to_string(parents[1]) + "," +
			std::to_string(parents[2]) + "G" +
			std::to_string(parents[3]);
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
		// TODO

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
		if (!(gen % 10) || gen == GENERATIONS-1) {
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
		}
	}

	return 0;
}
