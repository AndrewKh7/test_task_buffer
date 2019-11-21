#pragma once
#include <iostream>

class Buffer{
public:
    Buffer(uint32_t length);
    ~Buffer();
    uint32_t addBytes(const uint8_t *data, uint32_t len);
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

    Buffer operator=(Buffer &other);
    Buffer operator*(Buffer &other);
};