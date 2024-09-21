import os

if not os.path.isfile("src/main.cpp"):
    with open("src/main.cpp", "w") as file:
        file.write(
            """\
#include <Arduino.h>
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
  Serial.begin(115200);
  RustyKeypad::addKeyUpListener(keyUp);
  RustyKeypad::addMultipleKeyListener(multipleKey);
  RustyKeypad::addKeyDownListener(keyDown);
  RustyKeypad::setType(T9);
  RustyKeypad::enable();
}

void loop() { 
  RustyKeypad::scan();  
  // put your main code here, to run repeatedly:
}
"""
        )
