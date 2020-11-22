#ifndef BUTTON_H
#define BUTTON_H

#include <main.h>

#define DEBOUCE_DELAY 70
#define HOME_MENU 0
#define TEMP_MENU 1
#define MOTOR_MENU 2

extern int g_home;
extern int g_button_num;
extern int g_button_reading;
extern int g_set_offset;
void CheckButtons(void);
void AccionBotones(int estado_boton);

#endif