// 使用 DHT11 library
// http://playground.arduino.cc/Main/DHT11Lib
#include <dht11.h>

// 建立感測物件
dht11 sensor;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // 從數位 2 腳讀取溫濕度
  if(sensor.read(2) == DHTLIB_OK) {     // 如果成功讀取
    Serial.print(sensor.humidity);    // 送出濕度 (整數)
    Serial.print("%\t");
    Serial.print(sensor.temperature); // 送出溫度 (整數)
    Serial.println("*C");
  }
  else { // 讀取失敗
    Serial.println("error.."); // 顯示錯誤訊息
  }
  delay(2000); // 間隔 2 秒後再重新讀取
}
