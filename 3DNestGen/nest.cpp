#include "stdafx.h"

// Private methods
void Nest::add_initiation_sites(int cell, double threshold) {
    std::vector<int> home_coordinates{ _cells[cell].getx(), _cells[cell].gety(), _cells[cell].getz() };
	std::vector<int> adjusted, work;
	int neighbors = 0, neighbor, adjacent, work_index, work_adjacent;

    for (int i = 0; i < 6; ++i) {
        adjusted = Adjustments::adjust_coordinates(home_coordinates[0], home_coordinates[1], home_coordinates[2], i);
		neighbor = find_cell(adjusted[0], adjusted[1], adjusted[2]);
		adjacent = Adjustments::opposite_position(i);

		if (neighbor == -1) {
			std::vector<std::shared_ptr<Wall>> walls{ };
			for (int j = 0; j < 6; ++j)	{
				work = Adjustments::adjust_coordinates(adjusted[0], adjusted[1], adjusted[2], j);
				work_index = find_cell(work[0], work[1], work[2]);
				
				if (work_index == -1) {
					walls.emplace_back(nullptr);
				}
				else {
					work_adjacent = Adjustments::opposite_position(j);

					if (!_cells[work_index].wall_exists(work_adjacent)) {
						walls.emplace_back(nullptr);
					}
					else {
						walls.emplace_back(std::make_shared<Wall>(*_cells[work_index].get_wall_pointer(work_adjacent)));
					}
				}
			}
			add_cell(Cell{ walls, (int)_cells.size(), adjusted[0], adjusted[1], adjusted[2], -1, 0, threshold });
			_buildable_sites.emplace_back((int)_cells.size() - 1);
		}
		else if (!_cells[neighbor].wall_exists(adjacent)) {
			_cells[neighbor].add_wall(*_cells[cell].get_wall_pointer(i), adjacent);
		}
		else { // know self exists AND neighbor exists - new neighbor, increment count of old neighbor
			_cells[neighbor].add_neighbors(1);
		}
    }
}

void Nest::add_cell(Cell cell) {
    _cells.emplace_back(cell);
}


void Nest::add_wall(Wall wall) {
    _walls.emplace_back(wall);
}

std::pair<std::vector<long>, double> Nest::calculate_center_of_mass() {
    std::vector<long> center_of_mass{0, 0, 0};
	double sum_height = 0.0;

    for(auto &index: _nest) {
        center_of_mass[0] += _cells[index].getx();
        center_of_mass[1] += _cells[index].gety();
        center_of_mass[2] += _cells[index].getz();
		sum_height += _cells[index].get_average_height();
    }

	return { center_of_mass, (sum_height / (double)_nest.size()) };
}

