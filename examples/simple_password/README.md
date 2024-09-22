### Simple Password Application

To help understand its usage, I created a simple password application. Of course, it doesn't reflect real life very well. I aimed for it to be not too complex, so that beginners can also grasp it easily.

I will explain in more detail below.👇

| WRONG | CORRECT |
|---------|---------|
| ![Resim 1](https://github.com/arastaskiran/RustyKeypad/blob/main/.platform/assets/wrong_password.gif?raw=true) | ![Resim 2](https://github.com/arastaskiran/RustyKeypad/blob/main/.platform/assets/correct_password.gif?raw=true) |



## Libraries

```cpp
#include <Arduino.h>
#include <rusty_keypad.h>
#include <LiquidCrystal.h>
```

* Arduino.h: This is the core library for the Arduino platform. It provides basic functionalities for input/output operations, timing, and more.

* rusty_keypad.h: This includes a custom library for managing keypad functionalities. It allows you to interact with a keypad.

* LiquidCrystal.h: This library is used to control an LCD screen. It provides functions to display text on the LCD.
  
## LCD Initialization
```cpp
LiquidCrystal LCD(A2, A1, A3, 10, 11, 12, 13);
```
* This creates a LiquidCrystal object named LCD. The pins A2, A1, A3, 10, 11, 12, and 13 are the connections to the LCD.

## A) Native Functions

#### 1. setup Function
```cpp
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
```
* Serial.begin(115200): Initializes serial communication at a baud rate of 115200.

* pinMode(...): Sets the specified pins as outputs.

* LCD.begin(16, 2): Initializes the LCD dimensions (16 columns and 2 rows).

* The RustyKeypad functions configure the keypad:
  * addTextChangeListener: Adds the textChange function to listen for text changes on the keypad.

  * addEnterActionListener: Calls the textEnter function when the Enter key is pressed.

  * setEnterKey and useDeleteKey: Assign the Enter and Delete keys.

  * setType(RKP_T9): Sets the keypad to work in T9 mode.

  * enableBuzzer: Configures the buzzer.

* Calls waitPassword() to prompt the user for a password.

> [!IMPORTANT]
> If you want your password to be displayed with a * mask, please configure the following in the setup section.
```cpp
 RustyKeypad::setPasswordMask(true);
```

#### 2. loop Function
```cpp
void loop()
{
  RustyKeypad::scan();
}
```
* The loop() function runs continuously.
  
* RustyKeypad::scan(): Checks the inputs from the keypad.


## B) Implementation Functions

#### 1. waitPassword
```cpp
void waitPassword()
{
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("PLEASE PASSWORD:");
}
```
* Clears the LCD screen.
  
* Displays "PLEASE PASSWORD:" on the first line, prompting the user to enter a password.

#### 2. wrongPassword
```cpp
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
```

* This function is called when the password entered is incorrect.
  
* It clears the screen and shows "WRONG" and "PASSWORD".

* Waits for 2 seconds and then calls waitPassword() to prompt the user for the password again.

#### 3. correctPassword
```cpp
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
```
* This function is called when the password entered is correct.
  
* It clears the screen and shows "CORRECT" and "PASSWORD".
  
* Waits for 2 seconds and then calls waitPassword() to prompt for the password again.

#### 4. clearSecondRow
```cpp
void clearSecondRow()
{
  LCD.setCursor(0, 1);
  LCD.print("                ");
}
```
* Clears the second row of the LCD by writing 16 spaces.


#### 5. textChange
```cpp
void textChange(String x)
{
  clearSecondRow();
  LCD.setCursor(0, 1);
  LCD.print(x);
}
```
* This function is called when there is a change in the keypad input.

* It clears the second row and prints the new text x in that row.

#### 6. textEnter
```cpp
void textEnter(String text)
{
  if (RustyKeypad::isKeypadEqual("6789"))
  {
    correctPassword();
    return;
  }
  wrongPassword();
}
```
* This function is called after the user enters the password.

* If the entered password is "6789", it calls correctPassword(); otherwise, it calls wrongPassword().

