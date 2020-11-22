#ifndef TEMP_H
#define TEMP_H

#include <OneWire.h> 
#include <DallasTemperature.h>

#define TOLERANCIA 2

extern OneWire oneWire;
extern DallasTemperature sensor;
extern int g_temp_enabled;
extern float g_set_temp;
extern long double g_last_convertion_time;

float Get_Temp(void);
void Set_temp(void);
void Init_DS18B20 (void);
void AlarmHandler(const uint8_t* deviceAddress);
void Get_Temp_Async(void);

#endif