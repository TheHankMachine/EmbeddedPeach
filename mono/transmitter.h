#pragma once

#include "../constants.h"
#include <algorithm>

namespace mono {

static const uint16_t TRANSMISSION_BUFFER_SIZE = 128;
typedef void (*transmit_callback_t)(uint8_t* buff, size_t size);

// TODO: make more robust
class DoubleTransmissionBuffer {

    float buffers[2][TRANSMISSION_BUFFER_SIZE] = { 0.0f };

    uint16_t buffer_index;
    uint16_t sample_index;

    // there should be a ready per buffer
    // (also gives us a overflow check)
    bool ready = false;

    inline uint16_t other(uint16_t index) {
        return 1 - index;
    }

public:

    inline bool is_ready() {
        return ready;
    }

    void add(float* buffer) {
        // no bounds checking as of now. If the bounds are wrong 
        // then we have bigger, structural problems.
        std::copy(buffer, buffer + BLOCK_SIZE, buffers[buffer_index] + sample_index);

        sample_index += BLOCK_SIZE;

        // TODO: potentially move this assertion somewhere else
        static_assert(TRANSMISSION_BUFFER_SIZE % BLOCK_SIZE == 0);

        // note that since TRANSMISSION_BUFFER_SIZE must be a multiple
        // of BLOCK_SIZE, thus the strictly greater than case should
        // never be hit.
        if (sample_index >= TRANSMISSION_BUFFER_SIZE) {
            buffer_index = other(buffer_index);
            sample_index = 0;
            ready = true;
        }
    }

    void transmit(transmit_callback_t callback) {
        callback((uint8_t*) buffers[other(buffer_index)], sizeof(float) * TRANSMISSION_BUFFER_SIZE);
        this->ready = false;
    }

};

// // TODO: rename me
// class Transmittor {

//     float buffer[TRANSMISSION_BUFFER_SIZE] = { 0.0f };
//     uint16_t length = 0;
//     bool full = false;

// public:
//     void add(float* buffer) {

//         if (this->length + BLOCK_SIZE > TRANSMISSION_BUFFER_SIZE) {
//             // buffer overrun. this is quite bad.

//             // TODO: handle this
//             return;
//         }

//         // dear Future Henry,
//         // 
//         // depending on how task switching works this will not work 
//         // due to a race condition.
//         // 
//         // fuck.
//         // 
//         // sincerely,
//         //  - Hank

//         std::copy(buffer, buffer + BLOCK_SIZE, this->buffer + this->length);

//         this->length += BLOCK_SIZE;

//         if (this->length >= FLUSH_SIZE) {
//             this->full = true;
//         }
//     }

//     bool should_flush() {
//         return this->full;
//     }

//     void flush(transmit_callback_t callback) {
//         callback((uint8_t*) this->buffer, this->length * sizeof(float));

//         this->length = 0;
//         this->full = false;
//     }

// };

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