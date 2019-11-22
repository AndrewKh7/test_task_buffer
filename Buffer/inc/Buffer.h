#pragma once
#include <stdint.h>
#include <mutex>
#include <thread>

class Buffer{
public:
    Buffer(uint32_t length);
    ~Buffer();
    uint32_t addBytes(uint8_t const *data, uint32_t len);
    uint32_t readBytes(uint8_t *data, uint32_t len);
    uint32_t getQuantityEmptyBytes();
    uint32_t getQuantityBusyBytes();
    uint32_t getLength();

private:
    uint8_t *buf;
    uint32_t length;
    uint32_t start;
    uint32_t busyBytes;
    uint32_t end;
    std::mutex mtx;
    
    Buffer(Buffer const &);
    Buffer operator=(Buffer const &);
    Buffer operator*(Buffer const &);
};