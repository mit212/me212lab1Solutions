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
bool velocityControl = true;
const float Kpv1 = 2500.0;  // around 1000 is good for a start
const float Kdv1 = 0.00;     // Keep this value less than 10
const float Kiv1 = 200.0;   // around 20 is good for a start
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

//Motor Positions
float wheelPos1 = 0.0; //meters
float desiredWheelPos1 = 0.0; //meters

//Motor Position Errors
float wheelPosError1 = 0.0;
float wheelPosError1Prev = 0.0;
float integratedWheelPosError1 = 0.0;
int wheelProportionalCommand1 = 0;
int wheelDerivativeCommand1 = 0;
int wheelIntegralCommand1 = 0;

//Position Control Gains, Motor1
const float Kpp1 = 2000;  //around 500 is a good start.
const float Kdp1 = 0.0;//1200.0;  // try 0 and 1000.
const float Kip1 = 0.0;//1400.0;  // around 5 is a good start. do not exceed 400.
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
      if(velocityControl){
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
      else{
        currentSerialTime = micros();

        Serial.print("#,");
        Serial.print(millis());
        Serial.print(',');
        Serial.print(wheelPos1);
        Serial.print(',');
        Serial.print(desiredWheelPos1);
        Serial.print(',');
        Serial.print(m1Command);
        Serial.println(",#");

        prevSerialTime = currentSerialTime;

        currentSerialTime = micros();
      }
    }
}

