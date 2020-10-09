#ifndef RULES_H
#define RULES_H

namespace Rules {
	int random_step(Nest nest, uint64_t random);
	int max_age_step(Nest nest, uint64_t random, int current_step);
	int max_height_step(Nest nest, uint64_t random);
	int max_wall_step(Nest nest, uint64_t random);
	int height_difference_step(Nest nest, uint64_t random);
	int hybrid_height_step(Nest nest, uint64_t random);
	int hybrid_age_step(Nest nest, uint64_t random, int current_step);
	int hybrid_wall_step(Nest nest, uint64_t random);
	int hybrid_age_wall_step(Nest nest, uint64_t random, int current_step);
}

#endif // !RULES_H
