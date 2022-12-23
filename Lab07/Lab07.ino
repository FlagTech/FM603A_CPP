// 使用 Adafruit DHT-sensor-library
// http://learn.adafruit.com/dht/downloads
// 同時需要使用 Adafruit unified sensor library
// https://github.com/adafruit/Adafruit_Sensor
#include <DHT.h> 

// 建立物件, 提供接必須腳編號與感測器型號
// 此函式庫可同時適用於 DHT22 與 DHT21 型號感測器
DHT dht(2, DHT11);

void setup() {
  Serial.begin(9600); // 啟用序列埠
  dht.begin();        // 啟用溫濕度感測器
}

void loop() {  
  float h = dht.readHumidity();    // 讀取濕度
  float t = dht.readTemperature(); // 讀取攝氏溫度

  // 確認正確讀取到感測值
  if (isnan(h) || isnan(t)) {
    Serial.println("Error reading!");
    return;
  }

  // 依照溫度與相對濕度計算美國海洋大氣管理局制訂的熱指數
  // 第 3 個參數表示第 1 個參數是/否為華氏溫度？
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(h);     // 送出相對濕度到電腦上
  Serial.print("%\t");
  Serial.print(t);     // 送出攝氏溫度到電腦
  Serial.print("*C\t");
  Serial.print("(");
  Serial.print(hic);   // 附加熱指數到電腦端
  Serial.println("*C)");
  delay(2000); // 每次量測之間的間隔時間
}
