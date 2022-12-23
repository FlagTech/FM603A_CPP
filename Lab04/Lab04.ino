unsigned long now;     // 等待感測器穩定計時用 

void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);   // 控制 LED 燈
  pinMode(2,INPUT);    // 接收人體紅外線感測狀態
  now = millis();      // 記錄目前時間
  while(millis() - now < 30000) { // 等待 30 秒
    digitalWrite(13,HIGH); // 等待期間閃爍 LED 燈
    delay(300);
    digitalWrite(13,LOW);
    delay(300);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13,digitalRead(2)); // 由感測結果控制燈光
}
