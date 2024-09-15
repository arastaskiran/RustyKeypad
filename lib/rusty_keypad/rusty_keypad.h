#ifndef RUSTY_KEYPAD_H
#define RUSTY_KEYPAD_H

#include <base_keypad.h>

class RustyKeypad: public BaseRustyKeypad {

public:
    static void scan();

private:
    static bool checkKey(RustyKey* key);


};
#endif