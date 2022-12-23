int prevTouch = LOW;   // 觸控感測器之前狀態
int currTouch = LOW;   // 觸控感測器目前狀態
bool lightOn = false;  // 燈光狀態, 預設為不亮

void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);   // 控制 LED 燈
  pinMode(2,INPUT);    // 接收觸控按鈕狀態
  digitalWrite(6,LOW); // 先熄掉 LED 燈
}

void loop() {
  // put your main code here, to run repeatedly:
  currTouch = digitalRead(2); // 讀取觸控感測器狀態
  // 如果之前沒有觸碰, 而現在觸碰了, 就切換燈光
  if(prevTouch == LOW && currTouch == HIGH) {
    lightOn = !lightOn; // 燈光由亮變不亮, 或不亮變亮
    digitalWrite(13,lightOn); // 實際控制燈光
  }
  prevTouch = currTouch; // 記錄本次觸控感測器狀態
}
