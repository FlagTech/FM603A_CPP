#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// 建立物件
LiquidCrystal_I2C lcd(0x2f, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
unsigned long startTime; // 之前時間
int seconds = 5;         // 倒數總秒數
int secondsLeft;         // 倒數剩餘秒數

// 發出警示音並讓 LCD 背光閃爍
void beepAndBlink() { 
  lcd.noBacklight();     // 關閉背光
  digitalWrite(6,HIGH);  // 開警示音
  delay(300);
  lcd.backlight();       // 開啟被光
  digitalWrite(6,LOW);   // 關警示音
  delay(300);
}

// 停止計時並在 LCD 上顯示使用說明
void stopTimer() {
  startTime = 0;      // 計時歸零
  lcd.setCursor(0,0); // 游標移回左上角
  lcd.print("Turn left to");
  lcd.setCursor(0,1); // 游標移到下列首
  lcd.print("start....");
}

void countDown() {     // 進行倒數計時
  if(startTime == 0) { // 尚未開始計時
    secondsLeft = seconds;
    lcd.clear();
    lcd.print(secondsLeft);
    startTime = millis(); // 記錄開始時間
  }
  else if(secondsLeft == 0) { // 計時終了
    beepAndBlink();           // 警示
  }
  else { // 檢查是否又過 1 秒
    if(millis() - startTime >= 1000) { 
      secondsLeft--;
      lcd.clear();
      startTime = millis(); // 重新記錄時間
      if(secondsLeft > 0)   // 尚未計時終了
        lcd.print(secondsLeft);
      else                  // 計時終了
        lcd.print("Time is up!");  
    }
  }
}

void setup() {
  pinMode(2,INPUT_PULLUP); // 傾斜開關腳位
  pinMode(6,OUTPUT);       // 蜂鳴器腳位
  lcd.begin(16,2);         // 啟用 LCD
}

void loop() {
  if(digitalRead(2) == HIGH) { // 未傾斜
    delay(100);                // 防碰撞
    if(digitalRead(2) == HIGH) // 確實未傾斜
      countDown();             // 倒數計時
  }
  else if(digitalRead(2) == LOW) { // 已傾斜
    delay(100);                    // 防碰撞
    if(digitalRead(2) == LOW) // 確定傾斜
      stopTimer();            // 停止計時
  }
}
