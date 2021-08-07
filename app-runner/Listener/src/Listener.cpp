#include "Listener.h"

#include <chrono>
#include <iostream>

#define LOCK std::lock_guard<std::mutex> guard(listeners_lock)

namespace kn = kissnet;

constexpr std::chrono::seconds SLEEP_TIME(2);

UdpListener::~UdpListener() {
    stop();
}

void UdpListener::start() {
    //Socket used to receive, the "endpoint" is where to listen to data
    listen_socket = kn::udp_socket(kn::endpoint("0.0.0.0", port));
    listen_socket.bind();

    //Kick off the listener thread
    runner = std::thread(&UdpListener::run,this);

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

void UdpListener::setFilter(std::string_view ip) noexcept {
    filterIp = ip;
}

void UdpListener::setPort(int port) noexcept {
    this->port = port;
}

void UdpListener::notify(std::string_view key) {
    LOCK;
    auto listener = listeners.find(key);
    if(listener != listeners.end()) {
        listener->second();
    }
}

template<std::size_t T>
std::string UdpListener::readData(kn::buffer<T> &readBuffer) {

    constexpr auto endOfBuffer = T - 1;
    constexpr auto nullByte = std::byte { '\0' };

    //clear out any previous data
    readBuffer.fill(nullByte);

    //read in data
    auto [received_bytes, status] = listen_socket.recv(readBuffer);
    const auto from = listen_socket.get_recv_endpoint();

    // make sure data is null terminated
    readBuffer[endOfBuffer] = nullByte;

    return from.address;
}


// function run by thread to make waiting for messages non-blocking
void UdpListener::run() {

    //per thread buffer
    kn::buffer<255> readBuffer;

    const bool allowAll = filterIp == ANY_IP;

    // run until stop is called
    while(running) {

        //read in the next packet
        auto from = readData(readBuffer);

        //filter data based on IP
        if(allowAll || filterIp == from) {
            //convert to string
            auto data = std::string_view(reinterpret_cast<const char*>(readBuffer.data()));

            std::cout << "Data from: " << from << " :: *" << data << "*\n";

            //push data to listeners
            notify(data);
        }

        std::this_thread::sleep_for(SLEEP_TIME);
    }
}
