#include "./transform.h"
#include "../../constants.h"
#include <cmath>

namespace mono {

/**
 * Wah using SVF 
 * https://www.musicdsp.org/en/latest/Filters/23-state-variable.html
 */ 
class Wah : public Transform {

    float low;
    float band;
    // float notch;

    float q;

    float envelope;
    
    void init() {

        low = 0.0f;
        band = 0.0f;

        q = 0.2;

        envelope = 0;

    }

    float process(float sample) {
        float attack = 0.995;
        float release = 0.999;

        float abs_sample = fabsf(sample);
        if (abs_sample > envelope) {
            envelope = attack * (envelope - abs_sample) + abs_sample;
        } else {
            envelope = release * (envelope - abs_sample) + abs_sample;
        }
        
        float cutoff = 200.0f * exp2f(envelope * 3.5f);
        float f = 2 * sinf(PI * cutoff / SAMPLE_RATE);

        low = low + f * band;
        float high = q * (sample - band) - low;
        band = f * high + band;
        // notch = high + low;

        return band;
    }

    void set_param(int param_id, float value) {
        // TODO: implement
        ;
    }

};

}