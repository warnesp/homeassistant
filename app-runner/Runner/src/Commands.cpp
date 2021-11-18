#include "Commands.h"

#include <algorithm>
#include <chrono>
#include <future>
#include <iostream>
#include <thread>

namespace Commands {

    // used to keep main thread from exiting while waiting for a quit command
    std::promise<void> barrier;

    constexpr auto FIREFOX_CMD = "firefox";
    constexpr auto CHROMIUM_CMD = "chromimum";
    constexpr auto CHROME_CMD = "chrome";
    constexpr std::array<std::string_view, 3> BrowserStrings = {FIREFOX_CMD, CHROMIUM_CMD, CHROME_CMD};

    // launches the given site in the chosen browser
    void runInBrowser(Browsers browser, std::string_view site) {

        std::string browserStr(browserToString(browser));

        std::cout << "Opening site " << site << " in "<< browserStr << "\n";

        std::string base = browserStr.append(" \"").append(site).append("\"");
        system(base.c_str());
    }

    void shutdownComputer() { 
        system("systemctl poweroff"); 
        quit();
    }

    void quit() { barrier.set_value(); }

    void waitToQuit() {
        barrier.get_future().wait();
    }

    Browsers stringToBrowser(std::string_view str) {
        auto i = std::find(BrowserStrings.begin(), BrowserStrings.end(), str) - BrowserStrings.begin();

        // convert to enum value, if not found, use first enum
        return static_cast<Browsers>((i != BrowserStrings.size()) * i);
    }

    std::string_view browserToString(Browsers b) {
        return BrowserStrings[static_cast<int>(b)];
    }
}

