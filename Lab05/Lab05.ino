void setup() {
  pinMode(13,OUTPUT);   // 控制蜂鳴器
  pinMode(2,INPUT);    // 接收霍爾磁力感測
  Serial.begin(9600);
}

void loop() {
  while(digitalRead(2) == HIGH) { // 偵測到磁力消失
    digitalWrite(13,HIGH);     // 發出警示音
    delay(300);
    digitalWrite(13,LOW);
    delay(300);
  }
//  Serial.println(analogRead(A0));
//  delay(300);
}
