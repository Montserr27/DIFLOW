#include <Arduino.h>
#include <temp.h>
#include <main.h>
#include <button.h>
#include <oled.h>

static void InitPins(void);

static void InitPins(void)
{
  pinMode(BOTON_MODE, INPUT);
  pinMode(BOTON_SET, INPUT);
  pinMode(BOTON_PLUS, INPUT);
  pinMode(BOTON_MINUS, INPUT);
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(MOTOR_PIN3, OUTPUT);
  pinMode(MOTOR_PIN4, OUTPUT);
  pinMode(RESISTENCIA, OUTPUT);
  digitalWrite(MOTOR_PIN1, LOW);
  digitalWrite(MOTOR_PIN2, LOW);
  digitalWrite(MOTOR_PIN3, LOW);
  digitalWrite(MOTOR_PIN4, LOW);
  digitalWrite(RESISTENCIA, LOW);
}

void setup(void) 
{
  InitPins();
  Init_DS18B20();
  Serial.begin(9600);
  Init_Display();
  DrawHome();
  
}

void loop(void) 
{
  ProcessTemp();
  CheckButtons();
  UploadScreen();
  if(g_button_reading)
  {
    AccionBotones(g_button_num);
  }
}