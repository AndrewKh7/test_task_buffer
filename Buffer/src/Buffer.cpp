#include <buffer.h>


Buffer::Buffer(uint32_t length){
    this->length = length;
    this->buf = new uint8_t[length];
    this->busyBytes = 0;
    this->start = 0;
    this->end = 0;
}

Buffer::~Buffer(){
    delete[] this->buf;
}

uint32_t Buffer::addBytes(const uint8_t *data, uint32_t len){

    if(this->getQuantityEmptyBytes() < len)
        len = this->getQuantityEmptyBytes();

    for( uint32_t i = 0; i < len; i++){
        this->buf[this->end] = data[i];
        this->busyBytes++;
        this->end = this->end == (this->length - 1) ? 0 : this->end + 1;
    }

    return len;
}

uint32_t Buffer::readBytes(uint8_t *data, uint32_t len){
    if(this->getQuantityBusyBytes() < len)
        len = this->getQuantityBusyBytes();

    for(uint32_t i = 0; i < len; i++){
        data[i] = this->buf[this->start];
        this->busyBytes--;
        this->start = this->start == (this->length - 1) ? 0 : this->start + 1;
    }
    return len;
}

uint32_t Buffer::getQuantityEmptyBytes(){
    return this->length - this->busyBytes;
}

uint32_t Buffer::getQuantityBusyBytes(){
    return this->busyBytes;
}

uint32_t Buffer::getLength(){
    return this->length;
}

Buffer Buffer::operator=(Buffer &other){};
Buffer Buffer::operator*(Buffer &other){};