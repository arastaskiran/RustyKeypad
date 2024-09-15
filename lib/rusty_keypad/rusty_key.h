#ifndef KEYPAD_RUSTY_KEY_H
#define KEYPAD_RUSTY_KEY_H

#include <stdint.h>
#define RUSTY_KEYPAD_KEY_FILTER_MILLIS 20

typedef enum KeypadEventTypes
{
    KEY_IDLE,
    KEY_DOWN,
    KEY_UP,
    LONG_PRESS,
    WAIT
} KeypadEventTypes;

class RustyKey
{

public:
    RustyKey(char key, uint8_t row_pin, uint8_t col_pin);
    ~RustyKey();
    bool check();
    void reset();
    bool isPressed();
    void disable();
    void enable();
    bool read();
    KeypadEventTypes getCurrentEvent() const;
    char getKeyCode() const;

protected:
private:
    unsigned long last_activity_ts;
    KeypadEventTypes current_event;
    char key_code;
    uint8_t row_out_pin;
    uint8_t col_in_pin;
    bool enabled;
    void rowActive();
    void rowPassive();
    bool current_state;
    void analyzeState();   
    bool checkTimeout();
    void setEvent(KeypadEventTypes e);
    bool isScanAvailable();
};
#endif