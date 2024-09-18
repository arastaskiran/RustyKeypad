#include <rusty_keypad.h>

void keyUp(char x)
{
  Serial.println(x);

}
void multipleKey(String x)
{
  Serial.println(x);
}

void keyDown(char x)
{
  Serial.println(x);

}
void setup() {
  Serial.begin(9600);
  RustyKeypad::addKeyUpListener(keyUp);
  RustyKeypad::addMultipleKeyListener(multipleKey);
  RustyKeypad::addKeyDownListener(keyDown);
  RustyKeypad::setType(INTEGER);
  RustyKeypad::enable();
  
}

void loop() { 
  RustyKeypad::scan();  
}


