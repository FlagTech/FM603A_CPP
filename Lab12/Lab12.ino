// 使用 Sparkfun's ADXL345 Library
// https://github.com/sparkfun/SparkFun_ADXL345_Arduino_Library
#include <SparkFun_ADXL345.h>
#include <LiquidCrystal_I2C.h>

ADXL345 adxl = ADXL345();             // 採用 I2C 通訊介面
LiquidCrystal_I2C lcd(0x3f, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

#define RES (0.004)                   // 解析度為 0.004g
double gains[] = {RES,RES,RES};       

void setup(){
  adxl.powerOn();                     // 開啟電源
  adxl.setRangeSetting(16);           // 設定偵測範圍
  adxl.setFullResBit(true);
//  adxl.setAxisGains(gains);           // 設定解析度
 adxl.setAxisOffset(0,0,0);
  lcd.begin(16,2);
}

//double xyz[3];
int xyz[3];
int x,y,z;   

void loop(){
  lcd.clear();
  //adxl.get_Gxyz(xyz);
  adxl.readAccel(xyz);
  lcd.print(int(xyz[0] * 3.9));
  lcd.setCursor(8,0);
  lcd.print(int(xyz[1] * 3.9));
  lcd.setCursor(0,1);
  lcd.print(int(xyz[2] * 3.9)); 
  delay(200);
}
