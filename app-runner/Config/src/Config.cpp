#include "Config.h"

#include <iostream>
#include <fstream>


using namespace std;
using json = nlohmann::json;


map<string_view, string> Config::getCommands() {
	map<string_view, string> results;

	for(auto& [key, value] : data["commands"].items()) {
		cout << key << " " << value.get<string>() << endl;
		results.emplace(key, value.get<string>());
	}

	return results;
}

void Config::parse(string fileName) {
	// read a JSON file
	ifstream in(fileName.c_str());	

	in >> data;
}

