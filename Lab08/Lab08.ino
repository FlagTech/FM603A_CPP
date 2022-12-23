// 使用 New LiquidCrystal 函式庫
// https://bitbucket.org/fmalpartida/new-liquidcrystal
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// 建立 LCD 物件
// 參數：LCD 控制板 I2C 位址,....,是否開啟背光？
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup()
{
  lcd.begin(16,2); // 啟用 LCD, 指定共 16 直行、2 橫列

  lcd.home ();     // 將游標歸位回左上角
  lcd.print("Hello, ARDUINO"); // 顯示字串
  delay ( 1000 );
}

void loop()
{
  //lcd.scrollDisplayLeft(); // 將 LCD 目前內容往左捲動一直行
  delay(400);
}
