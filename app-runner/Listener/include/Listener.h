#include <functional>
#include <map>
#include <mutex>
#include <string_view>
#include <thread>

#include "kissnet.hpp"

using Callback = std::function<void()>;

/// Listens on a udp socket (non-blocking) and calls a handler based on the data received.
class UdpListener {
    
    kissnet::udp_socket listen_socket;

    std::map<std::string_view, Callback> listeners;
    std::mutex listeners_lock;

    std::thread runner;

    bool running = true;

    std::string filterIp;
    int port = 5577;

    public:

        static constexpr std::string_view ANY_IP = "0.0.0.0";
        static constexpr std::string_view EMPTY_DATA = "";

        UdpListener() = default;
        ~UdpListener();

        UdpListener(const UdpListener&) = delete;
        UdpListener& operator=(const UdpListener&) = delete;

        ///starts the listening thread
        void start();

        ///lets the thread know it should exit
        void stop();

        ///adds a listener for the given key, returns true if added, and false otherwise
        bool addListener(std::string_view key, Callback handle);

        ///removes a listener for the given key
        void removeListener(std::string_view key);

        void setFilter(std::string_view ip) noexcept;
        void setPort(int port) noexcept;

    private:

        void notify(std::string_view key);
        template<std::size_t T>
        std::string readData(kissnet::buffer<T> &readBuffer);
        void run();
};

