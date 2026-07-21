#pragma once

#include <variant>

namespace mono {

class Transform {
public:
    virtual void init() = 0;
    virtual void set_param(int param_id, float value) = 0;
    virtual float process(float sample) = 0;
};

}