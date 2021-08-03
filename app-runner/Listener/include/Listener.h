#include <functional>
#include <map>
#include <mutex>
#include <string_view>
#include <thread>

#include "kissnet.hpp"

class UdpListener {
	

	kissnet::udp_socket listen_socket;

	std::map<std::string_view, std::function<void()>> listeners;
	std::mutex listeners_lock;

	std::thread runner;


	bool running = true;




	public:

		UdpListener();
		~UdpListener();

	    ///adds a listener for the given key, returns true if added, and false otherwise
		bool addListener(std::string_view key, std::function<void()> handle);

		///removes a listener for the given key
		void removeListener(std::string_view key);


	private:

		void notify(std::string_view key);
		std::string_view readData(kissnet::buffer<255> &readBuffer);
		void run();
};



