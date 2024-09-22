#include <Arduino.h>
#include <rusty_keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal LCD(A2, A1, A3, 10, 11, 12, 13);

void waitPassword()
{
 
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("PLEASE PASSWORD:");
}

void wrongPassword()
{
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("WRONG");
  LCD.setCursor(0, 1);
  LCD.print("PASSWORD");
  delay(2000);
  waitPassword();
}

void correctPassword()
{
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("CORRECT");
  LCD.setCursor(0, 1);
  LCD.print("PASSWORD");
  delay(2000);
  waitPassword();
}

void clearSecondRow()
{
  LCD.setCursor(0, 1);
  LCD.print("                ");
}

void textChange(String x)
{
  clearSecondRow();
  LCD.setCursor(0, 1);
  LCD.print(x);
}

void textEnter(String text)
{
  if (RustyKeypad::isKeypadEqual("6789"))
  {
    correctPassword();
    return;
  }
  wrongPassword();
}

void setup()
{
  Serial.begin(115200);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  LCD.begin(16, 2);
  RustyKeypad::addTextChangeListener(textChange);
  RustyKeypad::addEnterActionListener(textEnter);
  RustyKeypad::setEnterKey('#');
  RustyKeypad::useDeleteKey('*');
  RustyKeypad::setType(RKP_T9);
  RustyKeypad::enableBuzzer(9, 10UL);
  RustyKeypad::enable(); 
  waitPassword();
}

void loop()
{
  RustyKeypad::scan();
  // put your main code here, to run repeatedly:
}
