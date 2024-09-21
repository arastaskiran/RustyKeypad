#include <rusty_key.h>
#include <Arduino.h>
#include <rusty_keypad.h>

RustyKey::RustyKey(const char *key, uint8_t row_pin, uint8_t col_pin)
{
    key_code = key;
    row_out_pin = row_pin;
    col_in_pin = col_pin;
    current_state = false;
    enabled = true;
    char_index = 0;
    setEvent(RKP_KEY_IDLE);
    pinMode(row_pin, OUTPUT);
    pinMode(col_pin, RustyKeypad::pins_mode);
}

RustyKey::~RustyKey()
{
    rowPassive();
}

bool RustyKey::check()
{
    if (!isScanAvailable())
    {
        return false;
    }

    bool new_state = read();
    if (new_state == current_state)
    {
        return analyzeSameState(new_state);
    }
    current_state = new_state;
    if (!new_state)
    {
        analyzeState();
        return true;
    }
    char_index = 0;
    setEvent(RKP_KEY_DOWN);
    return true;
}

void RustyKey::nextCharIndex()
{
    if ((char_index + 1) >= (int)strlen(key_code))
        char_index = 0;
    else
        char_index++;

    resetActivityTimer();
}
bool RustyKey::checkTimeout()
{
    if (RustyKeypad::isDeleteKey(getFirstKeyCode()))
    {
        if (isOverT9Duration())
        {
            setEvent(RKP_PRESS_DELETE);
            return true;
        }
    }
    if (RustyKeypad::getType() == RKP_T9)
    {
        if (isOverT9Duration())
        {
            nextCharIndex();
            setEvent(RKP_KEY_DOWN);
            return true;
        }
        return false;
    }

    if (isOverKeydownDuration())
    {
        setEvent(RKP_KEY_UP);
        return true;
    }
    return false;
}

bool RustyKey::isOverT9Duration()
{
    return ((millis() - last_activity_ts) > RustyKeypad::t9_duration);
}

bool RustyKey::isOverKeydownDuration()
{
    return ((millis() - last_activity_ts) > RustyKeypad::keydown_timeout);
}

bool RustyKey::isPressed()
{
    return current_state;
}

void RustyKey::analyzeState()
{
    if (getCurrentEvent() == RKP_PRESS_DELETE)
    {
        setEvent(RKP_RELEASE_DELETE);
        return;
    }
    if (RustyKeypad::getType() == RKP_T9)
    {
        setEvent(RKP_KEY_UP);
        return;
    }
    if ((millis() - last_activity_ts) > RustyKeypad::long_press_duration)
    {
        setEvent(RKP_LONG_PRESS);
        return;
    }
    setEvent(RKP_KEY_UP);
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
    char_index = 0;
    current_state = false;
    setEvent(RKP_KEY_IDLE);
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
    return key_code[char_index];
}

char RustyKey::getFirstKeyCode() const
{
    return key_code[0];
}

void RustyKey::setEvent(KeypadEventTypes e)
{

    current_event = e;
    resetActivityTimer();
}
void RustyKey::resetActivityTimer()
{
    last_activity_ts = millis();
}

bool RustyKey::isScanAvailable()
{
    return ((millis() - last_activity_ts) > RUSTY_KEYPAD_KEY_FILTER_MILLIS);
}

bool RustyKey::isEqual(const RustyKey *key)
{
    if (key == nullptr)
        return false;

    return getFirstKeyCode() == key->getFirstKeyCode();
}

bool RustyKey::analyzeSameState(bool new_state)
{
    if (new_state && current_event != RKP_WAIT)
    {
        if (current_event == RKP_PRESS_DELETE)
        {
            return false;
        }
        if (current_event == RKP_KEY_UP)
        {
            char_index = 0;
            setEvent(RKP_KEY_DOWN);
            return true;
        }
        setEvent(RKP_WAIT);
    }
    else if (!new_state && current_event != RKP_KEY_IDLE)
    {
        setEvent(RKP_KEY_IDLE);
    }
    return !current_state ? false : checkTimeout();
}