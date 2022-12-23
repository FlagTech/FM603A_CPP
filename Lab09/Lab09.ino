#include <DHT.h> 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// 建立物件
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
DHT dht(2, DHT11);

void setup() {
  dht.begin();        // 啟用溫濕度感測器
  lcd.begin(16,2);    // 啟用 LCD
}

void loop() {
  lcd.home();
  float h = dht.readHumidity();    // 讀取濕度
  float t = dht.readTemperature(); // 讀取攝氏溫度

  // 確認正確讀取到感測值
  if (isnan(h) || isnan(t)) {
    lcd.clear();
    lcd.print("Error occurred!");
    return;
  }

  lcd.print(h,0);     // 送出相對濕度到電腦上
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print(t,0);     // 送出攝氏溫度到電腦
  lcd.print("\xDF""C");
  delay(2000); // 每次量測之間的間隔時間
}
