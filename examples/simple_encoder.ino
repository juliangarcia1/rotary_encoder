#include <rotary_encoder.h>
//TODO Test, cause it is not tested yet

// Rotary encoder using ESP32 Dev Module with esp-wromm-32
#define pinCLK 21
#define pinDT  22
#define pinSW  34
#endif

Encoder encoder(pinCLK, pinDT, pinSW);

void IRAM_ATTR readEncoderCLK() {
  (&encoder)->processEncoderCLK();
}
void IRAM_ATTR readEncoderDT() {
  (&encoder)->processEncoderDT();
}
void IRAM_ATTR readEncoderSW() {
  (&encoder)->processEncoderSW();
}

void setup() {
    Serial.begin(115200);

    delay(1000);

    // This can be set in the IDE no need for ext library
    // system_update_cpu_freq(160);

    Serial.println("\n\nSimple Encoder example");

    encoder.setup(readEncoderCLK, readEncoderDT, readEncoderSW);
    // Every time that the rotary encoder rotates a message is printed
}

void loop() {

}
