#include "kmp.h"
#include "packet_capture.h"
#include <iostream>
#include <string>

// Callback to process packet data
void processPacket(const unsigned char* data, int length) {
    std::string packetData(reinterpret_cast<const char*>(data), length);
    KMP kmp("malicious-pattern"); // Example pattern
    auto matches = kmp.search(packetData);

    if (!matches.empty()) {
        std::cout << "Intrusion detected! Pattern found at offsets: ";
        for (auto offset : matches) {
            std::cout << offset << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    PacketCapture capturer;
    capturer.startCapture("eth0", processPacket); // Replace "eth0" with your network interface
    return 0;
}
