/*

    pickup.h

*/

#ifndef PICKUP_H
#define PICKUP_H

void initPickup(void);

void pickup(void);

void moveStepper(int duration);

void moveStepperToLimit(int limitSwitch);

void enableMagnet(void);

void disableMagnet(void);

void runStepper(void);

#endif
