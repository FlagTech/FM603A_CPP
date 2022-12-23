unsigned long now,period;     // 等待感測器穩定計時用 
int prev,curr;
void setup() {
  // put your setup code here, to run once:
  pinMode(6,OUTPUT);   // 控制 LED 燈
  pinMode(2,INPUT);    // 接收人體紅外線感測狀態
  now = millis();      // 記錄目前時間
  while(millis() - now < 30000) { // 等待 30 秒
    digitalWrite(6,HIGH); // 等待期間閃爍 LED 燈
    delay(300);
    digitalWrite(6,LOW);
    delay(300);
  }
  Serial.begin(9600);
  prev = digitalRead(2);
  now = millis();
}

void loop() {
  curr = digitalRead(2);
  if(curr != prev) {
    period = millis() - now;
    now = millis();
    Serial.print(prev);
    Serial.print(" to ");
    Serial.print(curr);
    Serial.print(" :");
    Serial.println(period);
    prev = curr;
  }
  // put your main code here, to run repeatedly:
  digitalWrite(6,digitalRead(2)); // 由感測結果控制燈光
}
