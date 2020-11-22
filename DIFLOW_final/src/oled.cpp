#include <oled.h>
#include <main.h>
#include <temp.h>
#include <button.h>
#include <motor.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

static void Check_Motores(void);
static void Check_Res(void);
static void DrawLogo(void);
static void DrawTemp(void);
static void DrawMotor(int motor_num, int lleno);
static void DrawTermometro(int lleno);
static void DrawTermometroGrande(void);
static void DisplayTemp(void);
static void DisplayMotors(void);
static void DisplaySpeed(void);

void Init_Display(void)
{
    if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) 
    {
        Serial.println(F("SSD1306 no encontrada"));
        for(;;); //Loop infinito
    }
    Serial.println("OLED inicializada");
    display.clearDisplay();
    display.display();
}

void DrawLogo(void)
{
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(20,30);
    display.println(F("Paulo"));
    display.setCursor(20,50);
    display.println(F("Soution"));
}

void DrawMotor(int motor_num, int lleno)
{
    int rect_size = 15;
    int space = 5;
    if(lleno) display.fillRect((motor_num*rect_size)+(motor_num*space),0,rect_size,rect_size,SSD1306_WHITE);
    else display.drawRect((motor_num*rect_size)+(motor_num*space),0,rect_size,rect_size,SSD1306_WHITE);
}

void Check_Motores(void)
{
    if(g_duty_1 > 0) DrawMotor(0,1);
    else DrawMotor(0,0);
    if(g_duty_2 > 0) DrawMotor(1,1);
    else DrawMotor(1,0);
    if(g_duty_3 > 0) DrawMotor(2,1);
    else DrawMotor(2,0);
    if(g_duty_4 > 0) DrawMotor(3,1);
    else DrawMotor(3,0);
}

void DrawTermometro(int lleno)
{
    if(lleno)
    {
        display.fillCircle(105,20,4,SSD1306_WHITE);
        display.fillRoundRect(103,0,5,20,2,SSD1306_WHITE);
    }
    else
    {
        display.drawCircle(105,20,4,SSD1306_WHITE);
        display.drawRoundRect(103,0,5,20,2,SSD1306_WHITE);
        display.drawPixel(105,19,SSD1306_BLACK);
        display.drawPixel(106,19,SSD1306_BLACK);
        display.drawPixel(104,19,SSD1306_BLACK);
        display.drawPixel(107,18,SSD1306_BLACK);
        display.drawPixel(103,18,SSD1306_BLACK);
    }
}

void Check_Res(void)
{
    if(digitalRead(RESISTENCIA)) DrawTermometro(1);
    else DrawTermometro(0); 
}

void DrawTemp(void)
{
    double temp = sensor.getTempCByIndex(0);
    display.setTextSize(1);
    display.setCursor(90,30);
    Serial.println(temp);
    if(temp > 0)
    {
        display.print(temp, 1);
        display.setCursor(120,30);
        display.println(F("C"));
        display.drawCircle(115,31,2,SSD1306_WHITE);
    }
    else
    {
        display.println(F(" Err"));
    }
}



void DrawTermometroGrande(void)
{
    display.drawCircle(100,50,12,SSD1306_WHITE);
    display.drawRoundRect(94,4,13,40,5,SSD1306_WHITE);
    display.drawLine(97,43,103,43,SSD1306_BLACK);
    display.drawPixel(96,42,SSD1306_BLACK);
    display.drawPixel(104,42,SSD1306_BLACK);
    display.drawPixel(95,41,SSD1306_BLACK);
    display.drawPixel(105,41,SSD1306_BLACK);
}

void DisplayTemp(void)
{
    display.setTextSize(2);
    display.setCursor(20,30);
    if(g_set_temp != 0) display.print(g_set_temp);
    else
    {
        float temp = sensor.getTempCByIndex(0);
        if(temp > 0) display.print(temp,1);
        else display.println(F("Err"));
    }    
}

void DisplayMotors(void)
{
    int size = 28;
    int space = ((SCREEN_WIDTH-2)-(size*4))/3;
    display.drawRect(1, (SCREEN_HEIGHT/2) - (size/2),size,size,SSD1306_WHITE);
    display.drawRect(33, (SCREEN_HEIGHT/2) - (size/2),size,size,SSD1306_WHITE);
    display.drawRect(65, (SCREEN_HEIGHT/2) - (size/2),size,size,SSD1306_WHITE);
    display.drawRect(97, (SCREEN_HEIGHT/2) - (size/2),size,size,SSD1306_WHITE);
    display.drawRect((g_selected_motor*size)+((g_selected_motor)*space),((SCREEN_HEIGHT/2) - (size/2))-1, size+2,size+2,SSD1306_WHITE);
}

void DisplaySpeed(void)
{
    display.setTextSize(3);
    display.setCursor(6,21);
    display.println(g_duty_1);
    display.setCursor(40,21);
    display.println(g_duty_2);
    display.setCursor(72,21);
    display.println(g_duty_3);
    display.setCursor(105,21);
    display.println(g_duty_4);
}

void DrawConfitmationLine(void)
{
    for(int i = 0; i< 2; i++)
    {
        display.drawLine(18,50,68,50,SSD1306_WHITE);
        display.display();
        delay(300);
        display.drawLine(18,50,68,50,SSD1306_BLACK);
        display.display();
        delay(300);
    }
}
/**********************************************************
*                      MENUS INICIA                      *
***********************************************************/
void UploadScreen(void)
{
    display.clearDisplay();
    if(g_home == HOME_MENU) DrawHome();
    if(g_home == TEMP_MENU) DrawTempMenu();
    if(g_home == MOTOR_MENU) DrawMotorMenu();
}

void DrawHome(void)
{
    display.clearDisplay();
    Check_Motores();
    Check_Res();
    DrawLogo();
    DrawTemp();
    display.display();
}

void DrawTempMenu(void)
{
    display.clearDisplay();
    DisplayTemp();
    DrawTermometroGrande();
    display.display();
}

void DrawMotorMenu(void)
{
    display.clearDisplay();
    DisplayMotors();
    DisplaySpeed();
    display.display();
}
/**********************************************************
*                     MENUS TERMINA                      *
***********************************************************/
