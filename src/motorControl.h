/*

    motorControl.h

*/

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

void motorControl(int IRVal);

void initMotors();

void turnLeft();

void turnRight();

void driveStraight();

void creep();

void reverse();

void stop();

void smartControl(int rightTarget, int leftTarget);

#endif