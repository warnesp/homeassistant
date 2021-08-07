#include <map>
#include <string>

#include "json.hpp"

namespace Config {
    using Commands = std::map<std::string, std::string>;

    class JsonConfig {

        nlohmann::json data;

        static constexpr auto DefaultAllowShutdown = false;
        static constexpr auto DefaultBrowser = "firefox";
        static constexpr auto DefaultPort = 5577;
        static constexpr auto DefaultSender = "0.0.0.0";

        public:
        void parse(std::string const & fileName);

        bool getAllowShutdown() const;
        std::string getBrowser() const;
        Commands getSiteCommands() const;
        int getPort() const;
        std::string getSender() const;

        bool doesAllowShutdownExists() const noexcept;
        bool doesBrowserExists() const noexcept;
        bool doesSiteCommandsExists() const noexcept;
        bool doesPortExists() const noexcept;
        bool doesSenderExists() const noexcept;

    };
}
