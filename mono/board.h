#pragma once

#include <variant>
#include <cstdint>
#include <concepts>
#include "transform/transform.h"
#include "transform/distortion.h"
#include "transform/octave.h"

static const uint16_t POOL_SIZE = 4;
static const uint16_t MAX_EFFECTS = 4;

namespace mono {

using TransformVariant = std::variant<distortion::SoftClip, distortion::HardClip, octaver::Up>;

class Board {

    TransformVariant transformPool[POOL_SIZE];          // used for actually storing the classes
    Transform* transforms[MAX_EFFECTS] = { nullptr } ;  // orders the pooled classes
    int length = 0;

    bool mute = false;

public:
    void clear() {

        for (int i = 0; i < MAX_EFFECTS; i++) {
            this->transforms[i] = nullptr;
        }

        this->length = 0;
    }

    template <class T>//, class Transform>
    void add() {
        static_assert(std::derived_from<T, Transform>);

        this->transformPool[this->length].emplace<T>();
        this->transforms[this->length] = std::get_if<T>(&this->transformPool[this->length]);
        this->transforms[this->length]->init();
        
        this->length++;
    }

    Transform* get(int index) {
        // if (index >= this->length) {
        //     throw "KILL YOURSELF!";
        // } 

        return this->transforms[index];
    }

    float process(float sample) {
        // if (this->mute) {
        //     return 0.0f;
        // }
        
        for (int i = 0; i < MAX_EFFECTS; ++i) {
            Transform* transform = this->transforms[i];

            if (transform == nullptr) {
                break;
            }

            sample = transform->process(sample);
        }

        return sample;
    }



    // simple_transform_t transforms[MAX_TRANSFORMS] = {nullptr}; 
    // float params[MAX_TRANSFORMS][MAX_PARAMS] = {0.f};

    // float process(float sample) {
    //     float value = sample;
        
    //     for (int i = 0; i < MAX_TRANSFORMS; ++i) {
    //         if (this->transforms[i] != nullptr) {
    //             value = this->transforms[i](value, params[i]);
    //         }
    //     }

    //     return value;
    // }

};

}