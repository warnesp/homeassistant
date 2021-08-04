#include "Listener.h"

#include <chrono>
#include <iostream>


#define LOCK std::lock_guard<std::mutex> guard(listeners_lock)

namespace kn = kissnet;

constexpr std::chrono::seconds SLEEP_TIME(2);

UdpListener::UdpListener() {

	//Socket used to receive, the "endpoint" is where to listen to data
	listen_socket = kn::udp_socket(kn::endpoint("0.0.0.0", 5577));
	listen_socket.bind();

	//Kick off the listener thread
    runner = std::thread(&UdpListener::run,this);
}

UdpListener::~UdpListener() {
	stop();
}

void UdpListener::stop() {
	running = false;
	listen_socket.close();
    runner.detach();
}

bool UdpListener::addListener(std::string_view key, Callback handle) {
	LOCK;
	return listeners.emplace(key, handle).second;
}

void UdpListener::removeListener(std::string_view key) {
	LOCK;
	listeners.erase(key);
}


void UdpListener::notify(std::string_view key) {
	LOCK;
	auto listener = listeners.find(key);
	if(listener != listeners.end()) {
		listener->second();
	}
}

std::string_view UdpListener::readData(kn::buffer<255> &readBuffer) {

	//read in data
	auto [received_bytes, status] = listen_socket.recv(readBuffer);
	const auto from = listen_socket.get_recv_endpoint();

	// make sure data is null terminated
	auto lastByte = received_bytes < readBuffer.size() ? received_bytes : (readBuffer.size() - 1);
	readBuffer[lastByte] = std::byte { '\0' };

	//convert to string
	auto data = std::string_view(reinterpret_cast<const char*>(readBuffer.data()));

    std::cout << "Data from: " << from.address << " :: *" << data << "*\n";

	return data;
}


// function run by thread to make waiting for messages non-blocking
void UdpListener::run() {

	//per thread buffer
	kn::buffer<255> readBuffer;

	// run until stop is called
	while(running) {

		//read in the next packet
		auto data = readData(readBuffer);

		//push data to listeners
		notify(data);
		
  		std::this_thread::sleep_for(SLEEP_TIME);
	}
}
