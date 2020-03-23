#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include "M5StackUpdater.h"
#include <M5Stack.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150
#define SERVOMAX  400


uint8_t servonum = 0;
int pulselen = 0;
void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");
  M5.begin(true, false, true);
  M5.Power.begin();
  pwm.begin();
  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(65, 10);
  M5.Lcd.println("Servo Config");
  M5.Lcd.setCursor(3, 35);
  M5.Lcd.println("Press B for next");
  M5.Lcd.println("A and C to + and -");
  M5.Lcd.setTextColor(RED,BLACK);
  pwm.setPWMFreq(50);
  Wire.begin();if(digitalRead(39)==0){updateFromFS(SD);ESP.restart();} 
  
  //yield();
}


void loop() {
while (servonum<16)
     {
  M5.update();
  if (M5.BtnA.wasReleased()) {
    M5.Lcd.print(pulselen); pulselen+=10;
  } else if (M5.BtnB.wasReleased()) {
    M5.Lcd.print(servonum); servonum++;
  } else if (M5.BtnC.wasReleased()) {
    M5.Lcd.print(pulselen); pulselen-=10;
  } ;
  M5.Lcd.setCursor(0, 0);
  
    
  // update the servos
  pwm.setPWM(servonum, 0, SERVOMIN + pulselen);
  
  
  }
  servonum == 0;
}
