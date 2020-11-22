#ifndef OLED_H
#define OLED_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <main.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1
extern Adafruit_SSD1306 display;
extern int g_blink;

#define OLED_ADDRESS 0x3C

void DrawHome(void);
void Init_Display(void);
void UploadScreen(void);
void DrawTempMenu(void);
void DrawMotorMenu(void);
void DrawConfitmationLine(void);
#endif