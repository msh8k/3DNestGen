//#include <chrono>

#include "stdafx.h"

int main() {
//    Xorshiro x;



//    uint64_t boundary = std::numeric_limits<uint64_t>::max ( ) / 7;
//    std::cout << "Longest possible uint64_t / 7: " << boundary << std::endl;
//    std::cout << "First random: " << x.next ( ) / boundary << std::endl << "Second random: " << x.next ( ) / boundary;
//    for (int j = 0; j < 20; ++j) {
//        auto start = std::chrono::high_resolution_clock::now();
//        for (int i = 0; i < 1000000; ++i) {
//            x.next();
//        };
//        auto finish = std::chrono::high_resolution_clock::now();
//
//        auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);
//        std::cout << microseconds.count() << " µs\n";
//        if (microseconds > std::chrono::seconds(1))
//            break;
//    }
	Mongo mongo;

//// Random Testing
//	const int SIZE = 1000000000;
//
//	std::vector<int> percentages{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
//	uint64_t random;
//	uint64_t ten_percent = UINT64_MAX / 10;
//	uint64_t twenty_percent = (UINT64_MAX / 10) * 2;
//	uint64_t thirty_percent = (UINT64_MAX / 10) * 3;
//	uint64_t fourty_percent = (UINT64_MAX / 10) * 4;
//	uint64_t fifty_percent = (UINT64_MAX / 10) * 5;
//	uint64_t sixty_percent = (UINT64_MAX / 10) * 6;
//	uint64_t seventy_percent = (UINT64_MAX / 10) * 7;
//	uint64_t eighty_percent = (UINT64_MAX / 10) * 8;
//	uint64_t ninety_percent = (UINT64_MAX / 10) * 9;
//
//	std::cout << UINT64_MAX << std::endl;
//	std::cout << ten_percent << std::endl;
//	std::cout << twenty_percent << std::endl;
//
//
//	
//	for (int j = 0; j < 100; ++j) {
//		Xorshiro x;
//
//		for (auto &p : percentages) {
//			p = 0;
//		}
//
//		for (int i = 0; i < SIZE; ++i) {
//			random = x.next();
//
//			if (random < ten_percent)
//				++percentages[0];
//			else if (random < twenty_percent)
//				++percentages[1];
//			else if (random < thirty_percent)
//				++percentages[2];
//			else if (random < fourty_percent)
//				++percentages[3];
//			else if (random < fifty_percent)
//				++percentages[4];
//			else if (random < sixty_percent)
//				++percentages[5];
//			else if (random < seventy_percent)
//				++percentages[6];
//			else if (random < eighty_percent)
//				++percentages[7];
//			else if (random < ninety_percent)
//				++percentages[8];
//			else
//				++percentages[9];
//		}
//
//		mongo.insert_random_test(percentages, j + 1);
//	}

	// Nest Generation
	std::vector<int> loads{ };
	int START_I = 0;
	int END_I = 100;
	int START_J = 2;
	int roll, i, j;

	for (int z = 10; z < 500; z += 10)	{
		loads.emplace_back(z);
	}

	for (int z = 500; z <= 5000; z += 100) {
		loads.emplace_back(z);
	}
	
	for (auto &load : loads) {
	// Random rule
		for (i = START_I; i < END_I; ++i) {
			// re-seed random generator after each nest
			Xorshiro x;

			// threshold for maxed-out cell height: 1 coordinate unit = 5.0 mm
			double max_height = 6.0;
			
			// calculate second load initiation site
			int build_index = x.next() % 6;

			Nest nest(max_height, build_index);
						
			bool result = false;

			nest.calculate_measurements();

			// start counter at step 2: steps 0 and 1 taken automatically
			for (j = START_J; j < load; ++j) {
				roll = x.next();
				build_index = Rules::random_step(nest, roll);

				if (nest.cell_initiated(build_index)) {
					nest.lengthen(build_index);
				}
				else {
					nest.initiate_cell(build_index, j, max_height);
				}
			}

			nest.calculate_measurements();
			mongo.insert_one(nest, i + 1, "random_const", std::to_string(load).c_str());
		}

		// Age rule
		for (i = START_I; i < END_I; ++i) {
		 // re-seed random generator after each nest
		  Xorshiro x;

			// threshold for maxed-out cell height: 1 coordinate unit = 5.0 mm
			double max_height = 6.0;

			// calculate second load initiation site
			int build_index = x.next() % 6;

			Nest nest(max_height, build_index);

			bool result = false;

			nest.calculate_measurements();

			// start counter at step 1: step 0 taken automatically at (0, 0, 0)
			for (j = START_J; j < load; ++j) {
				roll = x.next();
				build_index = Rules::max_age_step(nest, roll, j);

				if (nest.cell_initiated(build_index)) {
					nest.lengthen(build_index);
				}
				else {
					nest.initiate_cell(build_index, j, max_height);
				}
			}

			nest.calculate_measurements();
			mongo.insert_one(nest, i + 1, "maximum_age_const", std::to_string(load).c_str());
		}

		// Max Height rule
		for (i = START_I; i < END_I; ++i) {
			// re-seed random generator after each nest
			Xorshiro x;

			// threshold for maxed-out cell height: 1 coordinate unit = 5.0 mm
			double max_height = 6.0;

			// calculate second load initiation site
			int build_index = x.next() % 6;

			Nest nest(max_height, build_index);

			bool result = false;

			nest.calculate_measurements();

			// start counter at step 1: step 0 taken automatically at (0, 0, 0)
			for (j = START_J; j < load; ++j) {
				roll = x.next();
				build_index = Rules::max_height_step(nest, roll);

				if (nest.cell_initiated(build_index)) {
					nest.lengthen(build_index);
				}
				else {
					nest.initiate_cell(build_index, j, max_height);
				}
			}

			nest.calculate_measurements();
			mongo.insert_one(nest, i + 1, "maximum_height_const", std::to_string(load).c_str());
		}

		// Height Difference rule
		for (i = START_I; i < END_I; ++i) {
			// re-seed random generator after each nest
			Xorshiro x;

			// threshold for maxed-out cell height: 1 coordinate unit = 5.0 mm
			double max_height = 6.0;

			// calculate second load initiation site
			int build_index = x.next() % 6;

			Nest nest(max_height, build_index);

			bool result = false;

			nest.calculate_measurements();

			// start counter at step 1: step 0 taken automatically at (0, 0, 0)
			for (j = START_J; j < load; ++j) {
				roll = x.next();
				build_index = Rules::height_difference_step(nest, roll);

				if (nest.cell_initiated(build_index)) {
					nest.lengthen(build_index);
				}
				else {
					nest.initiate_cell(build_index, j, max_height);
				}
			}

			nest.calculate_measurements();
			mongo.insert_one(nest, i + 1, "height_difference_const", std::to_string(load).c_str());
		}

		// Hybrid Height rule
		for (i = START_I; i < END_I; ++i) {
			// re-seed random generator after each nest
			Xorshiro x;

			// threshold for maxed-out cell height: 1 coordinate unit = 5.0 mm
			double max_height = 6.0;

			// calculate second load initiation site
			int build_index = x.next() % 6;

			Nest nest(max_height, build_index);

			bool result = false;

			nest.calculate_measurements();

			// start counter at step 1: step 0 taken automatically at (0, 0, 0)
			for (j = START_J; j < load; ++j) {
				roll = x.next();
				build_index = Rules::hybrid_height_step(nest, roll);

				if (nest.cell_initiated(build_index)) {
					nest.lengthen(build_index);
				}
				else {
					nest.initiate_cell(build_index, j, max_height);
				}
			}

			nest.calculate_measurements();
			mongo.insert_one(nest, i + 1, "hybrid_height_const", std::to_string(load).c_str());
		}

		// Hybrid Age rule
		for (i = START_I; i < END_I; ++i) {
			// re-seed random generator after each nest
			Xorshiro x;

			// threshold for maxed-out cell height: 1 coordinate unit = 5.0 mm
			double max_height = 6.0;

			// calculate second load initiation site
			int build_index = x.next() % 6;

			Nest nest(max_height, build_index);

			bool result = false;

			nest.calculate_measurements();

			// start counter at step 1: step 0 taken automatically at (0, 0, 0)
			for (j = START_J; j < load; ++j) {
				roll = x.next();
				build_index = Rules::hybrid_age_step(nest, roll, j);

				if (nest.cell_initiated(build_index)) {
					nest.lengthen(build_index);
				}
				else {
					nest.initiate_cell(build_index, j, max_height);
				}
			}

			nest.calculate_measurements();
			mongo.insert_one(nest, i + 1, "hybrid_age_const", std::to_string(load).c_str());
		}

		// Max Wall rule
		for (i = START_I; i < END_I; ++i) {
			// re-seed random generator after each nest
			Xorshiro x;

			// threshold for maxed-out cell height: 1 coordinate unit = 5.0 mm
			double max_height = 6.0;

			// calculate second load initiation site
			int build_index = x.next() % 6;

			Nest nest(max_height, build_index);

			bool result = false;

			nest.calculate_measurements();

			// start counter at step 1: step 0 taken automatically at (0, 0, 0)
			for (j = START_J; j < load; ++j) {
				roll = x.next();
				build_index = Rules::max_wall_step(nest, roll);

				if (nest.cell_initiated(build_index)) {
					nest.lengthen(build_index);
				}
				else {
					nest.initiate_cell(build_index, j, max_height);
				}
			}

			nest.calculate_measurements();
			mongo.insert_one(nest, i + 1, "max_wall_const", std::to_string(load).c_str());
		}

		// Hybrid Wall rule
		for (i = START_I; i < END_I; ++i) {
			// re-seed random generator after each nest
			Xorshiro x;

			// threshold for maxed-out cell height: 1 coordinate unit = 5.0 mm
			double max_height = 6.0;

			// calculate second load initiation site
			int build_index = x.next() % 6;

			Nest nest(max_height, build_index);

			bool result = false;

			nest.calculate_measurements();

			// start counter at step 1: step 0 taken automatically at (0, 0, 0)
			for (j = START_J; j < load; ++j) {
				roll = x.next();
				build_index = Rules::hybrid_wall_step(nest, roll);

				if (nest.cell_initiated(build_index)) {
					nest.lengthen(build_index);
				}
				else {
					nest.initiate_cell(build_index, j, max_height);
				}
			}

			nest.calculate_measurements();
			mongo.insert_one(nest, i + 1, "hybrid_wall_const", std::to_string(load).c_str());
		}

		//// Hybrid Age Wall rule
		//for (i = START_I; i < END_I; ++i) {
		//	// re-seed random generator after each nest
		//	Xorshiro x;

		//	// threshold for maxed-out cell height: 1 coordinate unit = 5.0 mm
		//	double max_height = 6.0;

		//	// calculate second load initiation site
		//	int build_index = x.next() % 6;

		//	Nest nest(max_height, build_index);

		//	bool result = false;

		//	nest.calculate_measurements();

		//	// start counter at step 1: step 0 taken automatically at (0, 0, 0)
		//	for (j = START_J; j < load; ++j) {
		//		roll = x.next();
		//		build_index = Rules::hybrid_age_wall_step(nest, roll, j);

		//		if (nest.cell_initiated(build_index)) {
		//			nest.lengthen(build_index);
		//		}
		//		else {
		//			nest.initiate_cell(build_index, j, max_height);
		//		}
		//	}

		//	nest.calculate_measurements();
		//	mongo.insert_one(nest, i + 1, "hybrid_age_wall_const", std::to_string(load).c_str());
		//}
	}

	return 0;
}
