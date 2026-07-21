#pragma once 

#include "transform.h"

namespace mono {
namespace octaver {

class Up : public Transform {

    float y;
    float wetness;
    float dry_past;
    float wet_past;

    void init() {
        this->wetness = 0.5;
        this->wet_past = 0.0f;
        this->dry_past = 0.0f;
        this->y = 0.0f;
    }

    float process(float sample) {

        this->dry_past = this->dry_past + 0.5 * (sample - this->dry_past);

        float value = fabsf(this->dry_past);

        this->y = value - this->wet_past + this->y * 0.9995f;

        this->wet_past = value;

        return this->y * this->wetness + sample * (1.0f - this->wetness);
    }

    void set_param(int param_id, float value) {
        // switch (param_id) {
        //     case 0: this->gain = value;         return;
        //     case 1: this->threshold = value;    return;
        // }
    }

};

}
}