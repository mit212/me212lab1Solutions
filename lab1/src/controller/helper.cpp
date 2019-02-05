// Zack Bright        - zbright _ mit _ edu,  Sept 2015
// Daniel J. Gonzalez - dgonz _ mit _ edu,    Sept 2015
// Peter KT Yu        - peterkty _ mit _ edu, Sept 2016
// Ryan Fish          - fishr _mit_ edu,      Sept 2016

// See helper.h for additional notes and comments on the purpose of each variable

#include "helper.h"

#include "Arduino.h"

///////////////////////Shared Variables///////////////////////

// These hold the current and previous encoder count.
signed long encoder1count = 0;
signed long encoder1countPrev = 0;

// Timing
unsigned long currentTime = 0;
unsigned long prevTime = 0;
unsigned long startTime = 0;
unsigned long freqTime = 0;
unsigned long currentSerialTime = 0;
unsigned long prevSerialTime = 0;
float         dt = 0;

// Velocity Control Gains, Motor 1
const float Kpv1 = 1000.0;  // around 1000 is good
const float Kdv1 = 0.0;
const float Kiv1 = 0.0;
float error1 = 0.0;
float error1Prev = 0.0;
float integratedError1 = 0;
int m1Command = 0.0; //  From -400 to 400;
float proportionalCommand1 = 0;
float derivativeCommand1 = 0;
float integralCommand1 = 0;
int currentCommand1 = 0;

// Motor Velocities
float mV1 = 0.0;
float desiredMV1 = 0; //  meters/second

// Sine Wave
float sinFreq = 0.5; // (Hz)

///////////////////////Helper Functions///////////////////////  
  
void stopIfFault()
{
    if (md.getFault())
    {
        Serial.println("fault");
        md.setM1Speed(0);
        while(1);
    }
}

// Sending values through serial port to plot on the computer:
void DoSerialSend()
{
    if(micros() - prevSerialTime >= SERIAL_PERIOD_MICROS){
        currentSerialTime = micros();

        Serial.print("#,");
        Serial.print(millis());
        Serial.print(',');
        Serial.print(mV1);
        Serial.print(',');
        Serial.print(desiredMV1);
        Serial.print(',');
        Serial.print(m1Command);
        Serial.println(",#");

        prevSerialTime = currentSerialTime;

        currentSerialTime = micros();
    }
}

