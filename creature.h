class Creature {
public:
	// Weights (genes)
	double node_weights[NODE_AMOUNT*3];
	double output_weights[NODE_AMOUNT];

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
	void set_parents (int gen, int p1, int p2) {
		parents[0] = gen;
		parents[1] = p1;
		parents[2] = p2;
	}

	// Get parents as a string
	std::string get_parents () {
		if (parents[0] < 0)
			return "N/A";
		return "G" + std::to_string(parents[0]) + ":" +
			std::to_string(parents[1]) + "," + std::to_string(parents[2]);
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
		return atan(1/std::abs(real_x - x))*2/M_PI;
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
	Creature * breed (unsigned gen, unsigned p1, unsigned p2, Creature * c) {
		Creature * child;
		child->set_parents(gen, p1, p2);

		// Node weights
		double n_w[NODE_AMOUNT*3];
		for (unsigned i = 0; i < NODE_AMOUNT*3; i++) {
			// Randomly allocate genes from each parent
			n_w[i] = node_weights[i];
			if (rand()/(RAND_MAX + 1.0) < 0.5)
				n_w[i] = c->node_weights[i];

			// Mutate genes
			if (rand()/(RAND_MAX + 1.0) < MUTATION_RATE) {
				n_w[i] += 2*rand()/(RAND_MAX + 1.0);
				if (n_w[i] > 1 || n_w[i] < -1)
					n_w[i] = n_w[i] + ( n_w[i] > 1 ? -1 : 1 ) * floor(n_w[i]);
			}

			// Set the genes
			child->node_weights[i] = n_w[i];
		}

		// Output weights
		double o_w[NODE_AMOUNT];
		for (unsigned i = 0; i < NODE_AMOUNT; i++) {
			// Randomly allocate genes from each parent
			o_w[i] = output_weights[i];
			if (rand()/(RAND_MAX + 1.0) < 0.5)
				o_w[i] = c->output_weights[i];

			// Mutate genes
			if (rand()/(RAND_MAX + 1.0) < MUTATION_RATE) {
				o_w[i] += 2*rand()/(RAND_MAX + 1.0);
				if (o_w[i] > 1 || o_w[i] < -1)
					o_w[i] = o_w[i] + ( o_w[i] > 1 ? -1 : 1 ) * floor(o_w[i]);
			}

			// Set the genes
			child->output_weights[i] = o_w[i];
		}

		// Return this new creature
		return child;
	}
private:
	// Takes in the inputs of a, b, c
	double input[3];
	// Hidden nodes
	double nodes[NODE_AMOUNT];
	// Outputs x
	double output = 0;

	// Generation, Index 1, Index 2
	int parents[3] = { -1, -1, -1 };
};
