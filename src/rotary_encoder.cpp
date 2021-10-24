#include "rotary_encoder.h"


Encoder::Encoder(uint8_t pinCLK, uint8_t pinDT, uint8_t pinSW, 
                 void (*ISR_callback_CLK)(void), 
                 void (*ISR_callback_DT)(void), 
                 void (*ISR_callback_SW)(void))
{
    this->pinCLK = pinCLK;
    this->pinDT = pinDT;
    this->pinSW = pinSW;
    pinMode(pinCLK, INPUT);
    pinMode(pinDT, INPUT);
    pinMode(pinSW, INPUT);

    attachInterrupt(digitalPinToInterrupt(this->pinCLK), ISR_callback_CLK, CHANGE);
    attachInterrupt(digitalPinToInterrupt(this->pinDT), ISR_callback_DT, CHANGE);
    attachInterrupt(digitalPinToInterrupt(this->pinSW), ISR_callback_SW, CHANGE);

    // Serial.begin(9600);
}
uint8_t Encoder::getEncoderValue(uint8_t value) { 
    if(value >= this->max_value) {
        value = this->max_value;
    }
    if(value <= this->min_value) {
        value = this->min_value;
    }
    return value;
}

void Encoder::processEncoderCLK()
{
    // look for a low-to-high on channel A
    if (digitalRead(this->pinCLK) == HIGH)
    {
        // check channel B to see which way encoder is turning
        if (digitalRead(this->pinDT) == LOW)
        {
            this->encoderVal += 1; // CW
        }
        else
        {
            this->encoderVal -= 1; // CCW
        }
    }
    else // must be a high-to-low edge on channel A
    {
        // check channel B to see which way encoder is turning
        if (digitalRead(this->pinDT) == HIGH)
        {
            this->encoderVal += 1; // CW
        }
        else
        {
            this->encoderVal -= 1; // CCW
        }
    }
    
    this->encoderVal = this->getEncoderValue(encoderVal);

    // for debugging purposes only
    // Serial.println(encoderVal, DEC);
}


//porocess encoder´s pinB
void Encoder::processEncoderDT()
{
    if (digitalRead(this->pinDT) == HIGH)
    {
        if (digitalRead(this->pinCLK) == HIGH)
        {
            this->encoderVal += 1; // CW
        }
        else
        {
            this->encoderVal -= 1; // CCW
        }
    }
    else
    { 
        if (digitalRead(this->pinCLK) == LOW)
        {
            this->encoderVal += 1; // CW
        }
        else
        {
            this->encoderVal -= 1; // CCW
        }
    }
}
void Encoder::processEncoderSW(){
    if( digitalRead(this->pinSW) == HIGH) {
        // Indicates it was pushed
        this->encoderSWisPushed = true;
        //Do something with it
    } else {
        //Indicates it was released
        this->encoderSWisPushed = false;
        // Do something with it
    }
}