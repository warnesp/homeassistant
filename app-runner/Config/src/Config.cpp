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

    void JsonConfig::parse(std::string const & fileName) {
        // read a JSON file
        std::ifstream in(fileName.c_str()); 

        in >> data;
    }

    DEFAULT_GETTER(bool, AllowShutdown)
    DEFAULT_GETTER(std::string, Browser)
    DEFAULT_GETTER(int, Port)
    DEFAULT_GETTER(std::string, Sender)

    DEFAULT_EXISTS(SiteCommands)

    Commands JsonConfig::getSiteCommands() const {
        Commands results;

        if(doesSiteCommandsExists()) {
            for(auto& [key, value] : data[KeySiteCommands].items()) {
                results.emplace(key, value.get<std::string>());
            }
        }

        return results;
    }

}
