#include <functional>
#include <map>
#include <mutex>
#include <string_view>
#include <thread>

#include "kissnet.hpp"

using Callback = std::function<void()>;

class UdpListener {
	
	kissnet::udp_socket listen_socket;

	std::map<std::string_view, Callback> listeners;
	std::mutex listeners_lock;

	std::thread runner;

	bool running = true;

	public:

		UdpListener();
		~UdpListener();

		UdpListener(const UdpListener&) = delete;
		UdpListener& operator=(const UdpListener&) = delete;

		///lets the thread know it should exit
		void stop();

	    ///adds a listener for the given key, returns true if added, and false otherwise
		bool addListener(std::string_view key, Callback handle);

		///removes a listener for the given key
		void removeListener(std::string_view key);


	private:

		void notify(std::string_view key);
		std::string_view readData(kissnet::buffer<255> &readBuffer);
		void run();
};

