int temp,humi;

int DHT11Read(int dataPin) {
  int currByte,currBit;
  byte data[5],checkSum;
  unsigned long startTime;
  
  for(int i = 0;i < 5;i++) {  // 先清除舊資料
    data[i] = 0;
  }
  
  pinMode(dataPin,OUTPUT);    // 設為輸出模式通知 DHT11 送出資料
  digitalWrite(dataPin,LOW);  // 持續輸出低電位 18ms
  delay(18);
  digitalWrite(dataPin,HIGH); // 持續輸出高電位 40μs
  delayMicroseconds(40);

  pinMode(dataPin,INPUT); // 設為輸入模式準備接收 DHT11 送來的資料
  startTime = micros();                 // 記錄開始等待時間
  while(digitalRead(dataPin) == LOW) {  // 等待 DHT11 送出高電位
    if(micros() - startTime > 90) {     // 若等待超過 80+10μs
      return -1;                        // 表示 DHT11 出錯逾時
    }
  }
  startTime = micros();                 // 記錄開始等待時間
  while(digitalRead(dataPin) == HIGH) { // 等待 DHT11 送出低電位
    if(micros() - startTime > 90) {     // 若等待超過 80+10μs
      return -1;                        // 表示 DHT11 出錯逾時
    }
  }

  currByte = 0; // 準備接收 DHT11 送出的溫濕度資料
  currBit = 7;  // 從 data[0] 的最高位元 (bit7) 開始接收
  for(int i = 0;i < 40;i++) { // 完整資料共 40 個位元
    startTime = micros();                // 記錄開始等待時間
    while(digitalRead(dataPin) == LOW) { // 等待 DHT11 送出高電位
      if(micros() - startTime > 60) {    // 若等待超過 50+10μs
        return -1;                       // 表示 DHT11 出錯逾時
      }
    }
    startTime = micros();                 // 記錄開始等待時間
    while(digitalRead(dataPin) == HIGH) { // 等待 DHT11 送出低電位
      if(micros() - startTime > 80) {     // 若等待超過 70+10μs
        return -1;                        // 表示 DHT11 出錯逾時
      }
    }
    // 高電位持續 28μs 為 0, 70μs 為 1, 此處以中間的 50μs 為界判斷
    if((micros() - startTime) > 50) {
      // 將目前處理位元組中的對應位元設為 1
      data[currByte] = data[currByte] | (1 << currBit);
    }
    if(currBit == 0) { // 若接收的是目前位元組中的最低位元
      currByte++;      // 下一次接收的就是下個位元組的資料
      currBit = 7;     // 一樣是從最高位元開始接收資料
    }
    else {
      currBit--;       // 往低位元方向接收下一個位元資料
    }
  }
  checkSum = data[0] + data[1] + data[2] + data[3]; // 計算校驗值
  if(checkSum != data[4]){                          // 檢核資料正確
    return -2;
  }
  temp = data[2]; // 取出溫度整數部分 (DHT11 解析度為 1 度, 小數部分恆為 0, 忽略)
  humi = data[0]; // 取出濕度整數部分 (DHT11 解析度為 1%, 小數部分恆為 0, 忽略)
  return 0;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  if(DHT11Read(2) == 0) {
    Serial.print("temp:");
    Serial.print(temp);
    Serial.print("\thumi:");
    Serial.println(humi);
  }
  else {
    Serial.println("Reading error....");
  }
  delay(300);
}