void Nest::calculate_compactness() {
    std::pair<std::vector<long>, double> center_of_mass = calculate_center_of_mass();

    long x;
    long y;
    long z;


    auto nestSize = (long)_nest.size();
    double squaredNest = nestSize * nestSize;

	double height;

	double compactness_2D = 0.0;
	double compactness_3D = 0.0;

    for(auto &index: _nest) {
        x = (_cells[index].getx() * nestSize - center_of_mass.first[0]) * (_cells[index].getx() * nestSize - center_of_mass.first[0]);
        y = (_cells[index].gety() * nestSize - center_of_mass.first[1]) * (_cells[index].gety() * nestSize - center_of_mass.first[1]);
        z = (_cells[index].getz() * nestSize - center_of_mass.first[2]) * (_cells[index].getz() * nestSize - center_of_mass.first[2]);
		height = (_cells[index].get_average_height() - center_of_mass.second) * (_cells[index].get_average_height() - center_of_mass.second);

		// account for sqrt(2) difference between HCS and RCS compactness
		compactness_2D += std::sqrt(((x / squaredNest) + (y / squaredNest) + (z / squaredNest)) / 2.0);
        compactness_3D += std::sqrt((((x / squaredNest) + (y / squaredNest) + (z / squaredNest)) / 2.0) + height);
    }

    
	//_compactness_2D.emplace_back(compactness_2D);
	//_compactness_3D.emplace_back(compactness_3D);

	_compactness_2D = compactness_2D;
	_compactness_3D = compactness_3D;

    // Petiole always at (0, 0, 0) and 0 * nestSize = 0, so why bother
    x = (0 - center_of_mass.first[0]) * (0 - center_of_mass.first[0]);
    y = (0 - center_of_mass.first[1]) * (0 - center_of_mass.first[1]);
    z = (0 - center_of_mass.first[2]) * (0 - center_of_mass.first[2]);

	height = (_cells[0].get_average_height() - center_of_mass.second) * (_cells[0].get_average_height() - center_of_mass.second);

    //_eccentricity_2D.emplace_back(std::sqrt(((x / squaredNest) + (y / squaredNest) + (z / squaredNest)) / 2.0));
	//_eccentricity_3D.emplace_back(std::sqrt((((x / squaredNest) + (y / squaredNest) + (z / squaredNest)) / 2.0) + height));

	_eccentricity_2D = std::sqrt(((x / squaredNest) + (y / squaredNest) + (z / squaredNest)) / 2.0);
	_eccentricity_3D = std::sqrt((((x / squaredNest) + (y / squaredNest) + (z / squaredNest)) / 2.0) + height);
}

// Public methods
Nest::Nest(double max_height, int second_step) {
	_eligible_initiation_site_count = 0;
	_max_height = 0.0;
	
	// first initiation at (0, 0, 0)
	_buildable_sites.emplace_back(0);
	add_cell(Cell{ max_height });
    initiate_cell(0, 0, max_height);

	// second initiation at one of six neighbor sites (have to violate constraint in this case)
	std::vector<int> coordinates = Adjustments::adjust_coordinates(0, 0, 0, second_step);
	int second_index = find_cell(coordinates[0], coordinates[1], coordinates[2]);
	initiate_cell(second_index, 1, max_height);
}

void Nest::calculate_measurements() {
    calculate_compactness();
    calculate_outer_walls();
    //_total_walls.emplace_back((int)_walls.size());
	_total_walls = (int)_walls.size();
}

bool Nest::cell_initiated(int cell_index)
{
	if (_cells[cell_index].get_birth() == -1) { return false; }
	return true;
}

void Nest::calculate_outer_walls() {
    int outer_walls = 0;

    for (auto &index: _nest) {
        outer_walls += (6 - _cells[index].get_neighbors());
    }

    //_outer_walls.emplace_back(outer_walls);
	_outer_walls = outer_walls;
}

int Nest::find_cell(int x, int y, int z) {
    int counter = -1;

    for (Cell &c : _cells) {
        ++counter;

        if (x != c.getx()) { continue; }
        if (y != c.gety()) { continue; }
        if (z != c.getz()) { continue; }

        return counter;
    }

    return -1;
}

//std::vector<std::shared_ptr<Wall>> Nest::find_existing_walls(std::vector<int> site) {
//	std::vector<std::shared_ptr<Wall>> walls = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
//	int parent1_index = find_cell(site[0], site[1], site[2]), parent2_index;
//
//    for (int i = 0; i < 6; ++i) {
//        std::vector<int> parent2 = Adjustments::adjust_coordinates(site[0], site[1], site[2], i);
//		parent2_index = find_cell(parent2[0], parent2[1], parent2[2]);
//
//		if (parent1_index == -1 && parent2_index == -1) { continue; }
//		// if (parent1_index != -1 && _cells[parent1_index].get_birth() == -1) { continue; }
//		// if (parent2_index != -1 && _cells[parent2_index].get_birth() == -1) { continue; }
//
//        for (auto &wall : _walls) {
//            if (wall.find_parent(site[0], site[1], site[2], i)) {
//                walls[i] = std::make_shared<Wall> (wall);
//                break;
//            }
//        }
//    }
//
//	return walls;
//}

