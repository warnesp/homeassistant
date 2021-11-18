#include <iostream>
#include <thread>

#include "AppRunnerConfig.h"

#include "Commands.h"
#include "Config.h"
#include "Listener.h"

void setupListener(UdpListener& listener, Config::JsonConfig const &  config) {
    // basic listener setup
    listener.setPort(config.getPort());
    if(config.doesSenderExists()) {
        listener.setFilter(config.getSender());
    }

    // add built in listeners
    listener.addListener(Commands::QuitKey, Commands::quit);

    if(config.getAllowShutdown()) {
        listener.addListener(Commands::ShutdownKey, Commands::shutdownComputer);
    }

    Commands::Browsers browser = Commands::stringToBrowser(config.getBrowser());

    // add commands from file
    for(auto const & [key, value] : config.getSiteCommands()) {
        std::cout << "Adding " << key << " " << value << "\n";
        listener.addListener(key, std::bind(Commands::runInBrowser, browser, value));
    }
}

// Returns if execution should continue
bool handleArgs(int argc, char *argv[]) {
    // print out the version info if any extra parameters are given
    if (argc >= 2 && std::string(argv[1]) == std::string("-v")) {
        std::cout << argv[0] << " Version " 
            << AppRunner_VERSION_MAJOR << "." << AppRunner_VERSION_MINOR 
            << std::endl;
        return false;
    }

    return true;
}

int main (int argc, char *argv[]) {
    
    if(!handleArgs(argc, argv)) {
        return 0;
    }

    // read config file for keys, command pairs
    Config::JsonConfig config;
    if(config.parse(CONFIG_FILE_NAME)) {

        // setup UdpListener
        UdpListener listener;
        setupListener(listener, config);

        // start the listener
        listener.start();

        // keep running until quit is signaled
        Commands::waitToQuit();
    } else {
        std::cout << "Could not read config file: " << CONFIG_FILE_NAME << "\n";
    }

    return 0;
}
