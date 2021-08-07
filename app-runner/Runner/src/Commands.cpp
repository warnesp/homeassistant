#include "Commands.h"

#include <chrono>
#include <iostream>
#include <thread>

namespace Commands {
    bool thread_running = true;
    constexpr std::chrono::seconds WAIT_TIME(2);

    //launches firefox with the given site
    void runInBrowser(std::string_view browser, std::string_view site) {
        std::cout << "Opening site " << site << " in "<< browser << "\n";

        std::string base = std::string(browser).append(" \"").append(site).append("\"");
        system(base.c_str());
    }

    void shutdownComputer() { system("systemctl poweroff"); }

    void quit() { thread_running  = false; }

    void waitToQuit() {
        while(thread_running) {
            std::this_thread::sleep_for(WAIT_TIME);
        }
    }

}

