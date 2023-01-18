#pragma once

#include <string>

namespace runner {

    struct Arguments {
        explicit Arguments(int argc, char *argv[]);

        std::string configFilePath;
        bool run = false;
    };

    // Returns if execution should continue
}
