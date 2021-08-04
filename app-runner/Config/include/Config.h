#include <map>
#include <string>

#include "json.hpp"

class Config {

	nlohmann::json data;


	public:

		std::map<std::string_view, std::string_view> getCommands();

		void parse(std::string fileName);
};

