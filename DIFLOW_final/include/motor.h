#ifndef MOTOR_H
#define MOTOR_H

extern int g_duty_1;
extern int g_duty_2;
extern int g_duty_3;
extern int g_duty_4;
extern int g_selected_motor;

#define MOTOR1 0
#define MOTOR2 1
#define MOTOR3 2
#define MOTOR4 3
#define DUTY_0 0
#define DUTY_1 (255/5)
#define DUTY_2 ((255/5)*2)
#define DUTY_3 ((255/5)*3)
#define DUTY_4 ((255/5)*4)
#define DUTY_5 ((255/5)*5)

void SetDuty(int motor_num, int duty);

#endif