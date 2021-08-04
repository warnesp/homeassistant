#include "Config.h"

#include <iostream>
#include <fstream>


using namespace std;
using json = nlohmann::json;


map<string_view, string_view> Config::getCommands() {
	map<string_view, string_view> results;

	for(auto& [key, value] : data["commands"].items()) {
		results.emplace(key, value.get<std::string>());
	}

	return results;
}

void Config::parse(string fileName) {
	// read a JSON file
	std::ifstream in(fileName.c_str());	

	in >> data;
}

