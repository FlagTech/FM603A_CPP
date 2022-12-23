void setup() {
  Serial.begin(9600);       // 啟用序列埠
}

int period = 0;             // 目前經過時間

void loop() {
  Serial.println(period++); // 送出經過時間到電腦
  delay(1000);              // 延遲 1 秒鐘
}
