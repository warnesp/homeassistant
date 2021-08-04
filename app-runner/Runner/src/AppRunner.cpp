#include <iostream>
#include <chrono>
#include <thread>

#include "AppRunnerConfig.h"


#include "Listener.h"

bool running = true;

//launches firefox with the given site
void firefox(std::string_view site) {
	std::string base = "firefox \"";
	base.append(site).append("\"");
	system(base.c_str());
}


void quit() { running = false; }

int main (int argc, char *argv[])
{
  if (argc >= 2)
  {

	  std::cout << argv[0] << " Version " 
		  << AppRunner_VERSION_MAJOR << "." << AppRunner_VERSION_MINOR 
		  << std::endl;
    return 1;
  }


  //TODO read config file for keys, command pairs
  
  //setup UdpListener
  UdpListener listener;

  //TODO handle notifications
  listener.addListener("foo", std::bind(firefox, "www.netflix.com"));
  listener.addListener("bar", std::bind(firefox, "www.crunchyroll.com"));
  listener.addListener("quit", quit);

  // wait to quit
  while(running) {
	std::this_thread::sleep_for (std::chrono::seconds(2));
  }


  return 0;
}
