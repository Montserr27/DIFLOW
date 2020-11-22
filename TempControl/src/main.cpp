#include <Arduino.h>
#include <temp.h>
#include <main.h>

static void InitPins(void);

static void InitPins(void)
{
  pinMode(BOTON_MODE, INPUT);
  pinMode(BOTON_SET, INPUT);
  pinMode(BOTON_PLUS, INPUT);
  pinMode(BOTON_MINUS, INPUT);
  pinMode(MOTOR1, OUTPUT);
  pinMode(MOTOR2, OUTPUT);
  pinMode(MOTOR3, OUTPUT);
  pinMode(MOTOR4, OUTPUT);
  pinMode(RESISTENCIA, OUTPUT);
  digitalWrite(MOTOR1, LOW);
  digitalWrite(MOTOR2, LOW);
  digitalWrite(MOTOR3, LOW);
  digitalWrite(MOTOR4, LOW);
  digitalWrite(RESISTENCIA, LOW);
}

void setup(void) 
{
  InitPins();
  Init_DS18B20();
  Serial.begin(9600);
  g_set_temp = 35;
  Set_temp();
  Serial.println("CLEARDATA");
  Serial.println("LABEL,Computer Time,Time (Milli Sec.),Temp");
  Serial.println("RESETTIMER");
}

void loop(void) 
{
  Get_Temp_Async();

  if(sensor.hasAlarm())
  {
    sensor.processAlarms();
  }
  else
  {
    digitalWrite(RESISTENCIA, LOW);
  }
}