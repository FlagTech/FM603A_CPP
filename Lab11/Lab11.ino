#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// 建立物件
LiquidCrystal_I2C lcd(0x3f, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int level;                    // 目前水位
bool warning = false;         // 是否在警示狀態

void beepAndBlink() {         // 發出警示音並讓 LCD 背光閃爍
  lcd.noBacklight();
  digitalWrite(6,HIGH);
  delay(300);
  lcd.backlight();
  digitalWrite(6,LOW);
  delay(300);
}

void setup() {
  pinMode(6,OUTPUT);          // 控制蜂鳴器的腳位
  lcd.begin(16,2);            // 啟用 LCD
  lcd.home();
  lcd.print("Current level:");
}

void loop() {
  level = analogRead(A0);     // 讀取傾斜水位計值
  lcd.setCursor(0,1);         // 清除 LCD 顯示數值
  lcd.print("    ");
  lcd.setCursor(0,1);         // 顯示目前數值
  lcd.print(level);   
  if(!warning) {              // 目前不是警戒狀態
    if(level > 480) {         // 但是水位超過 480 了
      warning = true;         // 進入警戒狀態
    }
  }
  else if(level < 450) {      // 本來是警戒狀態但水位降到 450 以下
    warning = false;          // 取消警戒狀態
  }
  if(warning) {               // 警戒狀態下
    beepAndBlink();           // 發出通知警示音並閃爍 LCD 背光
  }
  else { 
    delay(300);               // 否則等待 0.3 秒後重新偵測水位
  }
}
