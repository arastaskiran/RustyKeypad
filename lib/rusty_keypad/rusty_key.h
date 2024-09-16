/*
 * RustyKey Class
 *
 * Author: Aras TAŞKIRAN
 * Email: aras@arastaskiran.com
 * Date: 2024-09-2024
 *
 * Description:
 *
 * Each key on the KeyPad is derived from this class.
 * Specifically, everything related to the key will be handled within this class.
 *
 * License:
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef KEYPAD_RUSTY_KEY_H
#define KEYPAD_RUSTY_KEY_H

#include <stdint.h>
#define RUSTY_KEYPAD_KEY_FILTER_MILLIS 20
/**
 * @enum KeypadEventTypes
 * @brief Defines various states or events for a keypad.
 *
 * This enumeration represents the different states a key on the keypad can experience during operation.
 * These states are useful for tracking key interactions like pressing, releasing, or holding down a key.
 */
typedef enum KeypadEventTypes
{
    /** The key is idle, not pressed. */
    KEY_IDLE,

    /** The key has just been pressed down. */
    KEY_DOWN,

    /** The key has been released. */
    KEY_UP,

    /** The key is held down for a long press. */
    LONG_PRESS,

    /** The key is waiting for the next interaction. */
    WAIT
} KeypadEventTypes;

class RustyKey
{

public:
    /**
     * @brief Constructs a RustyKey object.
     *
     * Initializes a key with a specified character and assigns it to the given row and column pins.
     *
     * @param key       A constant character pointer representing the key's value (e.g., "A", "A1B", "*").
     * @param row_pin   The GPIO pin for the row where the key is located.
     * @param col_pin   The GPIO pin for the column where the key is located.
     *
     * @example
     * RustyKey key1("A", 5, 2);  // Creates key 'A' at row pin 5, column pin 2
     */
    RustyKey(const char *key, uint8_t row_pin, uint8_t col_pin);
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
    const char *key_code;
    uint8_t row_out_pin;
    uint8_t col_in_pin;
    uint8_t char_index;
    bool enabled;
    void rowActive();
    void rowPassive();
    bool current_state;
    void analyzeState();
    bool checkTimeout();
    void setEvent(KeypadEventTypes e);
    bool isScanAvailable();
    void nextCharIndex();
    void resetActivityTimer();
};
#endif