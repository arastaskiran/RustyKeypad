/*
||
|| @file base_keypad.h
|| @version 1.0
|| @author Aras TAŞKIRAN
|| @contact aras@arastaskiran.com
||
|| @description
|| | Add the configurations for the Rusty Keypad program to this class
|| #
||
|| @license
|| | This library is free software; you can redistribute it and/or
|| | modify it under the terms of the GNU Lesser General Public
|| | License as published by the Free Software Foundation; version
|| | 2.1 of the License.
|| |
|| | This library is distributed in the hope that it will be useful,
|| | but WITHOUT ANY WARRANTY; without even the implied warranty of
|| | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
|| | Lesser General Public License for more details.
|| |
|| | You should have received a copy of the GNU Lesser General Public
|| | License along with this library; if not, write to the Free Software
|| | Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
|| #
||
*/
#ifndef BASE_KEYPAD_RUSTY_KEY_H
#define BASE_KEYPAD_RUSTY_KEY_H

#include <stdint.h>
#include <Arduino.h>
#include <rusty_key_list.h>

#define MAX_KEYPAD_MATRIX_SIZE 5

typedef enum
{
    INTEGER,
    FLOAT

} KeypadTypes;
typedef enum
{
    NONE_KEY_ACTION,
    ENTER,
    DELETE,
    CLEAR,
    CHANGED,   
    IDLE
} KeypadActionEvents;
typedef enum
{
    SCAN_IN_LOOP = 0,
    SCAN_ITERATION = 1,

} KeypadDriverTypes;

class BaseRustyKeypad
{

public:
    static void keyboardSetup(
        char map[MAX_KEYPAD_MATRIX_SIZE][MAX_KEYPAD_MATRIX_SIZE],
        uint8_t row_pins[MAX_KEYPAD_MATRIX_SIZE],
        uint8_t col_pins[MAX_KEYPAD_MATRIX_SIZE],
        uint8_t row,
        uint8_t col,
        uint8_t mode = INPUT_PULLUP);
    static void enable();
    static void disable();
    static uint8_t pins_mode;
    static unsigned long keydown_timeout;
    static unsigned long long_press_duration;
    static void addKeyDownListener(void (*listener)(char));
    static void addKeyUpListener(void (*listener)(char));
    static void addLongPressListener(void (*listener)(char));
    static void addMultipleKeyListener(void (*listener)(String));
    static bool isEnabled();

protected:
    static void reset();
    static void clearScreen();
    static RustyKeyList *KeyList;
    static void setFactoryConfig();
    static void (*keyDownListener)(char);
    static void (*keyUpListener)(char);
    static void (*longPressListener)(char);
    static void (*multipleKeyListener)(String);
    static bool interrupted;

private:
    static uint8_t row_size;
    static uint8_t col_size;
    static char float_char;    
    static uint8_t keypad_type;
    static bool enabled;
    static String keypad_data;
    static unsigned int keypad_data_cursor;
    static unsigned long idle_timeout;
    static unsigned long last_activity_ts;
    static void setCursor(uint8_t x, uint8_t y);
    static void appendKey(char key);
    static uint8_t *row_out_pins;
    static void resizeRowPins(size_t size);
};
#endif