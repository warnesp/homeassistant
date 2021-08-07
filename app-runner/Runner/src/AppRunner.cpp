#include <chrono>
#include <iostream>
#include <thread>

#include "AppRunnerConfig.h"

#include "Config.h"
#include "Listener.h"

constexpr std::chrono::seconds WAIT_TIME(2);

bool running = true;

//launches firefox with the given site
void firefox(std::string_view site) {
	std::cout << "Opening site " << site << " in firefox\n";

	std::string base = "firefox \"";
	base.append(site).append("\"");
	system(base.c_str());
}

void shutdownComputer() { system("systemctl poweroff"); }

void quit() { running = false; }

void setupListeners(UdpListener& listener, Config const &  config) {
	listener.addListener("quit", quit);
	listener.addListener("shutdown", shutdownComputer);

	for(auto const & [key, value] : config.getCommands()) {
		std::cout << "Adding " << key << " " << value << "\n";
		listener.addListener(key, std::bind(firefox, value));
	}
}

void waitToQuit() {
	while(running) {
		std::this_thread::sleep_for(WAIT_TIME);
	}
}

int main (int argc, char *argv[]) {
	if (argc >= 2) {
		std::cout << argv[0] << " Version " 
			<< AppRunner_VERSION_MAJOR << "." << AppRunner_VERSION_MINOR 
			<< std::endl;
		return 1;
	}

	// read config file for keys, command pairs
	Config config;
	config.parse(CONFIG_FILE_NAME);

	// setup UdpListener
	UdpListener listener;
	listener.setPort(config.getPort());
	if(config.doesSenderExists()) {
		listener.setFilter(config.getSender());
	}
	listener.start();

	setupListeners(listener, config);

	waitToQuit();

	return 0;
}
