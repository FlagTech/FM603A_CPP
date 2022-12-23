unsigned long now;     // 等待感測器穩定計時用 
int lightOn = false;   // 目前亮燈狀況

void setup() {
  pinMode(6,OUTPUT);   // 控制 LED 燈
  pinMode(2,INPUT);    // 接收人體紅外線感測狀態
  now = millis();      // 記錄目前時間
  
  // 等待 30 秒讓人體動作感測器穩定
  while(millis() - now < 30000) {
    digitalWrite(6,HIGH); // 等待期間閃爍 LED 燈
    delay(300);
    digitalWrite(6,LOW);
    delay(300);
  }
}

void loop() {
  if(digitalRead(2) == HIGH) { // 偵測到有人移動
    now = millis();            // 記錄目前時間
    digitalWrite(6,HIGH);      // 開啟 LED 燈
  }
  // 以下 else 部分表示沒有偵測到人體移動
  else if(millis() - now > 10000) {// 開啟 LED 燈至今超過 10 秒 
    digitalWrite(6,LOW);       // 熄滅 LED 燈
  }
}
