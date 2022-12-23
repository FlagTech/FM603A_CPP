#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// 建立物件
LiquidCrystal_I2C lcd(0x3f, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
unsigned long prevTime, currTime; // 之前時間與目前時間
int tick, timer;                  // 0.1 滴答數與倒數秒數
int btn;                          // 傾斜開關狀態
bool started = false;             // 是否已經開始倒數？
bool noodleOK = false;            // 倒數是否已經結束？(泡麵好了)

void printTimer() {      // 在 LCD 上顯示剩餘時間
  lcd.clear();           // 清除 LCD
  lcd.print(timer / 60); // 利用整數除法取得剩餘分鐘數
  lcd.print(":");     
  lcd.print(             // 若剩餘秒數不到 10 秒, 在十位數顯示 '0'
    timer % 60 < 10 ? "0":""); // % 為取除法餘數的運算
  lcd.print(timer % 60); // 顯示剩餘秒數
  lcd.setCursor(0,1);    // 游標一到下行開頭以便顯示進度條
}

void countDown() {       // 倒數 1 秒
  timer--;               // 將倒數秒數減 1
  if(timer <= 0) {       // 如果已經倒數完畢
    noodleOK = true;     // 設定泡麵已好
    started = false;
  }
}

void beepAndBlink() {    // 發出警示音並讓 LCD 背光閃爍
  lcd.noBacklight();
  digitalWrite(6,HIGH);
  delay(300);
  lcd.backlight();
  digitalWrite(6,LOW);
  delay(300);
}

void printUsage() {      // 在 LCD 上顯示使用說明
  lcd.clear();     
  lcd.print("Turn left to");
  lcd.setCursor(0,1);
  lcd.print("start....");
}

void setup() {
  pinMode(2,INPUT_PULLUP);    // 傾斜開關腳位
  pinMode(6,OUTPUT);          // 控制蜂鳴器的腳位
  lcd.begin(16,2);            // 啟用 LCD
  printUsage();               // 顯示用法
}

void loop() {
  btn = digitalRead(2);       // 讀取傾斜開關狀態
  if(!noodleOK) {             // 目前不是倒數完成的階段
    if(!started) {            // 而且也還沒有啟動倒數
      if(btn == HIGH) {       // 翻轉泡麵計時器成傾斜狀態
        delay(100);           // 等待 100 毫秒讓開關穩定
        btn = digitalRead(2); // 重複讀取開關狀態
        if(btn == HIGH) {     // 依舊維持傾斜
          tick = 0;           // 設定滴答計數為 0
          timer = 5;          // 設定倒數總秒數
          printTimer();       // 顯示剩餘時間
          started = true;     // 設定開始計時
          noodleOK = false;   // 泡麵還沒好
          prevTime = millis();// 記錄開始計時的時間
        }
      }
    }
    else {                    // 已經開始計時     
      currTime = millis();    // 取得目前時間
      if(currTime - prevTime >= 100) { // 已經過 0.1 秒
        if(tick == 9) {       // 總共已經過了 9 * 0.1 + 0.1 = 1 秒
          tick = 0;           // 將滴答計數重設回 0
          countDown();        // 倒數 1 秒
          printTimer();       // 顯示目前剩餘時間
        }
        else {
          tick++;             // 遞增滴答計數
          lcd.print("\xFF");  // 印出 0.1 秒刻度
        }
        prevTime = currTime;  // 記錄目前時間
      }
    }
  }
  if(btn == LOW) {            // 將計時器翻轉回未傾斜狀態
    delay(100);               // 等待 0.1 秒讓開關穩定
    btn = digitalRead(2);     // 重新取得開關狀態
    if(btn == LOW) {          // 仍然維持未傾斜, 終止計時
      if(started || noodleOK) printUsage();   // 顯示使用說明
      started = noodleOK = false; // 停止計時及警示通知
    }
  }
  if(noodleOK) {         // 倒數計時完成, 泡麵可以吃了
    beepAndBlink();      // 發出通知警示音並閃爍 LCD 背光
  }
}
