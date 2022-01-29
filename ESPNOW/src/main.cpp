#include <Arduino.h>
//ss
#include <Wire.h>
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
#include <display.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "timerSetups.h"
#include "algos.h"


bool loop_start_flag = false;
TaskHandle_t CoreZEROTasks;
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite logtxt1 = TFT_eSprite(&tft); // Sprite object stext1


BLEServer *pServer;
BLEService *pService;
BLECharacteristic *pCharacteristic;

int interruptCounter_last = 0;
extern volatile int interruptCounter;

long irValue, irArray[240];
float irArray_float[2500], irMax = 0, irmin = 1000000;
int dataCounter = 0;

void coreZEROTasks_code( void * pvParameters );

void setup()
{
  display_init();
  display_log_init();   display_log_print("Initialising...");
 
  delay(100); Serial.begin(115200);   display_log_print("Serial Debug connect!");
  logtxt1.drawNumber(getCpuFrequencyMhz(), 71, 240, 2);
  delay(300); display_log_print("CPU Freq.:     MHz");


 
  xTaskCreatePinnedToCore(
                    coreZEROTasks_code,      /* Task function. */
                    "Task1",        /* name of task. */
                    10000,          /* Stack size of task */
                    NULL,           /* parameter of the task */
                    1,              /* priority of the task */
                    &CoreZEROTasks, /* Task handle to keep track of created task */
                    0);             /* pin task to core 0 */                  
  delay(500); 

  delay(200); display_log_print("2nd Core setup!");
  delay(100); timer_init(); display_log_print("Timers connected!");

  // tft.setCursor(0, 0);
  // tft.setTextColor(TFT_WHITE, TFT_BLACK);
  // tft.print("No Finger    ");
}

void coreZEROTasks_code( void * pvParameters ){
 

  for(;;){
    // Serial.print("Task1 running on core ");  Serial.println(xPortGetCoreID());
    Serial.println(irValue); 
    delay(4);
  } 
}

// loop will be excuted on core1
void loop()
{
 
//tft.pushImage(0,0, 240, 135, info);  
// irValue = PPG_MAX_Sensor.getIR();
//Serial.println(irValue); //Send raw data to plotter
delay(1000);
}
