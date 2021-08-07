#include <map>
#include <string>

#include "json.hpp"

using Commands = std::map<std::string, std::string>;

class Config {

	nlohmann::json data;

	static constexpr auto DefaultBrowser = "firefox";
	static constexpr auto DefaultPort = 5577;
	static constexpr auto DefaultSender = "0.0.0.0";

	public:
		std::string getBrowser() const;
		Commands getCommands() const;
		int getPort() const;
		std::string getSender() const;

		bool doesBrowserExists() const noexcept;
		bool doesCommandsExists() const noexcept;
		bool doesPortExists() const noexcept;
		bool doesSenderExists() const noexcept;


		void parse(std::string const & fileName);
};

