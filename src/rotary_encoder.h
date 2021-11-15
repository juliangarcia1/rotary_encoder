#include "Arduino.h"

class Encoder {
    private:
        uint8_t encoderSWisPushed = false;
        uint8_t pinCLK;
        uint8_t pinDT;
        uint8_t pinSW;
    public:
        uint8_t encoderVal = 0;
        uint8_t max_value = 100;
        uint8_t min_value = 0;
        Encoder(uint8_t pinCLK, uint8_t pinDT, uint8_t pinSW);
        void setup(void (*ISR_callback_CLK)(void), 
                   void (*ISR_callback_DT)(void), 
                   void (*ISR_callback_SW)(void));
        uint8_t getEncoderValue(uint8_t last_value, uint8_t value);
        void processEncoderCLK();
        void processEncoderDT();
        void processEncoderSW();

};
