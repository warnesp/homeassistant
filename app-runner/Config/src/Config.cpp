#include "Config.h"

#include <fstream>

#include "JsonKeys.h"

using namespace std;
using json = nlohmann::json;

string Config::getBrowser() const {
	return data.contains(KEY_BROWSER) 
		? data[KEY_BROWSER].get<string>() 
		: DEFAULT_BROWSER;
}

map<string, string> Config::getCommands() const {
	map<string, string> results;

	for(auto& [key, value] : data[KEY_COMMANDS].items()) {
		results.emplace(key, value.get<string>());
	}

	return results;
}

void Config::parse(string fileName) {
	// read a JSON file
	ifstream in(fileName.c_str());	

	in >> data;
}

