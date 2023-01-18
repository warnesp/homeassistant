#include "Arguments.h"

#include "AppRunnerConfig.h"

#include <iostream>

using namespace runner;

Arguments::Arguments(int argc, char *argv[])
    : configFilePath(CONFIG_FILE_NAME) {

    if (argc >= 2) {
        std::string arg(argv[1]);
        if(arg == "-v") {
            // print version info
            std::cout << argv[0] << " Version "
                << AppRunner_VERSION_MAJOR << "." << AppRunner_VERSION_MINOR
                << std::endl;
            run = false;
        } else {
            configFilePath = arg;
        }
    }

    run = true;
}
