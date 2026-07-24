#pragma once

#include "transform.h"

namespace mono {
namespace distortion {

class HardClip : public Transform {
    float gain;
    float threshold;

    void init() {
        gain = 1.0f;
        threshold = 1.0f;
    }

    float process(float sample) {
        float value = sample * gain;
        
        if (value > threshold) {
            return threshold;
        }
        if (value < -threshold) {
            return -threshold;
        }

        return value;
    }

    void set_param(int param_id, float value) {
        switch (param_id) {
            case 0: gain = value;         return;
            case 1: threshold = value;    return;
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
        drive = 1.0f;
        limit = 1.0f;
    }

    float process(float sample) {
        return limit = soft_clip(drive * sample);
    }

    void set_param(int param_id, float value) {
        switch (param_id) {
            case 0: drive = value; return;
            case 1: limit = value; return;
        }
    }

};

}
}