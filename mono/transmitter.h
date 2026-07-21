#pragma once

#include "../constants.h"
#include <algorithm>

namespace mono {

static const uint16_t FLUSH_SIZE = 128;
static const uint16_t SAFTEY_FACTOR = 2;
static const uint16_t TRANSMISSION_BUFFER_SIZE = FLUSH_SIZE * SAFTEY_FACTOR;
// static_assert(TRANSMISSION_BUFFER_SIZE / BLOCK_SIZE is one bit);

typedef void (*transmitCallback)(uint8_t* buff, size_t size);

// TODO: rename me
class Transmittor {

    float buffer[TRANSMISSION_BUFFER_SIZE] = { 0.0f };
    uint16_t length = 0;
    bool full = false;

public:
    void add(float* buffer) {
        // dear Future Henry,
        // 
        // depending on how task switching works this will not work due to a race condition.
        // 
        // fuck.
        // 
        // sincerely,
        //  - Hank

        std::copy(buffer, buffer + BLOCK_SIZE, this->buffer + this->length);

        this->length += BLOCK_SIZE;

        if (this->length >= FLUSH_SIZE) {
            this->full = true;
        }
    }

    bool should_flush() {
        return this->full;
    }

    void flush(transmitCallback callback) {
        callback((uint8_t*) this->buffer, this->length * sizeof(float));

        this->length = 0;
        this->full = false;
    }

};

// 

// float TRANSMISSION_BUFFER[TRANSMISSION_BUFFER_SIZE] = { 0.0f };

// void add_to_transmission(float* buffer, int size) {
//     static int transmision_buffer_length = 0;

//     // TODO: use std::copy or memcpy here
//     std::copy(buffer, buffer + size, TRANSMISSION_BUFFER + transmision_buffer_length);
 
//     transmision_buffer_length += size;

//     if (transmision_buffer_length == TRANSMISSION_BUFFER_SIZE) {
//         transmision_buffer_length = 0;
        
//     }
// }

}