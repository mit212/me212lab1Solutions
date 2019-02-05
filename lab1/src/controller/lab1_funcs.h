/*
Ryan Fish - fishr _mit_ edu
Sept 2016
*/

#ifndef LAB1_FUNCS_H
#define LAB1_FUNCS_H

int openLoopController(void);
void storeOldVals(void);
float motor1_velocity(void);
float proportional_control(void);
float derivative_control(void);
float integral_control(void);
int closedLoopController(void);
int wheelPositionController(void);
void storeOldVals2(void);

#endif //LAB1_FUNCS_H
