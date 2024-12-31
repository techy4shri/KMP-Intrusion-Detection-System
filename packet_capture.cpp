#include "packet_capture.h"
#include <pcap.h>
#include <iostream>

// Callback function for processing packets
void packetCallback(u_char* args, const struct pcap_pkthdr* header, const u_char* packet) {
    auto handler = reinterpret_cast<PacketCapture*>(args);
    handler->handlePacket(packet, header->len);
}

// Start capturing packets
void PacketCapture::startCapture(const std::string& interface, void (*callback)(const unsigned char*, int)) {
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
