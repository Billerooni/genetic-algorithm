/*	A simple genetic algorithm to solve linear equations in the form
	ax + b = c.
*/

#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <vector>

const int NODE_AMOUNT = 3;
const int CREATURES = 50;
const int TESTS = 3;


// Creature
class Creature {
	// Takes in the inputs of a, b, c
	float input[3];
	// Weights (genes)
	float node_weights[NODE_AMOUNT*3];
	float output_weights[NODE_AMOUNT];
	// Hidden nodes
	float nodes[NODE_AMOUNT];
	// Outputs x
	float output = 0;

public:
	void seed () {
		for (unsigned i = 0; i < sizeof(node_weights)/sizeof(float); i++)
			node_weights[i] = 2*rand()/(RAND_MAX + 1.0);
		for (unsigned i = 0; i < sizeof(output_weights)/sizeof(float); i++)
			output_weights[i] = 2*rand()/(RAND_MAX + 1.0);
	}

	// Input values
	void set_input (float a, float b, float c) {
		input[0] = a;
		input[1] = b;
		input[2] = c;
	}

	// Get the output from the genes and input
	float get_output () {
		// Each node is equal to the three weighted inputs summed
		for (unsigned i = 0; i < sizeof(nodes)/sizeof(float); i++) {
			nodes[i] =
				input[0] * node_weights[i] +
				input[1] * node_weights[NODE_AMOUNT+i] +
				input[2] * node_weights[NODE_AMOUNT*2+i];
		}

		output = 0;
		// The output is equal to the weighted nodes summed
		for (unsigned i = 0; i < sizeof(nodes)/sizeof(float); i++)
			output += nodes[i] * output_weights[i];

		return output;
	}

	// Get fitness
	float get_fitness () {
		float x = get_output();
		float real_x = (input[2] - input[1]) / input[0];
		return 1 / std::abs(real_x - x);
	}

	// Get average fitness for several tests
	float get_avg_fitness (std::vector<std::vector<float>> t) {
		float total_fitness = 0;

		for (unsigned i = 0; i < t.size(); i++) {
			set_input(t[i][0], t[i][1], t[i][2]);
			total_fitness += get_fitness();
		}

		return total_fitness / t.size();
	}
};

// Main function
int main () {
	srand(time(NULL));

	// Add random tests
	std::vector<std::vector<float>> tests;
	for (unsigned i = 0; i < TESTS ; i++) {
		std::vector<float> tmp_test = {};
		tmp_test.push_back(rand() % 1000);
		tmp_test.push_back(rand() % 1000);
		tmp_test.push_back(rand() % 1000);
		tests.push_back(tmp_test);
	}

	// Initialise the population
	std::vector<Creature> population;
	population.resize(CREATURES);

	// Loop through each population and test their fitness
	for (unsigned i = 0; i < population.size(); i++) {
		population[i].seed();
		printf("%f\n", population[i].get_avg_fitness(tests));
	}

	return 0;
}
