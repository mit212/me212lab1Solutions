// Zack Bright        - zbright _ mit _ edu,  Sept 2015
// Daniel J. Gonzalez - dgonz _ mit _ edu,    Sept 2015
// Peter KT Yu        - peterkty _ mit _ edu, Sept 2016
// Ryan Fish          - fishr _mit_ edu,      Sept 2016


#include "DualMC33926MotorShield.h"

#ifndef HELPER_H
#define HELPER_H

// PI has been defined in arduino

const float wheelRadius = 0.037;  // In meters

// There are two type of motors, Model 26 and Model 53.
// Model 26 is 2000 encoder counts per wheel rev, Model 53 is 1000 counts per wheel rev

// If your motor has a 53 in the part number, comment out the next line
#define GEARBOX_26

#ifdef GEARBOX_26
  const float enc2rev = 2000.0;  // these motors have 2000 counts per rev
  const float gearing = 26.0;
#else  // otherwise gearbox 53 
  const float enc2rev = 1000.0;  // these motors have 1000 counts per rev
  const float gearing = 53.0;
#endif
const float enc2robotvel = (1.0 / enc2rev) * 2 * PI * wheelRadius; 

const float maxMV = 22.2 * 26.94 / gearing * wheelRadius;  // max wheelspeed, note cancelled factors of PI and 1/(PI)


// The variables with extern modifiers are defined in helper.cpp file
// These hold the current encoder count.
extern signed long encoder1count;  //current total encoder ticks since arduino powered on wraps around at 
extern signed long encoder1countPrev;

//Timing variables
extern unsigned long currentTime;
extern unsigned long prevTime;
extern unsigned long startTime;          // Time the arduino finished setup and started looping
extern unsigned long freqTime;
extern unsigned long currentSerialTime;  // current serial message time
extern unsigned long prevSerialTime;     // last time serial messages were dispatched
extern float         dt;                 // time between control loops

//Velocity Control Gains, Motor 1
extern bool velocityControl;    //Boolean to determine first part of the lab
extern const float Kpv1;        //Proportional gain, velocity, motor 1
extern const float Kdv1;        //Derivative gain
extern const float Kiv1;        //Integral gain

//Motor 1 Errors and Command Components
extern float error1;            //Current Motor 1 velocity error
extern float error1Prev;        //previous velocity error
extern float integratedError1;  //previously integrated error
extern int   m1Command;         //Motor 1 voltage command, bounded in -400 to 400
extern float proportionalCommand1;  //proportional component of motor command
extern float derivativeCommand1;    //derivative component
extern float integralCommand1;      //integral component
extern int   currentCommand1;

//Motor Velocities
extern float mV1;          // Estimated motor 1 velocity. (meters/second)
extern float desiredMV1;   // (meters/second)

//Motor Positions
extern float wheelPos1; //meters
extern float desiredWheelPos1; //meters

//Motor Position Errors
extern float wheelPosError1;
extern float wheelPosError1Prev;
extern float integratedWheelPosError1;
extern int wheelProportionalCommand1;
extern int wheelDerivativeCommand1;
extern int wheelIntegralCommand1;

//Position Control Gains, Motor1
extern const float Kpp1;  //Proportional gain, position, motor 1
extern const float Kdp1;  //Derivative gain
extern const float Kip1;  //Integral Gain

//Sine Wave
extern float sinFreq;  // (Hz)

//motor shield object
extern DualMC33926MotorShield md;

//Staff constants
const int   FREQ = 200;
const float PERIOD = 0.005;
const float PERIOD_MICROS = (PERIOD * 1000000.0);
const int   SERIAL_FREQ = 100;  //Should be at least 10 times greater than sin wave frequency
const float SERIAL_PERIOD = 0.01;
const float SERIAL_PERIOD_MICROS = 10000.0;

//Staff functions
void stopIfFault(void);
void DoSerialSend(void);

#endif //HELPER_H
