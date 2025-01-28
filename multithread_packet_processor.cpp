#include "multithreaded_packet_processor.h"
#include <iostream>


MultithreadedPacketProcessor::MultithreadedPacketProcessor(
    size_t threadCount,
    const std::function<void(const std::string&)>& processPacket)
    : threadCount(threadCount), processPacket(processPacket), stopFlag(false) {}

// Start the worker threads
void MultithreadedPacketProcessor::start() {
    for (size_t i = 0; i < threadCount; ++i) {
        threads.emplace_back(&MultithreadedPacketProcessor::workerThread, this);
    }
}

// Enqueue a packet for processing bc wdym ive to wait in line
void MultithreadedPacketProcessor::enqueuePacket(const std::string& packetData) {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        packetQueue.push(packetData);
    }
    condition.notify_one(); // packet arrival notification sent to one thread (will come back to this later)
}


void MultithreadedPacketProcessor::stop() {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        stopFlag = true;
    }
    condition.notify_all(); // Notify all threads to exit


    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

// Worker thread function
void MultithreadedPacketProcessor::workerThread() {
    while (true) {
        std::string packetData;

        {
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [this]() { return !packetQueue.empty() || stopFlag; });

            if (stopFlag && packetQueue.empty()) {
                return;
            }

            packetData = packetQueue.front();
            packetQueue.pop();
        }


        processPacket(packetData);
    }
}
