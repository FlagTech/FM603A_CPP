#include<Wire.h>

#define ADXL345_I2C_ADDR 0x53

void ADXLWriteByte(byte reg,byte val) { // 寫入 1 個位元組到指定位址
  Wire.beginTransmission(ADXL345_I2C_ADDR); // 開始傳輸
  Wire.write(reg);                          // 指定位址
  Wire.write(val);                          // 寫入資料
  Wire.endTransmission();                   // 結束傳輸
}

int ADXLReadInt32(byte reg) { // 從指定位址讀取 16 位元長度的有號整數
  byte high,low;                    // 整數的高低位元組
  Wire.beginTransmission(ADXL345_I2C_ADDR); // 開始傳輸
  Wire.write(reg);                          // 指定位址
  Wire.endTransmission();                   // 結束傳輸
  if(Wire.requestFrom(ADXL345_I2C_ADDR,2) == 2) { // 讀取 2 個位元組回來
    low = Wire.read();                      // 取得低位元組
    high = Wire.read();                     // 取得高位元組
    return int16_t(word(high,low));                  // 組合成 16 位元有號整數 
  }
  return 32767; // 若讀取有問題, 傳回 32767
}

void setup() {
  Serial.begin(9600);
  Wire.begin();             // 啟用 Wire (I2C) 程式庫
  ADXLWriteByte(0x31,0x0B); // 高解析度, ±16g 範圍
  ADXLWriteByte(0x2D,0x08); // 進入測量模式
  //ADXLWriteByte(0x1E,-6);   // 設定 X 軸偏移補正量 (單位：15.6mg)
  //ADXLWriteByte(0x1F,+6);   // 設定 Y 軸偏移補正量 (單位：15.6mg)
  //ADXLWriteByte(0x20,-9);   // 設定 Z 軸偏移補正量 (單位：15.6mg)
}

int x,y,z;
void loop() {
  x = ADXLReadInt32(0x32); // 讀取 X 軸加速度
  y = ADXLReadInt32(0x34); // 讀取 X 軸加速度
  z = ADXLReadInt32(0x36); // 讀取 Z 軸加速度
  Serial.print(x * 0.0039,4); // 高解析度為 0.004g
  Serial.print(",");
  Serial.print(y * 0.0039,4);
  Serial.print(",");
  Serial.println(z * 0.0039,4);
  delay(300);
}
