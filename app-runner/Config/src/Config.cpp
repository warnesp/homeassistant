#include "Config.h"

#include <fstream>

#include "JsonKeys.h"

using json = nlohmann::json;

#define DEFAULT_EXISTS(name)\
bool JsonConfig::does##name##Exists () const noexcept {\
    return data.contains(Key##name);\
}

#define DEFAULT_GETTER(type, name)\
DEFAULT_EXISTS(name)\
type JsonConfig::get##name () const {\
    return does##name##Exists () ? data[Key##name].get<type>() : Default##name ;\
}

namespace Config {

    DEFAULT_GETTER(bool, AllowShutdown)
    DEFAULT_GETTER(std::string, Browser)
    DEFAULT_GETTER(int, Port)
    DEFAULT_GETTER(std::string, Sender)

    Commands JsonConfig::getCommands() const {
        Commands results;

        if(doesCommandsExists()) {
            for(auto& [key, value] : data[KeyCommands].items()) {
                results.emplace(key, value.get<std::string>());
            }
        }

        return results;
    }

    DEFAULT_EXISTS(Commands)

        void JsonConfig::parse(std::string const & fileName) {
            // read a JSON file
            std::ifstream in(fileName.c_str()); 

            in >> data;
        }
}
