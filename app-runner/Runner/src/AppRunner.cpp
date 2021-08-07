#include <iostream>
#include <thread>

#include "AppRunnerConfig.h"

#include "Commands.h"
#include "Config.h"
#include "Listener.h"


constexpr auto QuitKey = "quit";
constexpr auto ShutdownKey = "shutdown";

void setupListeners(UdpListener& listener, Config::JsonConfig const &  config) {
    // add built in listeners
    listener.addListener(QuitKey, Commands::quit);

    if(config.getAllowShutdown()) {
        listener.addListener(ShutdownKey, Commands::shutdownComputer);
    }

    // add commands from file
    for(auto const & [key, value] : config.getCommands()) {
        std::cout << "Adding " << key << " " << value << "\n";
        listener.addListener(key, std::bind(Commands::runInBrowser, config.getBrowser(), value));
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
    Config::JsonConfig config;
    config.parse(CONFIG_FILE_NAME);

    // setup UdpListener
    UdpListener listener;
    listener.setPort(config.getPort());
    if(config.doesSenderExists()) {
        listener.setFilter(config.getSender());
    }

    listener.start();

    // wire up config settings to the listener
    setupListeners(listener, config);

    // keep running until quit is signaled
    Commands::waitToQuit();

    return 0;
}
