#ifndef PACKET_CAPTURE_H
#define PACKET_CAPTURE_H

#include <string>

class PacketCapture {
public:
    
    void startCapture(const std::string& interface, void (*callback)(const unsigned char*, int));

private:
    void handlePacket(const unsigned char* data, int length);
};

#endif
