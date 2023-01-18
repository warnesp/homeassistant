#include <iostream>
#include <thread>

#include "Arguments.h"
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


int main (int argc, char *argv[]) {
    runner::Arguments args(argc, argv);

    if(!args.run) { return 0; }

    // read config file for keys, command pairs
    Config::JsonConfig config;
    if(config.parse(args.configFilePath)) {

        // setup UdpListener
        UdpListener listener;
        setupListener(listener, config);

        // start the listener
        listener.start();

        // keep running until quit is signaled
        Commands::waitToQuit();
    } else {
        std::cout << "Could not read config file: " << args.configFilePath << "\n";
    }

    return 0;
}
