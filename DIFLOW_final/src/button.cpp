#include <button.h>
#include <main.h>
#include <temp.h>
#include <oled.h>
#include <motor.h>

int g_button_num = 0;
int g_button_reading = 0;
int g_home = 0;
int g_set_offset = 0;

void CheckButtons(void)
{
    if(!digitalRead(BOTON_MODE))
    {
        delay(DEBOUCE_DELAY);
        while(!digitalRead(BOTON_MODE));
        g_button_num = 1;
        g_button_reading = 1;
    }
    else if(!digitalRead(BOTON_SET))
    {
        delay(DEBOUCE_DELAY);
        while(!digitalRead(BOTON_SET));
        g_button_num = 2;
        g_button_reading = 1;
    }
    else if(!digitalRead(BOTON_PLUS))
    {
        delay(DEBOUCE_DELAY);
        while(!digitalRead(BOTON_PLUS));
        g_button_num = 3;
        g_button_reading = 1;
    }
    else if(!digitalRead(BOTON_MINUS))
    {
        delay(DEBOUCE_DELAY);
        while(!digitalRead(BOTON_MINUS));
        g_button_num = 4;
        g_button_reading = 1;
    }
    else
    {
        g_button_reading = 0;
        g_button_num = 0;
    }
}

void AccionBotones(int estado_boton)
{
    switch (estado_boton)
    {
    case 1://mode
        if(g_home == HOME_MENU)
        {
            g_home = TEMP_MENU;
            DrawTempMenu();
        }
        else if(g_home == TEMP_MENU)
        {
            g_home = MOTOR_MENU;
            DrawMotorMenu();
        }
        else if(g_home == MOTOR_MENU)
        {
            g_home = HOME_MENU;
            DrawHome();
        }
        break;
    case 2: //set
        if(g_home == TEMP_MENU)
        {
            if(g_set_temp <= 0) g_set_temp = sensor.getTempCByIndex(0);
            if(g_set_temp > 0) Set_temp();
            DrawConfitmationLine();
            g_home = HOME_MENU;
            DrawHome();
        }
        else if(g_home == MOTOR_MENU)
        {
            if(g_selected_motor == MOTOR1)
            {
                SetDuty(MOTOR1, g_duty_1);
                g_selected_motor = MOTOR2;
            }
            else if(g_selected_motor == MOTOR2)
            {
                SetDuty(MOTOR2, g_duty_2);
                g_selected_motor = MOTOR3;
            }
            else if(g_selected_motor == MOTOR3)
            {
                SetDuty(MOTOR3, g_duty_3);
                g_selected_motor = MOTOR4;
            }
            else if(g_selected_motor == MOTOR4)
            {
                SetDuty(MOTOR4, g_duty_4);
                g_selected_motor = MOTOR1;
            }
        }
        break;
    case 3: //plus
        if(g_home == TEMP_MENU)
        {
            if(g_set_temp == 0) g_set_temp = 30;
            else g_set_temp += 0.5;
        }
        else if(g_home == MOTOR_MENU)
        {
            if(g_selected_motor == MOTOR1) g_duty_1++;
            else if(g_selected_motor == MOTOR2) g_duty_2++;
            else if(g_selected_motor == MOTOR3) g_duty_3++;
            else if(g_selected_motor == MOTOR4) g_duty_4++;
            if(g_duty_1 >= 6)g_duty_1 = 0;
            if(g_duty_2 >= 6)g_duty_2 = 0;
            if(g_duty_3 >= 6)g_duty_3 = 0;
            if(g_duty_4 >= 6)g_duty_4 = 0;
        }
        break;
    case 4: //minus
        if(g_home == TEMP_MENU)
        {
            if(g_set_temp == 0) g_set_temp = 40;
            else g_set_temp -= 0.5;
        }
        else if(g_home == MOTOR_MENU)
        {
            if(g_selected_motor == MOTOR1) g_duty_1--;
            else if(g_selected_motor == MOTOR2) g_duty_2--;
            else if(g_selected_motor == MOTOR3) g_duty_3--;
            else if(g_selected_motor == MOTOR4) g_duty_4--;
            if(g_duty_1 <= 0)g_duty_1 = 5;
            if(g_duty_2 <= 0)g_duty_2 = 5;
            if(g_duty_3 <= 0)g_duty_3 = 5;
            if(g_duty_4 <= 0)g_duty_4 = 5;
        }
        break;
    default:
        break;
    }
}
