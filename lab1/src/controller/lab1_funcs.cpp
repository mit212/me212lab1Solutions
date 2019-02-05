// Peter KT Yu        - peterkty _ mit _ edu, Sept 2016
// Ryan Fish          - fishr _mit_ edu,      Sept 2016

#include "lab1_funcs.h"
#include "helper.h"

int openLoopController()
{
    // TODO:  Replace this with a calculated open loop motor command
    // e.g.  m1Command = desiredMV1 * some_factor;
    // remember the PWM limit is [-400,400]!

    // Fix this line
    m1Command = desiredMV1 * 400/maxMV;

    return m1Command;
}

void storeOldVals()
{    
    prevTime = currentTime;

    // TODO: Store the old encoder values so you can take their derivative
    //   relevant variables:
    //   encoder1count
    //   encoder1countPrev
    encoder1countPrev = encoder1count;

    // TODO: Store the old error values so you can take their derivative
    //   error1
    //   error1Prev
    error1Prev = error1;
}

float motor1_velocity()
{

    // TODO: Use the encoder count values and dt to determine motor1 velocity
    // relevant variables:
    //   encoder1count
    //   encoder1countPrev
    //   dt

    // Fix this line and uncomment it
    mV1 = (encoder1count - encoder1countPrev)/dt * enc2robotvel;

    return mV1;
}

float proportional_control()
{
    // TODO: Use the desired velocity and actual velocity to calculate the velocity error
    // relevant variables:
    //   mV1
    //   desiredMV1
    //   error1

    // Fix this line and uncomment it
    error1 = desiredMV1 - mV1;

    proportionalCommand1 = error1 * Kpv1;
    return proportionalCommand1;
}

int closedLoopController()
{
    // TODO: Sum your various controls here 
    // e.g. proportional_control() + derivative_control() + integral_control()
    m1Command = proportional_control() + integral_control() + derivative_control();
    return m1Command;
}

float derivative_control()
{
    // TODO: Use the old velocity value and the new one to determine the derivative of the error term
    // relevant variables:
    //  error1
    //  error1Prev
    //  dt
    //  Kdv1
    
    // Fix this line and uncomment it
    derivativeCommand1 = Kdv1*(error1 - error1Prev)/dt;
    return derivativeCommand1;
}

float integral_control()
{
    //TODO: Use the previously integrated error and the current error
    //to calculate the current error integral
    //relevant variables:
    //  error1
    //  integratedError1
    //  dt
    //  Kiv1

    // Fix this line and uncomment it
    integratedError1 = integratedError1 + error1*dt;
    integralCommand1 = Kiv1 * integratedError1;
    if(integralCommand1 > 200){
      integralCommand1 = 200;
    }
    else if(integralCommand1 < -200){
      integralCommand1 = -200;
    }
    return integralCommand1;
}


float wheelProportional_control()
{
    //TODO: Use the previously integrated error and the current error
    //to calculate the current error integral
    //relevant variables:
    //  wheelPosError1
    //  desiredWheelPos
    //  wheelPos
    //  Kpp1
  
    wheelPosError1 = desiredWheelPos1 - wheelPos1;

    //  Fix this line and uncomment it
    wheelProportionalCommand1 = Kpp1*wheelPosError1;
    return wheelProportionalCommand1;
    
}

float wheelDerivative_control()
{
    //TODO: Use the previously integrated error and the current error
    //to calculate the current error integral
    //relevant variables:
    //  wheelPosError1
    //  wheelPosError1Prev
    //  dt
    //  Kdp1
    
    // Fix this line and uncomment it
    wheelDerivativeCommand1 = Kdp1*(wheelPosError1 - wheelPosError1Prev)/dt;
    return wheelDerivativeCommand1;
}

float wheelIntegral_control()
{
    //TODO: Use the previously integrated error and the current error
    //to calculate the current error integral
    //relevant variables:
    //  wheelPosError1
    //  integratedWheelPosError1;
    //  dt
    //  Kip1

    // Fix these two lines and uncomment it
    integratedWheelPosError1 = integratedWheelPosError1 + wheelPosError1*dt;
    wheelIntegralCommand1 = Kip1*integratedWheelPosError1;
    if(wheelIntegralCommand1 > 200){
      wheelIntegralCommand1 = 200;
    }
    if(wheelIntegralCommand1 < -200){
      wheelIntegralCommand1 = -200;
    }
    return wheelIntegralCommand1;
  
}

int wheelPositionController()
{

    // TODO: Sum your various controls here 
    // e.g. wheelProportional_control() + wheelIntegral_control() + wheelDerivative_control();
    m1Command = wheelProportional_control() + wheelIntegral_control() + wheelDerivative_control();
    return m1Command;
}

void storeOldVals2()
{    
    prevTime = currentTime;

    //Store the old encoder values so you can take their derivative
    //   relevant variables:
    //   encoder1count
    //   encoder1countPrev
    encoder1countPrev = encoder1count;
    wheelPos1 = encoder1count*enc2robotvel;

    // Store the old error values so you can take their derivative
    //   error1
    //   error1Prev
    error1Prev = error1;
    wheelPosError1Prev = wheelPosError1;
}
