/* Get tilt angles on X and Y, and rotation angle on Z
 * Angles are given in degrees
 * 
 * License: MIT
 */

#include "Wire.h"
#include <MPU6050_light.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

MPU6050 mpu(Wire);
unsigned long timer = 0;
unsigned long timer2 = 0;


void setup() {
  Serial.begin(115200);
  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Calculating...");
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  

  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
  
}
int x ,y ,z ;
void loop() {
  mpu.update();
  if(millis()-timer2 >250) { 
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("X: ");
    lcd.print(x);
    lcd.setCursor(8,0);

    lcd.print("  Y: ");
    lcd.print(y);
    lcd.setCursor(0,1);
    lcd.print("Z: ");
    lcd.print(z);
    
    timer2 =millis();
  }
  if((millis()-timer)>100){ // print data every 10ms
  x = mpu.getAngleX();
  y = mpu.getAngleY();
  z = mpu.getAngleZ();
  Serial.print(x);
  Serial.print("/");
  Serial.print(y);
  Serial.print("/");
  Serial.println(z);
  timer = millis();  
  }
}
