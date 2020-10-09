#pragma once

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

class Mongo {
private:
	mongocxx::instance _instance{ };
	mongocxx::client _connection{ mongocxx::uri{ } };

public:
	void insert_one(Nest nest, int nest_number, const char* db, const char* coll);
	void insert_random_test(std::vector<int> counts, int test_id);
};

