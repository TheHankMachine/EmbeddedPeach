#include "daisy_seed.h"
#include "daisysp.h"
#include "mono/board.h"
#include <cmath>

using namespace daisy;
using namespace daisysp;

DaisySeed hw;
mono::Board board;

void AudioCallback(AudioHandle::InterleavingInputBuffer in, AudioHandle::InterleavingOutputBuffer out, size_t size) {

	for (size_t i = 0; i < size; i += 2) {

		float sample = in[i + 1];

		out[i + 1] = board.process(sample);
	}
}

int main(void)
{
	hw.Configure();
	hw.Init();

	hw.SetAudioBlockSize(32); // number of samples handled per callback
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);

	// board.add<mono::distortion::HardClip>();
	// board.get(0)->set_param(0, 7.0f);
	// board.get(0)->set_param(1, 0.3f);

	// board.add<mono::octaver::Up>();

	// hw.StartAudio(AudioCallback);

	hw.usb_handle.Init(UsbHandle::FS_INTERNAL);
	// hw.usb_handle.SetReceiveCallback(UsbCallback, UsbHandle::FS_INTERNAL);

	int i = 0;

	while (true) {

        hw.SetLed(true);
		
		char buff[512];
		sprintf(buff, "Tick:\t%d\r\n", i);
    	hw.usb_handle.TransmitInternal((uint8_t*)buff, strlen(buff));
		i++;

        System::Delay(100);


        hw.SetLed(false);
        System::Delay(1'900);

	}
}

// #include "daisy_seed.h"

// // Use the daisy namespace to prevent having to type
// // daisy:: before all libdaisy functions
// using namespace daisy;

// // Declare a DaisySeed object called hardware
// DaisySeed hardware;

// int main(void)
// {
//     // Declare a variable to store the state we want to set for the LED.
//     bool led_state;
//     led_state = true;

//     // Configure and Initialize the Daisy Seed
//     // These are separate to allow reconfiguration of any of the internal
//     // components before initialization.
//     hardware.Configure();
//     hardware.Init();

//     // Loop forever
//     for(;;)
//     {
//         // Set the onboard LED
//         hardware.SetLed(led_state);

//         // Toggle the LED state for the next time around.
//         led_state = !led_state;

//         // Wait 500ms
//         System::Delay(500);
//     }
// }
