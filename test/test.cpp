#include <vector>
#include <cstdint>
#include "../mono/board.h"


mono::Board board;


extern "C" {
    void test(float* buffer, int length) {

        board.add<mono::Wah>();
        // board.add<mono::distortion::HardClip>();
        // board.get(1)->set_param(0, 9.0f);
    	// board.get(1)->set_param(1, 0.3f);

        for (int i = 0; i < length; ++i) {
            buffer[i] = board.process(buffer[i]);
        }
    }
}