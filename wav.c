#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

struct WAV {
    char riff[4];
    int32_t file_length;
    char wave[4];
    char fmt[4];
    int32_t chunk_size;
    int16_t format_tag;
    int16_t num_channels;
    int32_t sample_rate;
    int32_t bytes_per_second;
    int16_t bytes_per_sample;
    int16_t bits_per_sample;
    char data[4];
    int32_t data_length;
};

int main(void)
{
    struct WAV wav;
    const int sample_rate = 8000;

    strncpy(wav.riff, "RIFF", 4);
    strncpy(wav.wave, "WAVE", 4);
    strncpy(wav.fmt, "fmt", 4);
    strncpy(wav.data, "data", 4);

    wav.chunk_size = 16;
    wav.format_tag = 1;
    wav.num_channels = 1;
    wav.sample_rate = sample_rate;
    wav.bits_per_sample = 16;
    wav.bytes_per_sample = (wav.bits_per_sample / 8) * wav.num_channels;
    wav.bytes_per_second = wav.sample_rate * wav.bytes_per_sample;

    const int duration_seconds = 10;
    const int buffer_size = wav.sample_rate * duration_seconds;

    wav.data_length = buffer_size * wav.bytes_per_sample;
    wav.file_length = wav.data_length + 44;

    short int buffer[buffer_size] = {};

    for (int i = 0; i < buffer_size; i++) {
        buffer[i] = (short int)(cos((2 * M_PI * 256.0 * i) / sample_rate) * 1000);
    }

    FILE *fp = fopen("test.wav", "w");
    fwrite(&wav, 1, sizeof(wav), fp);
    fwrite(buffer, 2, buffer_size, fp);

    fclose(fp);

    return 0;
}
