#ifndef PACKET_CAPTURE_H
#define PACKET_CAPTURE_H

#include <string>
#include <functional>

class PacketCapture {
public:
    void startCapture(const std::string& interface, std::function<void(const unsigned char*, int)> callback);
    void handlePacket(const unsigned char* data, int length);
    bool isCapturing() const;

private:
    bool capturing = false;
    std::function<void(const unsigned char*, int)> callback;
};

#endif