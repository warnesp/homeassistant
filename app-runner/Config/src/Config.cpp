#include "Config.h"

#include <fstream>

#include "JsonKeys.h"

using json = nlohmann::json;

namespace Config {

    bool JsonConfig::parse(std::string const & fileName) {
        // read a JSON file
        std::ifstream in(fileName.c_str()); 

        try { 
            in >> data;
        } catch ( nlohmann::detail::parse_error ) {
            return false;
        }

        return true;
    }

    bool JsonConfig::doesAllowShutdownExists() const noexcept {
        return data.contains(KeyAllowShutdown);
    }

    bool JsonConfig::getAllowShutdown() const {
        return doesAllowShutdownExists() ? data[KeyAllowShutdown].get<bool>() : DefaultAllowShutdown;
    }

    bool JsonConfig::doesBrowserExists() const noexcept {
        return data.contains(KeyBrowser);
    }

    std::string JsonConfig::getBrowser() const {
        return doesBrowserExists() ? data[KeyBrowser].get<std::string>() : DefaultBrowser;
    }

    bool JsonConfig::doesPortExists() const noexcept {
        return data.contains(KeyPort);
    }

    int JsonConfig::getPort() const {
        return doesPortExists() ? data[KeyPort].get<int>() : DefaultPort;
    }

    bool JsonConfig::doesSenderExists() const noexcept {
        return data.contains(KeySender);
    }

    std::string JsonConfig::getSender() const {
        return doesSenderExists() ? data[KeySender].get<std::string>() : DefaultSender;
    }

    bool JsonConfig::doesSiteCommandsExists() const noexcept {
        return data.contains(KeySiteCommands);
    }

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
