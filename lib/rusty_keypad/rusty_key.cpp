#include <rusty_key.h>
#include <Arduino.h>
#include <rusty_keypad.h>

RustyKey::RustyKey(char key, uint8_t row_pin, uint8_t col_pin)
{
    key_code = key;
    row_out_pin = row_pin;
    col_in_pin = col_pin;
    current_state = false;
    enabled = true;
    setEvent(KEY_IDLE);    
    pinMode(row_pin, OUTPUT);
    pinMode(col_pin, RustyKeypad::pins_mode);
    
}

RustyKey::~RustyKey()
{
    rowPassive();
}

bool RustyKey::check()
{
    if(!isScanAvailable())
    {
        return false;
    }

    bool new_state = read();
    if (new_state == current_state)
    {
        if (new_state && current_event != WAIT)
        {
            setEvent(WAIT);
        }
        else if (!new_state && current_event != KEY_IDLE)
        {
            setEvent(KEY_IDLE);           
        }
        return !current_state ? false : checkTimeout();
    }
    current_state = new_state;
    if (!new_state)
    {
        analyzeState();        
        return true;
    }
    setEvent(KEY_DOWN);
    return true;
}

bool RustyKey::checkTimeout()
{

    if ((millis() - last_activity_ts) > RustyKeypad::keydown_timeout)
    {        
        setEvent(KEY_DOWN);
        return true;
    }
    return false;
}

bool RustyKey::isPressed()
{
    return current_state;
}

void RustyKey::analyzeState()
{
    if ((millis() - last_activity_ts) > RustyKeypad::long_press_duration)
    {
        setEvent(LONG_PRESS);
        return;
    }
    setEvent(KEY_UP);
}

bool RustyKey::read()
{

    if (!enabled)
    {
        if (digitalRead(row_out_pin) == (RustyKeypad::pins_mode == INPUT_PULLUP ? LOW : HIGH))
        {
            rowPassive();
        }
        return false;
    }
    rowActive();
    bool state = (digitalRead(col_in_pin) == (RustyKeypad::pins_mode == INPUT_PULLUP ? LOW : HIGH));
    rowPassive();

    return state;
}

void RustyKey::reset()
{
    current_state = false;
    current_event = KEY_IDLE;
}

void RustyKey::enable()
{
    if (!enabled)
    {
        reset();
        enabled = true;
    }
}

void RustyKey::disable()
{
    if (enabled)
    {
        reset();
        enabled = false;
    }
}

void RustyKey::rowActive()
{
    digitalWrite(row_out_pin, (RustyKeypad::pins_mode == INPUT_PULLUP ? LOW : HIGH));
}
void RustyKey::rowPassive()
{
    digitalWrite(row_out_pin, (RustyKeypad::pins_mode == INPUT_PULLUP ? HIGH : LOW));
}

KeypadEventTypes RustyKey::getCurrentEvent() const
{
    return current_event;
}

char RustyKey::getKeyCode() const
{
    return key_code;
}

void RustyKey::setEvent(KeypadEventTypes e)
{
    current_event = e;
    last_activity_ts = millis();
}

bool RustyKey::isScanAvailable()
{
    return ((millis() - last_activity_ts) > RUSTY_KEYPAD_KEY_FILTER_MILLIS);
}