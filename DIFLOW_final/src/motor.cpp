#include <motor.h>
#include <main.h>

int g_duty_1 = DUTY_0;
int g_duty_2 = DUTY_0;
int g_duty_3 = DUTY_0;
int g_duty_4 = DUTY_0;
int g_selected_motor = MOTOR1;

void SetDuty(int motor_num, int duty)
{
    if(motor_num == MOTOR1)analogWrite(MOTOR_PIN1, duty);
    else if(motor_num == MOTOR2)analogWrite(MOTOR_PIN2, duty);
    else if(motor_num == MOTOR3)analogWrite(MOTOR_PIN3, duty);
    else if(motor_num == MOTOR4)analogWrite(MOTOR_PIN4, duty);
}
