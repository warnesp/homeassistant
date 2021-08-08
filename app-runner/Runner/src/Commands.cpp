#include "Commands.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>

namespace Commands {
    bool thread_running = true;
    constexpr std::chrono::seconds WAIT_TIME(2);

    constexpr auto FIREFOX_CMD = "firefox";
    constexpr auto CHROMIUM_CMD = "chromimum";
    constexpr auto CHROME_CMD = "chrome";
    constexpr std::array<std::string_view, 3> BrowserStrings = {FIREFOX_CMD, CHROMIUM_CMD, CHROME_CMD};


    //launches the given site in the chosen browser
    void runInBrowser(Browsers browser, std::string_view site) {

        std::cout << "Opening site " << site << " in "<< browser << "\n";

        std::string base = std::string(BrowserStrings[browser]).append(" \"").append(site).append("\"");
        system(base.c_str());
    }

    void shutdownComputer() { system("systemctl poweroff"); }

    void quit() { thread_running  = false; }

    void waitToQuit() {
        while(thread_running) {
            std::this_thread::sleep_for(WAIT_TIME);
        }
    }

    Browsers stringToBrowser(std::string_view str){
        auto i = std::find(BrowserStrings.begin(), BrowserStrings.end(), str) - BrowserStrings.begin();

        return static_cast<Browsers>((i != BrowserStrings.size()) * i);
    }
}

