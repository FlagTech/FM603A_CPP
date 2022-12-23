#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <I2Cdev.h>
#include <MPU6050.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
MPU6050 mpu6050;

// setup() 會先被執行且只會執行一次
void setup() {
  lcd.begin(16,2);
  mpu6050.initialize();

  Serial.begin(9600);
}

// loop() 裡面的程式會不斷重複執行
void loop() {
  lcd.clear();
  lcd.print((int(mpu6050.getAccelerationX() * 2.0 / 32.768)));
  lcd.print(",");
  lcd.print((int(mpu6050.getAccelerationY() * 2.0 / 32.768)));
  lcd.print(",");
  lcd.print((int(mpu6050.getAccelerationZ() * 2.0 / 32.768)));
  Serial.print((int(mpu6050.getAccelerationX() * 2.0 / 32.768)));
  Serial.print(",");
  Serial.print((int(mpu6050.getAccelerationY() * 2.0 / 32.768)));
  Serial.print(",");
  Serial.println((int(mpu6050.getAccelerationZ() * 2.0 / 32.768)));
  delay(300);
}
