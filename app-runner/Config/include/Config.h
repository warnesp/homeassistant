#include <map>
#include <string>

#include "json.hpp"

class Config {

	nlohmann::json data;


	public:

		std::string getBrowser() const;

		std::map<std::string, std::string> getCommands() const;

		void parse(std::string fileName);
};

