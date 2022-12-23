#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
char hello[] = "Hello, ARDUINO";
int len,spaces,curr = 1;

void setup()
{
  lcd.begin(16,2);               // initialize the lcd 

  lcd.home ();                   // go home
  lcd.print(hello);  
  len = strlen(hello);
  spaces = 16 - len;
  delay(2000);
}

void loop()
{
  lcd.clear();
  lcd.home();
  if(curr < len)
    lcd.print(hello + curr);
  if((len - curr + spaces) < 16) {
    lcd.setCursor(len - curr + spaces,0);
    lcd.print(hello);
  }
  curr = (curr + 1) % 16;
  delay(300);
}
