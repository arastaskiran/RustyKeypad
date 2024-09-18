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

    /**
     * @brief Enables the keypad functionality.
     *
     * This static function activates or enables the keypad, allowing it to start detecting and processing
     * key presses. It is typically called after the keypad has been set up.
     *
     * @note Call this function to begin listening for key events.
     */
    static void enable();

    /**
     * @brief Disables the keypad functionality.
     *
     * This static function deactivates the keypad, stopping it from detecting and processing
     * any further key presses. It is useful when you want to temporarily halt keypad operations.
     *
     * @note Call this function to stop listening for key events.
     */
    static void disable();

    /**
     * @brief Specifies the mode for keypad pins.
     *
     * This static variable defines the input mode for the keypad's row and column pins. It can be set to either
     * `INPUT_PULLUP` or `INPUT`, determining how the GPIO pins behave during keypad scanning.
     *
     * - `INPUT_PULLUP`: Enables internal pull-up resistors, useful for detecting button presses in an open-circuit configuration.
     * - `INPUT`: Standard input mode without internal pull-up resistors.
     *
     * @note Ensure to set this variable appropriately based on your circuit design.
     */
    static uint8_t pins_mode;

    /**
     * @brief Defines the timeout duration for key press, in milliseconds.
     *
     * This static variable sets a timeout duration (in milliseconds) for a key being held down.
     * If a key is pressed longer than this duration, it simulates a key release followed by a new key press,
     * even if the key is still held down. This feature does not function in T9 mode.
     *
     * - The value of `keydown_timeout` must be greater than `long_press_duration`.
     *
     * @note The value is specified in milliseconds and is used to manage prolonged key presses in non-T9 modes.
     */
    static unsigned long keydown_timeout;

    /**
     * @brief Defines the duration for a long key press, in milliseconds.
     *
     * This static variable specifies the minimum time (in milliseconds) that a key must be held down
     * to be considered a "long press." If the key is held for longer than this duration, it triggers
     * a long press event.
     *
     * @note The value is in milliseconds, and it should be less than `keydown_timeout` for proper functionality.
     */
    static unsigned long long_press_duration;

    /**
     * @brief Defines the duration for cycling through T9 characters, in milliseconds.
     *
     * This static variable sets the time (in milliseconds) for how long a key must be held down
     * to cycle through its assigned characters in T9 mode. For example, if the '1' key is assigned
     * '1.,?!', holding the key will cycle through these characters based on the `t9_duration`.
     *
     * - The value of `t9_duration` must be smaller than both `keydown_timeout` and `long_press_duration`.
     *
     * @note The value is specified in milliseconds, and it determines how fast you can switch
     * between characters when the keypad is in T9 mode.
     */
    static unsigned long t9_duration;

    /**
     * @brief Registers a listener for key down events.
     *
     * This static function allows you to register a callback function that will be triggered whenever
     * a key is pressed down. The callback function should accept a `char` parameter, which represents
     * the key that was pressed.
     *
     * @param listener  A pointer to the function that will handle key down events. The function must
     *                  take a `char` argument representing the key pressed.
     *
     * @example
     * void onKeyDown(char key) {
     *     // Handle key down event
     *     Serial.println(key);
     * }
     *
     * addKeyDownListener(onKeyDown);
     */
    static void addKeyDownListener(void (*listener)(char));

    /**
     * @brief Registers a listener for key up events.
     *
     * This static function allows you to register a callback function that will be triggered whenever
     * a key is released (key up event). The callback function should accept a `char` parameter,
     * which represents the key that was released.
     *
     * @param listener  A pointer to the function that will handle key up events. The function must
     *                  take a `char` argument representing the key released.
     *
     * @example
     * void onKeyUp(char key) {
     *     // Handle key up event
     *     Serial.println(key);
     * }
     *
     * addKeyUpListener(onKeyUp);
     */
    static void addKeyUpListener(void (*listener)(char));

    /**
     * @brief Registers a listener for long press events.
     *
     * This static function allows you to register a callback function that will be triggered whenever
     * a key is held down for longer than the `long_press_duration`. The callback function should accept
     * a `char` parameter, which represents the key that was held down.
     *
     * @param listener  A pointer to the function that will handle long press events. The function must
     *                  take a `char` argument representing the key that triggered the long press event.
     *
     * @example
     * void onLongPress(char key) {
     *     // Handle long press event
     *     Serial.println(key);
     * }
     *
     * addLongPressListener(onLongPress);
     */
    static void addLongPressListener(void (*listener)(char));

    /**
     * @brief Registers a listener for multiple key events.
     *
     * This static function allows you to register a callback function that will be triggered when
     * multiple keys are pressed in sequence. The callback function should accept a `String` parameter
     * representing the sequence of keys pressed.
     *
     * @param listener  A pointer to the function that will handle multiple key events. The function must
     *                  take a `String` argument representing the sequence of keys pressed.
     *
     * @example
     * void onMultipleKeyPress(String keys) {
     *     // Handle sequence of key presses
     *     Serial.println(keys);
     * }
     *
     * addMultipleKeyListener(onMultipleKeyPress);
     */
    static void addMultipleKeyListener(void (*listener)(String));

    /**
     * @brief Sets the type of the keypad.
     *
     * This static function configures the keypad to operate in a specific mode, as defined by the
     * `KeypadTypes` enumeration. The type determines the functionality and behavior of the keypad.
     *
     * @param type  The type of the keypad, specified using the `KeypadTypes` enumeration.
     *              Possible values include `INTEGER`, `FLOAT`, and `T9`.
     *
     * @example
     * setType(INTEGER);  // Configures the keypad for integer input
     */
    static void setType(KeypadTypes type);

    /**
     * @brief Retrieves the current type of the keypad.
     *
     * This static function returns the current configuration type of the keypad, as defined by the
     * `KeypadTypes` enumeration. It indicates which mode the keypad is operating in.
     *
     * @return The type of the keypad, specified using the `KeypadTypes` enumeration.
     *         Possible values include `INTEGER`, `FLOAT`, and `T9`.
     *
     * @example
     * KeypadTypes currentType = getType();
     * if (currentType == FLOAT) {
     *     // Keypad is configured for floating-point input
     * }
     */
    static KeypadTypes getType();

    /**
     * @brief Checks if the keypad is currently enabled.
     *
     * This static function returns a boolean value indicating whether the keypad functionality is
     * currently active and operational.
     *
     * @return `true` if the keypad is enabled and actively processing key events; `false` otherwise.
     *
     * @example
     * if (isEnabled()) {
     *     // Keypad is enabled
     * } else {
     *     // Keypad is not enabled
     * }
     */
    static bool isEnabled();

