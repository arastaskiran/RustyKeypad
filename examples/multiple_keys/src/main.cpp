#include <Arduino.h>
#include <rusty_keypad.h>




void textChange(String text)
{
  Serial.println(text);
}

void multipleKeys(String text)
{
   Serial.println(text);
}

void setup()
{
  Serial.begin(9600);

  RustyKeypad::addTextChangeListener(textChange);
  RustyKeypad::addMultipleKeyListener(multipleKeys);
  RustyKeypad::setType(RKP_INTEGER);
  RustyKeypad::enable(); 
  
}

void loop()
{
  RustyKeypad::scan();
  // put your main code here, to run repeatedly:
}