std::vector<Cell> Nest::get_all_buildable_sites()
{
	std::vector<Cell> buildable{ };
	for (int &cell: _buildable_sites) {
		buildable.push_back(_cells[cell]);
	}

	return buildable;
}

std::vector<Cell> Nest::get_eligible_sites()
{
	std::vector<int> neighbor;
	int initiation_count = 0, eligible_count, neighbor_index, i, x, y, z;
	_eligible_sites = { };
		
	for (auto &site : _buildable_sites) {
		eligible_count = 0;

		if (_cells[site].get_birth() == -1) {	// potential initiation sites
			for (i = 0; i < 6; ++i) {
				if (_cells[site].wall_exists(i)) {
					if (_cells[site].get_wall_pointer(i)->get_height() > 0) {
						++eligible_count;
						++initiation_count;
					}
				}
			}
		}

		else {									// initiated sites
			x = _cells[site].getx();
			y = _cells[site].gety();
			z = _cells[site].getz();

			for (i = 0; i < 6; ++i) {
				neighbor = Adjustments::adjust_coordinates(x, y, z, i);
				neighbor_index = find_cell(neighbor[0], neighbor[1], neighbor[2]);
				if (_cells[neighbor_index].get_min_height() >= _cells[site].get_min_height()) {
					++eligible_count;
				}
			}
		}
		if (eligible_count > 1) {
			_eligible_sites.emplace_back(_cells[site]);
		}
	}

	_eligible_initiation_site_count = initiation_count;
	return _eligible_sites;
}

std::vector<Cell> Nest::get_nest()
{
	std::vector<Cell> nest;
	for (int &cell : _nest) {
		nest.push_back(_cells[cell]);
	}

	return nest;
}

void Nest::initiate_cell(int cell_index, int step, double threshold) {
	bool wall_exists;
	int neighbors = 6;

    for (int i = 0; i < 6; ++i) {
        std::vector<int> parent2 = Adjustments::adjust_coordinates(_cells[cell_index].getx(), _cells[cell_index].gety(), 
																	_cells[cell_index].getz(), i);
		wall_exists = _cells[cell_index].wall_exists(i);
		        
        if (!wall_exists) {
            Wall w(Parent (_cells[cell_index].getx(), _cells[cell_index].gety(), _cells[cell_index].getz(), i),
                   Parent (parent2[0], parent2[1], parent2[2], Adjustments::opposite_position(i)), step);
            add_wall(w);
			neighbors--;
            _cells[cell_index].add_wall(w, i);
        }
    }

	_cells[cell_index].add_neighbors(neighbors);
	_cells[cell_index].set_birthday(step);
	_nest.emplace_back(cell_index);

	lengthen(cell_index, 60);

	add_initiation_sites(cell_index, threshold);	
}

void Nest::lengthen(int cell_index, int material) {
	_buildOrder.emplace_back((int)distance(_nest.begin(), std::find(_nest.begin(), _nest.end(), cell_index)));

    bool result = _cells[cell_index].build(material);
	_site_minimum_wall.emplace_back(_cells[cell_index].get_min_height_scaled());

	if (!result) {
		//std::cout << "Buildable before: ";
		//for (auto &site : _buildable_sites) {
		//	std::cout << site << " ";
		//}
		_buildable_sites.erase(std::remove(_buildable_sites.begin(), _buildable_sites.end(), cell_index), _buildable_sites.end());
		//++_mature_cells;
		//std::cout << "Buildable after: ";
		//for (auto &site : _buildable_sites) {
		//	std::cout << site << " ";
		//}
	}

	// divide by 40.0 to scale down
    double height = _cells[cell_index].get_max_height() / 40.0;

	if (_max_height < height) 
		_max_height = height;

    //_height.emplace_back(_max_height);   
}