protected:
    /**
     * @brief Resets the keypad to its default state.
     *
     * This static function performs a complete reset of the keypad system by:
     * - Clearing any interrupts that might be pending.
     * - Clearing the text or input that has been entered via the keypad.
     * - Resetting all registered event handlers to their initial state.
     *
     * This ensures that the keypad is returned to a clean state, ready for a fresh setup or
     * usage without any residual data or settings.
     *
     * @note After calling this function, the keypad may need to be reconfigured.
     *
     * @example
     * reset();  // Clears interrupts, clears entered text, and resets all event handlers
     */
    static void reset();

    /**
     * @brief Clears the text entered from the keypad.
     *
     * This static function resets the variable that holds the text or input entered via the keypad,
     * effectively clearing all currently stored key presses or text.
     *
     * @note This function is useful for starting a new input session or removing any previously
     *       entered text from the display or internal buffer.
     *
     * @example
     * clearScreen();  // Resets the text entered from the keypad
     */
    static void clearScreen();

    /**
     * @brief Linked list of `RustyKey` objects.
     *
     * This static variable represents a linked list that stores objects of the `RustyKey` class.
     * It is used to manage and access the keypad keys in a structured manner.
     *
     * @note Ensure proper management of this linked list to avoid memory leaks or access issues.
     */
    static RustyKeyList *KeyList;

    /**
     * @brief Configures the keypad with factory default settings.
     *
     * This static function sets up the keypad using predefined factory settings. It initializes the
     * keypad matrix with a standard character map, defines the number of rows and columns, and configures
     * the pin modes. The default configuration is set as follows:
     *
     * - Keypad matrix map:
     *   - Row 0: {"1.,?!'\"-()@/:_"}
     *   - Row 1: {"2ABCabc"}
     *   - Row 2: {"3DEFdef"}
     *   - Row 3: {"4GHIghiİ"}
     *   - Row 4: {"5JKLjkl"}
     *   - Row 5: {"6MNOmnoÖö"}
     *   - Row 6: {"7PQRSpqrsŞş"}
     *   - Row 7: {"8TUVtuvÜü"}
     *   - Row 8: {"9WXYZwxyz"}
     *   - Row 9: {"*"}
     *   - Row 10: {"0 +"}
     *   - Row 11: {"#"}
     *
     * - Number of rows: 4
     * - Number of columns: 3
     * - Pin mode: INPUT_PULLUP
     *
     * This method calls `keyboardSetup` with the above parameters to apply the factory settings to the keypad.
     *
     * @note This function is typically used to restore the keypad to its default configuration or initialize
     *       it for the first time.
     */
    static void setFactoryConfig();

    /**
     * @brief Pointer to the function handling key down events.
     *
     * This static variable holds a pointer to a function that will be called whenever a key is pressed down.
     * The function should accept a `char` parameter representing the key that was pressed.
     *
     * @note This function pointer is used by the `addKeyDownListener` method to register a key down event handler.
     */
    static void (*keyDownListener)(char);

    /**
     * @brief Pointer to the function handling key up events.
     *
     * This static variable holds a pointer to a function that will be called whenever a key is released.
     * The function should accept a `char` parameter representing the key that was released.
     *
     * @note This function pointer is used by the `addKeyUpListener` method to register a key up event handler.
     */
    static void (*keyUpListener)(char);

    /**
     * @brief Pointer to the function handling long press events.
     *
     * This static variable holds a pointer to a function that will be called when a key is held down for longer
     * than the defined long press duration. The function should accept a `char` parameter representing the key
     * that triggered the long press event.
     *
     * @note This function pointer is used by the `addLongPressListener` method to register a long press event handler.
     */
    static void (*longPressListener)(char);

    /**
     * @brief Pointer to the function handling multiple key events.
     *
     * This static variable holds a pointer to a function that will be called when multiple keys are pressed in
     * sequence. The function should accept a `String` parameter representing the sequence of keys pressed.
     *
     * @note This function pointer is used by the `addMultipleKeyListener` method to register a multiple key event handler.
     */
    static void (*multipleKeyListener)(String);

    /**
     * @brief Indicates whether an interrupt has occurred.
     *
     * This static boolean variable tracks whether an interrupt has been triggered by certain keys, such as
     * the Enter key. It is used to determine if an interrupt event has occurred and can be utilized to manage
     * the state of the keypad or related operations.
     *
     * @note The variable is set to `true` when an interrupt is triggered and `false` otherwise.
     */
    static bool interrupted;

