#include <chrono>
#include <iostream>
#include <thread>

#include "AppRunnerConfig.h"

#include "Config.h"
#include "Listener.h"

bool running = true;

//launches firefox with the given site
void firefox(std::string_view site) {
	std::cout << "Opening site " << site << " in firefox\n";

	std::string base = "firefox \"";
	base.append(site).append("\"");
	system(base.c_str());
}


void quit() { running = false; }

int main (int argc, char *argv[]) {
	if (argc >= 2) {
		std::cout << argv[0] << " Version " 
			<< AppRunner_VERSION_MAJOR << "." << AppRunner_VERSION_MINOR 
			<< std::endl;
		return 1;
	}

	// read config file for keys, command pairs
	Config c;
	c.parse(CONFIG_FILE_NAME);

	// setup UdpListener
	UdpListener listener;

	// handle notifications
	listener.addListener("quit", quit);

	for(auto& [key, value] : c.getCommands()) {
		std::cout << "Adding " << key << " " << value << "\n";
		listener.addListener(key, std::bind(firefox, value));
	}

	// wait to quit
	while(running) {
		std::this_thread::sleep_for (std::chrono::seconds(2));
	}

	return 0;
}
