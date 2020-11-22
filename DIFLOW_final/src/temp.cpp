#include <temp.h>
#include <main.h>

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire);
DeviceAddress InsideAddress, OutsideAddress;

float g_set_temp = 0;
long double g_last_convertion_time = 0;
int g_temp_enabled = 0;

void Init_DS18B20 (void)
{
    sensor.begin();
    sensor.getAddress(InsideAddress, 0);
    sensor.getAddress(OutsideAddress, 1);
    sensor.setWaitForConversion(false); //Hace la función de requestTemperatures asíncrona
    sensor.setAlarmHandler(&AlarmHandler);
}


void AlarmHandler(const uint8_t* deviceAddress)
{
    float temp = sensor.getTempCByIndex(0);
    Serial.print("Alarm triggered \n Temp: ");
    Serial.println(temp);
    Serial.print("Alarm set between: ");
    Serial.print(sensor.getHighAlarmTemp(deviceAddress));
    Serial.print("and :");
    Serial.println(sensor.getLowAlarmTemp(deviceAddress));
    if( temp < (sensor.getHighAlarmTemp(deviceAddress)-TOLERANCIA/2))
    {
        digitalWrite(RESISTENCIA, HIGH);
    }
    else if( temp > sensor.getLowAlarmTemp(deviceAddress))
    {
        digitalWrite(RESISTENCIA, LOW);
    }
}

float Get_Temp_Sync(void)
{
    sensor.requestTemperatures();
    float temp = sensor.getTempCByIndex(0);
    return temp;
}

void Get_Temp_Async(void)
{
    if((millis()-g_last_convertion_time) >= 750)
    {
        sensor.requestTemperatures();
        g_last_convertion_time = millis();
    }
}

void Set_temp(void)
{
    sensor.setHighAlarmTemp(InsideAddress, g_set_temp+(TOLERANCIA/2)+1);
    sensor.setLowAlarmTemp(InsideAddress, g_set_temp-(TOLERANCIA/2));
    sensor.setHighAlarmTemp(OutsideAddress, g_set_temp+(TOLERANCIA/2));
    sensor.setLowAlarmTemp(OutsideAddress, g_set_temp-(TOLERANCIA/2)-1);
    g_temp_enabled = 1;
}

void ProcessTemp(void)
{
    Get_Temp_Async();
    if(g_temp_enabled)
    {
        if(sensor.hasAlarm())
        {
            sensor.processAlarms();
        }
        else
        {
            digitalWrite(RESISTENCIA, LOW);
        }
    }
}