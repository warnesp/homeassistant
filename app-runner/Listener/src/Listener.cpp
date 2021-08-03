#include "Listener.h"


namespace kn = kissnet;

UdpListener::UdpListener() {

	//Socket used to receive, the "endpoint" is where to listen to data
	listen_socket = kn::udp_socket(kn::endpoint("0.0.0.0", 5577));
	listen_socket.bind();

    runner = std::thread(&UdpListener::run,this);
}

UdpListener::~UdpListener() {
	running = false;
}

bool UdpListener::addListener(std::string_view key, std::function<void()> handle) {
	std::lock_guard<std::mutex> guard(listeners_lock);
	return listeners.emplace(key, handle).second;
}

void UdpListener::removeListener(std::string_view key) {
	std::lock_guard<std::mutex> guard(listeners_lock);
	listeners.erase(key);
}


void UdpListener::notify(std::string_view key) {
	std::lock_guard<std::mutex> guard(listeners_lock);
	auto listener = listeners.find(key);
	if(listener != listeners.end()) {
		listener->second();
	}

}

std::string_view UdpListener::readData(kn::buffer<255> &readBuffer) {
	//read in data
	auto [received_bytes, status] = listen_socket.recv(readBuffer);
	//const auto from = listen_socket.get_recv_endpoint();

	// make sure data is null terminated
	if(received_bytes < readBuffer.size()) {
		readBuffer[received_bytes] = std::byte { '\0' };
	} else { 
		readBuffer[readBuffer.size() - 1] = std::byte { '\0' };
	}

	//convert to string
	return std::string_view(reinterpret_cast<const char*>(readBuffer.data()));
}


// function run by thread to make waiting for messages non-blocking
void UdpListener::run() {

	//per thread buffer
	kn::buffer<255> readBuffer;

	while(running) {

		//read in the next packet
		auto data = readData(readBuffer);

		//push data to listeners
		notify(data);
		
	}
}
