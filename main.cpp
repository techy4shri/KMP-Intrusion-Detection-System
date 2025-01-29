#include "kmp.h"
#include "packet_capture.h"
#include "multithreaded_packet_processor.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <fstream>

// Define known malicious patterns , this will be updated as I go
const std::vector<std::string> THREAT_PATTERNS = {
    "malicious-pattern",
    "sql-injection",
    "xss-attack",
    "buffer-overflow"
};

// Log file for alerts
std::ofstream alert_log("intrusion_alerts.log", std::ios::app);

void logAlert(const std::string& pattern, size_t offset) {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    alert_log << std::ctime(&time) 
              << "ALERT: Pattern '" << pattern 
              << "' found at offset " << offset << std::endl;
}

// Packet processing callback
void processPacketCallback(const std::string& packetData) {
    try {
        for (const auto& pattern : THREAT_PATTERNS) {
            KMP kmp(pattern);
            auto matches = kmp.search(packetData);

            if (!matches.empty()) {
                std::cout << "\n[!] INTRUSION DETECTED" << std::endl;
                std::cout << "Pattern: " << pattern << std::endl;
                std::cout << "Locations: ";

                for (auto offset : matches) {
                    std::cout << offset << " ";
                    logAlert(pattern, offset);
                }
                std::cout << "\n" << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error processing packet: " << e.what() << std::endl;
    }
}

int main() {
    try {
        MultithreadedPacketProcessor processor(4, processPacketCallback);
        bool captureResult;
        processor.start();

        PacketCapture capturer;
        std::cout << "KMP-based Intrusion Detection System" << std::endl;
        std::cout << "Monitoring network traffic..." << std::endl;
        std::cout << "Loaded " << THREAT_PATTERNS.size() << " threat patterns" << std::endl;

    void packetHandler(const unsigned char* data, int length); {
    std::string packetData(reinterpret_cast<const char*>(data), length);
    processor.enqueuePacket(packetData);
    }

capturer.startCapture("eth0", packetHandler);

        if (!captureResult) {
            throw std::runtime_error("Failed to start packet capture");
        }

        std::cout << "Press Ctrl+C to stop" << std::endl;
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
