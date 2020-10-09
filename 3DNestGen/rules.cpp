#include "stdafx.h"


int Rules::random_step(Nest nest, uint64_t random) {
	std::vector<Cell> cells = nest.get_eligible_sites();
	int index = random % cells.size();
	return cells[index].get_index();
}

int Rules::max_age_step(Nest nest, uint64_t random, int current_step)
{
 	std::vector<Cell> cells = nest.get_eligible_sites();
	std::vector<int> probabilities{ };

	int probability_sum = 0;
	int probability, work;
	
	for (auto &cell: cells) {
		work = cell.sum_wall_ages(current_step);
		probabilities.emplace_back(work);
		probability_sum += work;
	}

	probability = (int)(random % (probability_sum));
	work = -1;

	while (probability > -1) {
		probability -= probabilities[++work];		
	}

	return cells[work].get_index();
}

int Rules::max_height_step(Nest nest, uint64_t random)
{
	std::vector<Cell> cells = nest.get_eligible_sites();
	std::vector<long> probabilities{ };

	long probability_sum = 0;
	long probability, work;

	for (auto &cell : cells) {
		work = cell.sum_wall_heights();
		probabilities.emplace_back(work);
		probability_sum += work;
	}

	probability = (long)(random % (probability_sum));
	work = -1;

	while (probability > -1) {
		probability -= probabilities[++work];
	}

	return cells[work].get_index();
}

int Rules::max_wall_step(Nest nest, uint64_t random)
{
	std::vector<Cell> cells = nest.get_eligible_sites();
	std::vector<int> probabilities{ };

	int probability_sum = 0;
	int probability, work;

	for (auto &cell : cells) {
		work = cell.sum_existing_walls();
		probabilities.emplace_back(work);
		probability_sum += work;
	}

	probability = (int)(random % (probability_sum));
	work = -1;

	while (probability > -1) {
		probability -= probabilities[++work];
	}

	return cells[work].get_index();
}

int Rules::height_difference_step(Nest nest, uint64_t random)
{
	std::vector<Cell> cells = nest.get_eligible_sites();
	std::vector<int> probabilities{ };

	int probability_sum = 0;
	int probability, work;

	for (auto &cell : cells) {
		work = cell.get_max_height() - cell.get_min_height();
		if (work < 1) {
			work = 1;
		}
		probabilities.emplace_back(work);
		probability_sum += work;
	}

	probability = (int)(random % (probability_sum));
	work = -1;

	while (probability > -1) {
		probability -= probabilities[++work];
	}

	return cells[work].get_index();
}

int Rules::hybrid_height_step(Nest nest, uint64_t random)
{
	std::vector<Cell> cells = nest.get_eligible_sites();
	std::vector<long> probabilities{ };

	long probability_sum = 0;
	long probability, work;

	for (auto &cell : cells) {
		work = cell.sum_wall_heights() + cell.get_max_height() - cell.get_min_height();
		if (work < 1) {
			work = 1;
		}
		probabilities.emplace_back(work);
		probability_sum += work;
	}

	probability = (long)(random % (probability_sum));
	work = -1;

	while (probability > -1) {
		probability -= probabilities[++work];
	}

	return cells[work].get_index();
}

int Rules::hybrid_age_step(Nest nest, uint64_t random, int current_step)
{
	std::vector<Cell> cells = nest.get_eligible_sites();
	std::vector<int> probabilities{ };

	int probability_sum = 0;
	int probability, work;

	for (auto &cell : cells) {
		work = cell.sum_wall_ages(current_step) + cell.get_max_height() - cell.get_min_height();
		if (work < 1) {
			work = 1;
		}
		probabilities.emplace_back(work);
		probability_sum += work;
	}

	probability = (int)(random % (probability_sum));
	work = -1;

	while (probability > -1) {
		probability -= probabilities[++work];
	}

	return cells[work].get_index();
}

int Rules::hybrid_wall_step(Nest nest, uint64_t random)
{
	std::vector<Cell> cells = nest.get_eligible_sites();
	std::vector<int> probabilities{ };

	int probability_sum = 0;
	int probability, work;

	for (auto &cell : cells) {
		work = cell.sum_existing_walls() + cell.get_max_height() - cell.get_min_height();
		if (work < 1) {
			work = 1;
		}
		probabilities.emplace_back(work);
		probability_sum += work;
	}

	probability = (int)(random % (probability_sum));
	work = -1;

	while (probability > -1) {
		probability -= probabilities[++work];
	}

	return cells[work].get_index();
}

int Rules::hybrid_age_wall_step(Nest nest, uint64_t random, int current_step)
{
	std::vector<Cell> cells = nest.get_eligible_sites();
	std::vector<int> probabilities{ };

	int probability_sum = 0;
	int probability, work;

	for (auto &cell : cells) {
		work = cell.sum_wall_ages(current_step) + cell.sum_existing_walls() + cell.get_max_height() - cell.get_min_height();
		if (work < 1) {
			work = 1;
		}
		probabilities.emplace_back(work);
		probability_sum += work;
	}

	probability = (int)(random % (probability_sum));
	work = -1;

	while (probability > -1) {
		probability -= probabilities[++work];
	}

	return cells[work].get_index();
}