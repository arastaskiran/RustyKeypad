/*
 * BaseRustyKeypad Class
 *
 * Author: Aras TAŞKIRAN
 * Email: aras@arastaskiran.com
 * Date: 2024-09-2024
 *
 * Description:
 *
 * I will store the keypad configurations within this class.
 * I thought the keypad should be static, hopefully I won't regret it.
 * A keyboard is a keyboard everywhere in the application :)
 * Joking aside, since it's a fairly resource-intensive class,
 * I didn’t want to overburden the Arduino processor.
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

#ifndef BASE_KEYPAD_RUSTY_KEY_H
#define BASE_KEYPAD_RUSTY_KEY_H

#include <stdint.h>
#include <Arduino.h>
#include <rusty_key_list.h>

/**
 * @brief Defines the maximum size of the keypad matrix.
 * 
 * This macro sets the maximum number of rows and columns allowed in the keypad matrix.
 * It ensures that the keypad matrix does not exceed this size to maintain compatibility
 * with the rest of the system and avoid memory issues.
 * 
 * @note Adjust this value based on the specific requirements of your keypad matrix.
 */
#define MAX_KEYPAD_MATRIX_SIZE 5

/**
 * @enum KeypadTypes
 * @brief Defines the types of keypads.
 *
 * This enumeration represents the different types of keypads that can be used in the system.
 * It helps categorize keypads based on their input methods or formats.
 */
typedef enum
{
    /** Keypad for integer input. */
    INTEGER,

    /** Keypad for floating-point input. */
    FLOAT,

    /** Keypad for T9 text input. */
    T9

} KeypadTypes;
/**
 * @enum KeypadActionEvents
 * @brief Defines various actions or events associated with keypad interactions.
 *
 * This enumeration represents the different actions or events that can occur on a keypad,
 * such as entering a value, deleting, clearing, or indicating idle states.
 */
typedef enum
{
    /** No action or event. */
    NONE_KEY_ACTION,

    /** The action of entering a value. */
    ENTER,

    /** The action of deleting a value. */
    DELETE,

    /** The action of clearing the keypad input. */
    CLEAR,

    /** Indicates that the state has changed. */
    CHANGED,

    /** The keypad is idle, with no current action. */
    IDLE
} KeypadActionEvents;
/**
 * @enum KeypadDriverTypes
 * @brief Defines different types of keypad scanning methods.
 *
 * This enumeration represents the scanning methods used by the keypad driver,
 * determining how the keypad input is processed.
 */
typedef enum
{
    /** Scans the keypad in a continuous loop. */
    SCAN_IN_LOOP = 0,

    /** Scans the keypad in a single iteration. */
    SCAN_ITERATION = 1

} KeypadDriverTypes;

class BaseRustyKeypad
{

public:
    /**
     * @brief Configures the keypad matrix and associated pins.
     *
     * This static function sets up the keypad matrix by specifying the layout, row and column pins,
     * and the operating mode for the input pins. It initializes the keypad based on the provided parameters.
     *
     * @param map          A 2D array representing the keypad layout. Each entry in the array corresponds
     *                     to a key or a set of keys in the keypad matrix.
     * @param row_pins     An array of GPIO pins assigned to the rows of the keypad matrix.
     * @param col_pins     An array of GPIO pins assigned to the columns of the keypad matrix.
     * @param row          The number of rows in the keypad matrix.
     * @param col          The number of columns in the keypad matrix.
     * @param mode         The input mode for the GPIO pins (default is INPUT_PULLUP). This determines
     *                     the electrical state of the pins when not actively driven.
     *
     * @example
     * const char *map[MAX_KEYPAD_MATRIX_SIZE][MAX_KEYPAD_MATRIX_SIZE] = {
     *     {"1.,?!'\"-()@/:_", "2ABCabc", "3DEFdef"},
     *     {"4GHIghiİ", "5JKLjkl", "6MNOmnoÖö"},
     *     {"7PQRSpqrsŞş", "8TUVtuvÜü", "9WXYZwxyz"},
     *     {"*", "0 +", "#"},
     * };
     *
     * uint8_t rows[MAX_KEYPAD_MATRIX_SIZE] = {2U, 3U, 4U, 5U};
     * uint8_t cols[MAX_KEYPAD_MATRIX_SIZE] = {6U, 7U, 8U};
     *
     * keyboardSetup(
     *     map,
     *     rows,
     *     cols,
     *     (uint8_t)4,
     *     (uint8_t)3,
     *     INPUT_PULLUP
     * );
     */
    static void keyboardSetup(
        const char *map[MAX_KEYPAD_MATRIX_SIZE][MAX_KEYPAD_MATRIX_SIZE],
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
    static unsigned long t9_duration;
    static void addKeyDownListener(void (*listener)(char));
    static void addKeyUpListener(void (*listener)(char));
    static void addLongPressListener(void (*listener)(char));
    static void addMultipleKeyListener(void (*listener)(String));
    static void setType(KeypadTypes type);
    static KeypadTypes getType();
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
    static KeypadTypes keypad_type;
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