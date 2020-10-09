#ifndef NEST_H
#define NEST_H

class Nest {
private:
	std::vector<Cell> _cells{ };					// ALL cells (potential build sites with one wall, initiated cells, and mature cells)
	std::vector<Cell> _eligible_sites{ };			// used to determine nest build site via rules
	std::vector<Wall> _walls{ };					// ALL walls
	//std::vector<double> _compactness_2D{ };
	//std::vector<double> _compactness_3D{ };
	//std::vector<double> _eccentricity_2D{ };
	//std::vector<double> _eccentricity_3D{ };
	//std::vector<double> _height{ };
	std::vector<double> _site_minimum_wall{ };		// needed for nest visualization
	std::vector<int> _buildable_sites{ };			// used to track potentially eligible build sites
	std::vector<int> _nest{ };						// cells initiated in _cells
	//std::vector<int> _outer_walls{ };
	//std::vector<int> _total_walls{ };
	std::vector<int> _buildOrder{ };
	double _compactness_2D;
	double _compactness_3D;
	double _eccentricity_2D;
	double _eccentricity_3D;
	double _max_height;
	int _eligible_initiation_site_count;
	int _outer_walls;
	int _total_walls;

    void add_cell(Cell cell);
    void add_initiation_sites(int cell, double max_height);
    void add_wall(Wall wall);
    std::pair<std::vector<long>, double> calculate_center_of_mass();
    void calculate_compactness();
    void calculate_outer_walls();

public:
    Nest(double max_height, int second_step);
	std::vector<int> get_build_order() { return _buildOrder; }
	std::vector<int> get_nest_indices() { return _nest; }
	//std::vector<int> get_outer_walls() { return _outer_walls; }
	//std::vector<int> get_total_walls() { return _total_walls; }
	//std::vector<double> get_compactness_2D() { return _compactness_2D; }
	//std::vector<double> get_compactness_3D() { return _compactness_3D; }
	//std::vector<double> get_eccentricity_2D() { return _eccentricity_2D; }
	//std::vector<double> get_eccentricity_3D() { return _eccentricity_3D; }
	//std::vector<double> get_height() { return _height; }
	std::vector<double> get_site_minimum_wall() { return _site_minimum_wall; }

	int get_buildable_sites_count() { return _buildable_sites.size(); }
	int get_eligible_sites_count() { return _eligible_sites.size(); }
	int get_eligible_initiation_count() { return _eligible_initiation_site_count; }
	int get_outer_walls() { return _outer_walls; }
	int get_total_walls() { return _total_walls; }

	double get_compactness_2D() { return _compactness_2D; }
	double get_compactness_3D() { return _compactness_3D; }
	double get_eccentricity_2D() { return _eccentricity_2D; }
	double get_eccentricity_3D() { return _eccentricity_3D; }
	double get_max_height() { return _max_height; }


	std::vector<Cell> get_all_buildable_sites();
	std::vector<Cell> get_eligible_sites();
	std::vector<Cell> get_nest();

    void calculate_measurements();
	bool cell_initiated(int cell_index);
    int find_cell(int x, int y, int z);
	// std::vector<std::shared_ptr<Wall>> find_existing_walls(std::vector<int> site);
    void initiate_cell(int cell_index, int step, double max_height);
    void lengthen(int cell_index, int material = 60);
};

#endif //NEST_H
