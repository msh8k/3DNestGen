#include "stdafx.h"

void Mongo::insert_one(Nest nest, int nest_number, const char* db, const char* coll) {
	using bsoncxx::builder::stream::open_array;
	using bsoncxx::builder::stream::close_array;
	using bsoncxx::builder::stream::open_document;
	using bsoncxx::builder::stream::close_document;
	using bsoncxx::builder::stream::finalize;
	using bsoncxx::builder::core;

	bsoncxx::builder::stream::document document{ };

	document << "Nest ID" << nest_number << "Total Eligible Sites" << nest.get_eligible_sites_count() << "Eligible Initiation Sites" << nest.get_eligible_initiation_count();
	document << "Nest Height" << nest.get_max_height() << "Total Walls" << nest.get_total_walls() << "Outer Walls" << nest.get_outer_walls();
	document << "2D Compactness" << nest.get_compactness_2D() << "3D Compactness" << nest.get_compactness_3D();
	document << "2D Eccentricity" << nest.get_eccentricity_2D() << "3D Eccenctricity" << nest.get_eccentricity_3D();
	
	std::vector<Cell> cells = nest.get_nest();

	auto doc_cells = document << "Cells" << open_array;

	for (auto &cell : cells) {
		doc_cells = doc_cells << open_document << "X" <<  cell.getx() << "Y" << cell.gety() << "Z" << cell.getz() 
			<< "Cartesian X" << cell.get_cartesian_x() << "Cartesian Y" << cell.get_cartesian_y() << "Height" << cell.get_min_height_scaled() 
			<< "Birth" << cell.get_birth() << close_document;
	}
	doc_cells << close_array;

	std::vector<int> build_order = nest.get_build_order();

	auto doc_build_order = document << "Build order" << open_array;
	for (auto &location : build_order) {
		doc_build_order << location;
	}
	doc_build_order << close_array;

	std::vector<double> site_height = nest.get_site_minimum_wall();

	auto doc_site_height = document << "Build height" << open_array;
	for (auto &height : site_height) {
		doc_site_height << height;
	}
	doc_site_height << close_array;

	//std::vector<int> total_walls = nest.get_total_walls();

	//auto doc_total_walls = document << "Total walls" << open_array;
	//for (auto &total : total_walls) {
	//	doc_total_walls << total;
	//}
	//doc_total_walls << close_array;

	//std::vector<int> outer_walls = nest.get_outer_walls();

	//auto doc_outer_walls = document << "Outer walls" << open_array;
	//for (auto &outer : outer_walls) {
	//	doc_outer_walls << outer;
	//}
	//doc_outer_walls << close_array;

	//std::vector<double> compactness = nest.get_compactness_2D();

	//auto doc_compactness_2D = document << "2D Compactness" << open_array;
	//for (auto &c : compactness) {
	//	doc_compactness_2D << c;
	//}
	//doc_compactness_2D << close_array;

	//compactness = nest.get_compactness_3D();

	//auto doc_compactness_3D = document << "3D Compactness" << open_array;
	//for (auto &c : compactness) {
	//	doc_compactness_3D << c;
	//}
	//doc_compactness_3D << close_array;

	//std::vector<double> eccentricity = nest.get_eccentricity_2D();

	//auto doc_eccentricity_2D = document << "2D Eccentricity" << open_array;
	//for (auto &e : eccentricity) {
	//	doc_eccentricity_2D << e;
	//}
	//doc_eccentricity_2D << close_array;

	//eccentricity = nest.get_eccentricity_3D();

	//auto doc_eccentricity_3D = document << "3D Eccentricity" << open_array;
	//for (auto &e : eccentricity) {
	//	doc_eccentricity_3D << e;
	//}
	//doc_eccentricity_3D << close_array;

	//std::vector<double> height = nest.get_height();

	//auto doc_height = document << "Height" << open_array;
	//for (auto &h : height) {
	//	doc_height << h;
	//}
	//doc_height << close_array;

	bsoncxx::document::value final_document = document << finalize;

	auto collection = _connection [db][coll];

	collection.insert_one(final_document.view());
}

void Mongo::insert_random_test(std::vector<int> counts, int test_id)
{
	using bsoncxx::builder::stream::open_array;
	using bsoncxx::builder::stream::close_array;
	using bsoncxx::builder::stream::finalize;
	using bsoncxx::builder::core;

	bsoncxx::builder::stream::document document{ };

	document << "Test ID" << test_id;

	auto doc_array = document << "Percentages" << open_array;

	for (auto &count: counts) {
		doc_array << count;
	}
	doc_array << close_array;

	bsoncxx::document::value final_document = document << finalize;

	auto collection = _connection["randomness_validation"]["tests"];

	collection.insert_one(final_document.view());
}