private:
    /**
     * @brief Stores the number of rows in the keypad matrix.
     *
     * This static variable holds the size of the rows for the keypad matrix. It defines how many rows
     * are configured for the keypad layout.
     */
    static uint8_t row_size;

    /**
     * @brief Stores the number of columns in the keypad matrix.
     *
     * This static variable holds the size of the columns for the keypad matrix. It defines how many columns
     * are configured for the keypad layout.
     */
    static uint8_t col_size;

    /**
     * @brief Character used for floating-point input in float mode.
     *
     * This static variable stores the character used to insert a floating-point symbol (e.g., a decimal point)
     * when the keypad is in float mode. By default, the `'#'` key is assigned to act as the floating-point input.
     *
     * @note This character can be changed if needed, but the default value is set to `'#'`.
     */
    static char float_char;

    /**
     * @brief Holds the current type of the keypad.
     *
     * This static variable stores the type of the keypad as defined by the `KeypadTypes` enumeration.
     * It determines the behavior and mode of the keypad, such as `INTEGER`, `FLOAT`, or `T9`.
     */
    static KeypadTypes keypad_type;

    /**
     * @brief Indicates whether the keypad is enabled.
     *
     * This static boolean variable tracks whether the keypad is currently enabled.
     * If `true`, the keypad is active and ready for input; if `false`, it is disabled.
     */
    static bool enabled;

    /**
     * @brief Holds the text generated from keypad input.
     *
     * This static variable stores the string of characters entered via the keypad. It accumulates the
     * characters as keys are pressed, allowing you to capture and work with the complete input generated
     * from the keypad.
     *
     * @note The content of this variable represents the current input session and can be reset or modified
     *       as needed.
     */
    static String keypad_data;

    /**
     * @brief Tracks the position for the next character in the keypad input.
     *
     * This static variable holds the cursor position where the next character will be added in the `keypad_data` string.
     * Each time a key is pressed, the cursor is incremented by one to point to the next position. This position
     * can also be controlled externally to modify where the next character will be inserted.
     *
     * @note This allows you to track and manipulate the insertion point within the current input session.
     */
    static unsigned int keypad_data_cursor;

    /**
     * @brief Timeout duration for triggering the IDLE event, in milliseconds.
     *
     * This static variable defines the duration of inactivity (in milliseconds) after which the keypad will
     * trigger an IDLE event. The system compares the current time with the timestamp stored in `last_activity_ts`.
     * If the time difference exceeds `idle_timeout`, the keypad is considered idle, and the IDLE event is raised.
     *
     * @note The timeout is checked against `last_activity_ts`, which tracks the time of the last keypad activity.
     */
    static unsigned long idle_timeout;

    /**
     * @brief Stores the timestamp of the last keypad activity in milliseconds.
     *
     * This static variable holds the time of the most recent keypad interaction, recorded in milliseconds.
     * It tracks when the last key was pressed or an action occurred on the keypad, allowing the system to
     * monitor inactivity or trigger time-based events.
     *
     * @note The timestamp is based on the system clock and is updated with each keypad action.
     */
    static unsigned long last_activity_ts;

    /**
     * @brief Appends a character to the `keypad_data` at the current cursor position.
     *
     * This static function adds the character entered from the keypad to the `keypad_data` string
     * at the position specified by `keypad_data_cursor`. The cursor is automatically updated after the
     * character is inserted. This method is typically triggered by the `KEY_UP` event, indicating that
     * a key has been released.
     *
     * @param key The character to be appended to `keypad_data`.
     *
     * @note The cursor position (`keypad_data_cursor`) is incremented after the key is appended.
     */
    static void appendKey(char key);

    /**
     * @brief Holds the digital output pins used to drive the keypad rows.
     *
     * This static pointer stores the array of digital output pins that are used to control the rows
     * of the keypad during its operation. These pins are responsible for sending signals to the keypad rows
     * and are essential for scanning the keypad matrix.
     *
     * @note The pins are configured as outputs and are used in the keypad scanning process.
     */
    static uint8_t *row_out_pins;

    /**
     * @brief Resizes the array of row output pins to match the current configuration.
     *
     * This static function adjusts the size of the `row_out_pins` array based on the specified size.
     * While `row_out_pins` is initially allocated with a size defined by `MAX_KEYPAD_MATRIX_SIZE`,
     * if the actual number of rows in the keypad configuration is less than this maximum,
     * this function will resize the array to save memory.
     *
     * @param size The new size for the `row_out_pins` array, reflecting the number of row pins required.
     *
     * @note This function is used to optimize memory usage by resizing the array according to the actual
     *       keypad configuration rather than using the maximum predefined size.
     */
    static void resizeRowPins(size_t size);
};
#endif