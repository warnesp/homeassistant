#include <array>
#include <string>
#include <string_view>

namespace Commands {

    constexpr auto QuitKey = "quit";
    constexpr auto ShutdownKey = "shutdown";

    enum Browsers { FIREFOX, CHROME, CHROMIUM };

    // launches browser with the given site
    void runInBrowser(Browsers browser, std::string_view site); 

    /// shutsdown the computer
    void shutdownComputer();

    /// causes the wait loop to exit
    void quit(); 

    /// used to wait in a loop until quit is called
    void waitToQuit();


    Browsers stringToBrowser(std::string_view str);
}
