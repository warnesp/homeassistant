#include <string>

namespace Commands {

    constexpr auto QuitKey = "quit";
    constexpr auto ShutdownKey = "shutdown";


    // launches browser with the given site
    void runInBrowser(std::string_view browser, std::string_view site); 

    /// shutsdown the computer
    void shutdownComputer();

    /// causes the wait loop to exit
    void quit(); 

    /// used to wait in a loop until quit is called
    void waitToQuit();
}
