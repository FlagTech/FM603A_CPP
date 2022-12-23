#include <dht11.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// 建立物件
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
dht11 sensor;

void setup() {
  lcd.begin(16,2); // 啟用 LCD
}

void loop() {
  lcd.home();
  if(sensor.read(2) == DHTLIB_OK) {     // 如果成功讀取
    lcd.print(sensor.humidity);    // 送出濕度 (整數)
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print(sensor.temperature); // 送出溫度 (整數)
    lcd.print("\xDF""C"); // 0xDF 字元在 LCD 上是『°』符號
  }
  else { // 讀取失敗
    lcd.clear();
    lcd.print("error.."); // 顯示錯誤訊息
  }
  delay(2000); // 間隔 2 秒後再重新讀取
}
