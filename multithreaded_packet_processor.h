#ifndef MULTITHREADED_PACKET_PROCESSOR_H
#define MULTITHREADED_PACKET_PROCESSOR_H

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <vector>
#include <string>

class MultithreadedPacketProcessor {
public:
    MultithreadedPacketProcessor(size_t threadCount, const std::function<void(const std::string&)>& processPacket);

    void start();

    // Add a new packet for processing
    void enqueuePacket(const std::string& packetData);


    void stop();

private:
    size_t threadCount;
    std::vector<std::thread> threads;

    // Packet queue and synchronization primitives
    std::queue<std::string> packetQueue;
    std::mutex queueMutex;
    std::condition_variable condition;

    bool stopFlag;

    // Packet processing callback
    std::function<void(const std::string&)> processPacket;

    // Thread worker function
    void workerThread();
};

#endif
