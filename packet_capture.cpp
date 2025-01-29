#include "packet_capture.h"
#include <pcap.h>
#include <iostream>

class PacketCapture {

public:

    void startCapture(const std::string& interface, std::function<void(const unsigned char*, int)> callback);

    bool isCapturing() const; // Add this method declaration

    // Add other methods and members here

private:

    bool capturing = false; // Add this member variable

};

// Callback function for processing packets
void packetCallback(u_char* args, const struct pcap_pkthdr* header, const u_char* packet) {
    auto handler = reinterpret_cast<PacketCapture*>(args);
    handler->handlePacket(packet, header->len);
}

// Start capturing packets
void PacketCapture::startCapture(const std::string& interface, std::function<void(const unsigned char*, int)> callback) {

    capturing = true; // Set capturing to true when capture starts

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* handle = pcap_open_live(interface.c_str(), BUFSIZ, 1, 1000, errbuf);

    if (handle == nullptr) {
        std::cerr << "Error opening device: " << errbuf << std::endl;
        return;
    }

    pcap_loop(handle, 0, packetCallback, reinterpret_cast<u_char*>(this));
}

// Handle packet data (example: print first 20 bytes)
void PacketCapture::handlePacket(const unsigned char* data, int length) {
    std::cout << "Packet captured with length: " << length << std::endl;

    // You can pass the data to a custom callback for processing
}
