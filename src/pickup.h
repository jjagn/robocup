/*

    pickup.h

*/

#ifndef PICKUP_H
#define PICKUP_H

void initPickup(void);

void pickup(int* state);

void moveStepper(unsigned long target);

void moveStepperToLimit(int limitSwitch);

void enableMagnet(void);

void disableMagnet(void);

void runStepper(void);

void cycle(void);

bool zero(int* state);

#endif
