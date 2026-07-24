import matplotlib.pyplot as plt
import wave
import os
import ctypes
import numpy as np


SAMPLE_RATE = 48000
DTYPE = np.int32
DTYPE_BITWIDTH = (len(bin(np.iinfo(DTYPE).max)[2:]) + 1) // 8 #length of the binary string (plus one for parity bit) / 8
TEST_DIR = os.path.dirname(__file__)
AUDIO_OUT_DIR = os.path.join(TEST_DIR, 'audio/out')


dll = ctypes.cdll.LoadLibrary(os.path.join(TEST_DIR, "build/test.dll"))


def convert_file(path: str) -> str:
    # out_path = path.replace(".mp3", ".wav")
    out_path = os.path.join(AUDIO_OUT_DIR, "converted.wav")

    os.system(f"yes | ffmpeg -i {path} -acodec pcm_s32le -ar {SAMPLE_RATE} -ac 1 {out_path}")

    return out_path


def get_samples(path):
    # if path.endswith(".mp3"):
    path = convert_file(path)

    wav = wave.open(path, 'r')
    samples = np.frombuffer(wav.readframes(wav.getnframes()), DTYPE) / np.iinfo(DTYPE).max

    return samples


def test_output(sample):
    length = len(samples)
    buffer = (ctypes.c_float * length)(*samples)

    dll.test(buffer, length)

    return buffer


def plot_samples(samples):
    n_samples = len(samples)
    time = np.linspace(0, n_samples / SAMPLE_RATE, n_samples)

    plt.plot(time, samples)

    plt.xlabel("time (s)")
    plt.ylabel("value")

    plt.show()


def save_samples(samples, out_path = os.path.join(AUDIO_OUT_DIR, "out.wav")):
    wav = wave.open(out_path, "w")
    
    wav.setnchannels(1)
    wav.setsampwidth(DTYPE_BITWIDTH)
    wav.setframerate(SAMPLE_RATE)

    samples = np.round(np.array(samples) * np.iinfo(DTYPE).max).astype(DTYPE)

    wav.writeframes(samples.tobytes())




if __name__ == "__main__":
    samples = get_samples("./audio/fretless.mp3")
    samples = test_output(samples)

    save_samples(samples)

    # plot_samples(samples)
