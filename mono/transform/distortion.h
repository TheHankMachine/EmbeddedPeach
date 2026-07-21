#pragma once

#include "transform.h"

namespace mono {
namespace distortion {

class HardClip : public Transform {
    float gain;
    float threshold;

    void init() {
        this->gain = 1.0f;
        this->threshold = 1.0f;
    }

    float process(float sample) {
        float value = sample * this->gain;
        
        if (value > this->threshold) {
            return this->threshold;
        }
        if (value < -this->threshold) {
            return -this->threshold;
        }

        return value;
    }

    void set_param(int param_id, float value) {
        switch (param_id) {
            case 0: this->gain = value;         return;
            case 1: this->threshold = value;    return;
        }
    }

};

// funky black magic from https://github.com/electro-smith/DaisySP/blob/master/Source/Utility/dsp.h
// appears to be a Pade approximation
inline float soft_clip(float x) {
    if (x < -3) {
        return -1;
    }
    if (x > 3) {
        return 1;
    }

    return x * (27 + x * x) / (27 + 9 * x * x);
}


class SoftClip : public Transform {
    float drive;
    float limit;

    void init() {
        this->drive = 1.0f;
        this->limit = 1.0f;
    }

    float process(float sample) {
        return this->limit = soft_clip(this->drive * sample);
    }

    void set_param(int param_id, float value) {
        switch (param_id) {
            case 0: this->drive = value; return;
            case 1: this->limit = value; return;
        }
    }

};

}
}