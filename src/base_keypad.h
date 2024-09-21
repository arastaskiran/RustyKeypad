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
    /** Keypad for RKP_INTEGER input. */
    RKP_INTEGER,

    /** Keypad for floating-point input. */
    RKP_FLOAT,

    /** Keypad for RKP_T9 text input. */
    RKP_T9

} KeypadTypes;

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
        const uint8_t row_pins[MAX_KEYPAD_MATRIX_SIZE],
        const uint8_t col_pins[MAX_KEYPAD_MATRIX_SIZE],
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
     * @brief Sets the state for using stored text from key presses.
     *
     * This static function allows you to enable or disable the storage of characters pressed on the keyboard
     * in a `String` variable. When enabled, the input will be recorded up to the limit defined by
     * `max_text_length`.
     *
     * @param state A boolean value indicating whether to use stored text (true) or not (false).
     */
    static void setStoredText(bool state);

    /**
     * @brief Sets the maximum length for the stored text.
     *
     * This static function allows you to define the maximum number of characters that can be stored
     * when using the stored text feature. The length is specified by the `len` parameter.
     *
     * @param len The maximum number of characters to allow for stored text. Should be a value greater than 0.
     */
    static void setMaxTextLength(uint8_t len);

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
     * even if the key is still held down. This feature does not function in RKP_T9 mode.
     *
     * - The value of `keydown_timeout` must be greater than `long_press_duration`.
     *
     * @note The value is specified in milliseconds and is used to manage prolonged key presses in non-RKP_T9 modes.
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
     * @brief Defines the duration for cycling through RKP_T9 characters, in milliseconds.
     *
     * This static variable sets the time (in milliseconds) for how long a key must be held down
     * to cycle through its assigned characters in RKP_T9 mode. For example, if the '1' key is assigned
     * '1.,?!', holding the key will cycle through these characters based on the `t9_duration`.
     *
     * - The value of `t9_duration` must be smaller than both `keydown_timeout` and `long_press_duration`.
     *
     * @note The value is specified in milliseconds, and it determines how fast you can switch
     * between characters when the keypad is in RKP_T9 mode.
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
     * @brief Registers a listener for text changes.
     *
     * This static function allows you to register a callback function that will be triggered
     * whenever there is a change in the text. The callback function should accept a `String`
     * parameter representing the updated text.
     *
     * @param listener A pointer to the function that will handle text change events.
     *                 The function must take a `String` argument representing the updated text.
     *
     * @example
     * void onTextChange(String newText) {
     *     // Handle the updated text
     *     Serial.println(newText);
     * }
     *
     * addTextChangeListener(onTextChange);
     */
    static void addTextChangeListener(void (*listener)(String));

    /**
     * @brief Registers a listener for the enter key press event.
     *
     * This static function allows you to register a callback function that will be triggered
     * when the enter key is pressed. The callback function should accept a `String` parameter
     * representing the data or text entered before the enter key was pressed.
     *
     * @param listener  A pointer to the function that will handle the enter key press event.
     *                  The function must take a `String` argument representing the data entered.
     *
     * @example
     * void onEnterPress(String data) {
     *     // Handle enter key press event
     *     Serial.println(data);
     * }
     *
     * addEnterActionListener(onEnterPress);
     */
    static void addEnterActionListener(void (*listener)(String));

    /**
     * @brief Registers a listener for the Delete key action.
     *
     * This static function allows you to register a callback function that will be triggered
     * when the Delete key is pressed. The callback function should accept a `char` parameter
     * representing the character associated with the Delete action.
     *
     * @param listener A pointer to the function that will handle the Delete key action.
     *                 The function must take a `char` argument representing the Delete key.
     *
     * @example
     * void onDeletePressed(char key) {
     *     // Handle the Delete key press
     *     Serial.println(key);
     * }
     *
     * addDeleteActionListener(onDeletePressed);
     */
    static void addDeleteActionListener(void (*listener)(char));

    /**
     * @brief Sets the type of the keypad.
     *
     * This static function configures the keypad to operate in a specific mode, as defined by the
     * `KeypadTypes` enumeration. The type determines the functionality and behavior of the keypad.
     *
     * @param type  The type of the keypad, specified using the `KeypadTypes` enumeration.
     *              Possible values include `RKP_INTEGER`, `RKP_FLOAT`, and `RKP_T9`.
     *
     * @example
     * setType(RKP_INTEGER);  // Configures the keypad for RKP_INTEGER input
     */
    static void setType(KeypadTypes type);

    /**
     * @brief Retrieves the current type of the keypad.
     *
     * This static function returns the current configuration type of the keypad, as defined by the
     * `KeypadTypes` enumeration. It indicates which mode the keypad is operating in.
     *
     * @return The type of the keypad, specified using the `KeypadTypes` enumeration.
     *         Possible values include `RKP_INTEGER`, `RKP_FLOAT`, and `RKP_T9`.
     *
     * @example
     * KeypadTypes currentType = getType();
     * if (currentType == RKP_FLOAT) {
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

    /**
     * @brief Checks if the given key is the designated delete key.
     *
     * This function returns `true` if the provided key matches the key currently assigned
     * as the delete key. It allows the system to verify whether the specified key
     * is used for delete operations.
     *
     * @param key The key to check.
     * @return bool `true` if the provided key is the delete key, `false` otherwise.
     */
    static bool isDeleteKey(char key);

    /**
     * @brief Checks if the given key is assigned as the enter key.
     *
     * This static function verifies whether the specified key matches the assigned
     * enter key. It returns true if the key is the designated enter key, and false
     * otherwise.
     *
     * @param key The character to check against the enter key.
     * @return true If the provided key is the enter key; false otherwise.
     *
     * @note This function can be useful for determining if a specific key press
     * corresponds to the enter key within the keypad logic.
     */
    static bool isEnterKey(char key);

    /**
     * @brief Assigns a specific key as the enter key.
     *
     * This static function allows you to designate a specific key as the enter key
     * for the keypad. If the provided key represents multiple characters, only the
     * first character will be set as the enter key. This updates the `enter_key`
     * variable and sets `has_enter_key` to true.
     *
     * @param key The character representing the key to be assigned as the enter key.
     *
     * @note Ensure that the provided key is valid and corresponds to an actual key
     * on the keypad.
     */
    static void setEnterKey(char key);

    /**
     * @brief Assigns a key to be used as the delete key on the keyboard.
     *
     * This function designates a specific key to act as the delete key. Since each key
     * can represent multiple characters, the first character of the key is passed to
     * this method. When the assigned delete key is held down, it will remove one character
     * at a time from the end of the text input.
     *
     * @param key The first character of the key to be used as the delete key.
     */
    static void useDeleteKey(char key);

    /**
     * @brief Disables the delete key functionality.
     *
     * This function deactivates the delete key feature, removing any previously assigned
     * key from being used for delete operations. Once this function is called, no key will
     * act as the delete key until a new one is assigned.
     */
    static void ignoreDeleteKey();

    /**
     * @brief Disables the enter key functionality.
     *
     * This static function deactivates the functionality of the assigned enter key,
     * effectively ignoring any actions associated with it. After calling this function,
     * the enter key will no longer trigger its intended behavior until re-enabled.
     *
     * @note This function is useful in scenarios where you want to temporarily
     * disable the enter key, for example, during specific input modes or processes.
     */
    static void ignoreEnterKey();

    /**
     * @brief Returns the current text entered on the keypad.
     *
     * This static function retrieves the current string of characters entered on the keypad.
     * If the password mask is active, the string is returned with masked characters (e.g., '*')
     * instead of the actual input to protect sensitive information.
     *
     * @return A `String` representing the current keypad input. If the password mask is active,
     *         the string is returned with '*' characters.
     */
    static String getKeypadData();

    /**
     * @brief Compares the current keypad input with a specified string.
     *
     * This static function allows you to compare the text entered on the keypad with a given reference string.
     * It can be used, for example, to check if the entered text matches a password or other reference value.
     *
     * @param text The `String` to compare with the current keypad input.
     * @return true if the entered keypad input matches the provided text, otherwise false.
     */
    static bool isKeypadEqual(String text);

    /**
     * @brief Checks if password masking is enabled.
     *
     * This static function returns whether password masking is currently enabled for keypad input.
     * When password masking is enabled, characters entered on the keypad will be displayed as '*'
     * instead of the actual characters to protect sensitive information.
     *
     * @return true if password masking is enabled, otherwise false.
     */
    static bool hasPasswordMask();

    /**
     * @brief Checks if an enter key has been assigned.
     *
     * This static function returns a boolean indicating whether a specific key
     * has been designated as the enter key. It returns true if an enter key is
     * assigned and false otherwise.
     *
     * @return true If an enter key has been assigned; false if not.
     *
     * @note This function can be useful for determining if the keypad is configured
     * to recognize an enter key, affecting how key presses are handled.
     */
    static bool hasEnterKey();

    /**
     * @brief Sets the password masking state for keypad input.
     *
     * This static function allows you to enable or disable password masking for characters entered
     * on the keypad. When enabled, the characters will be masked (e.g., displayed as '*' characters)
     * to protect sensitive information such as passwords.
     *
     * @param state A boolean value where `true` enables password masking and `false` disables it.
     */
    static void setPasswordMask(bool state);

    /**
     * @brief Enables the buzzer on the specified pin with a default beep duration.
     *
     * This static function configures the buzzer to operate on a given GPIO pin. It activates the buzzer
     * and sets the duration for which it will sound. The default beep duration is set to 50 milliseconds,
     * but it can be overridden by providing a different value.
     *
     * @param pin The GPIO pin number where the buzzer is connected.
     * @param beep_duration The duration (in milliseconds) for which the buzzer should sound.
     *                      Default is 50 ms if not specified.
     *
     * @note Ensure the specified pin is correctly initialized as an output before calling this function.
     */
    static void enableBuzzer(uint8_t pin, unsigned long beep_duration = 50);

    /**
     * @brief Disables the buzzer.
     *
     * This static function turns off the buzzer if it is currently active. It stops any ongoing sound
     * and sets the buzzer state to inactive. This is useful for managing the buzzer's operation
     * based on specific events or conditions within the system.
     *
     * @note Ensure that this function is called when the buzzer is no longer needed to avoid
     * unnecessary power consumption or unwanted sound.
     */
    static void disableBuzzer();

    /**
     * @brief Beeps the buzzer a specified number of times.
     *
     * This static function activates the buzzer for a given number of beeps. If the specified
     * `beep_duration` is zero, it uses the previously set duration. If a new count is provided,
     * it overrides the previous beep count. The function returns `false` if the buzzer is currently
     * busy and cannot perform the operation; otherwise, it returns `true`.
     *
     * @param count The number of times to beep the buzzer.
     * @param beep_duration The duration for each beep in milliseconds. If set to zero, the last
     *                      used duration is applied.
     *
     * @return A boolean value:
     *         - `true` if the operation was successful and the buzzer is now beeping,
     *         - `false` if the buzzer was busy and the operation could not be performed.
     */
    static bool beepBuzzer(uint8_t count, unsigned long beep_duration = 0UL);

protected:
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
     * @brief Pointer to the function handling text change events.
     *
     * This static variable holds a pointer to a function that will be called whenever there is a change
     * in the text. The function should accept a `String` parameter representing the updated text.
     *
     * @note This function pointer is used by the `addTextChangeListener` method to register a text
     * change event handler.
     */
    static void (*textChangeListener)(String);

    /**
     * @brief Pointer to the function handling the enter key event.
     *
     * This static variable holds a pointer to a function that will be called when
     * the enter key is pressed. The function should accept a `String` parameter
     * representing the data or text entered before the enter key was pressed.
     *
     * @note This function pointer is used by the `addEnterActionListener` method
     * to register a callback that responds to the enter key event.
     *
     * @example
     * void onEnterPress(String data) {
     *     // Handle the enter key press event
     *     Serial.println(data);
     * }
     *
     * addEnterActionListener(onEnterPress);
     */
    static void (*onEnterListener)(String);

    /**
     * @brief Pointer to the function handling the Delete key action.
     *
     * This static variable holds a pointer to a function that will be called when the Delete key is pressed.
     * The function should accept a `char` parameter representing the character associated with the Delete action.
     *
     * @note This function pointer is used by the `addDeleteActionListener` method to register a Delete key
     * action handler.
     */
    static void (*onDeleteListener)(char);

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

    /**
     * @brief Checks if a key is currently pressed in RKP_T9 mode.
     *
     * This function returns `true` if a key is still being pressed in RKP_T9 mode,
     * preventing multiple key presses from being processed simultaneously.
     * It ensures that no other key inputs are considered until the current
     * key is released, enforcing single key press behavior in RKP_T9 mode.
     *
     * @return bool `true` if a key is currently pressed, `false` otherwise.
     */
    static bool hasWaitKey();

    /**
     * @brief Verifies if the scanned key is different from the currently pressed key in RKP_T9 mode.
     *
     * In RKP_T9 mode, this function checks whether the provided key is different from the key
     * that is currently being pressed. If the scanned key is not the one currently pressed,
     * it returns `true`. This can be used in an iteration to skip to the next key.
     *
     * @param key A pointer to the `RustyKey` object to compare against the current key.
     * @return bool `true` if the scanned key is different from the currently pressed key, `false` otherwise.
     */
    static bool checkWaitKey(RustyKey *key);

    /**
     * @brief Sets the currently pressed key in RKP_T9 mode to block other key scans.
     *
     * This function assigns the provided key as the currently pressed key in RKP_T9 mode.
     * It prevents other keys from being scanned until the current key is released.
     * Use this function to track the key being pressed and to ensure that no multiple
     * key inputs are processed simultaneously in RKP_T9 mode.
     *
     * @param key A pointer to the `RustyKey` object representing the key being pressed.
     */
    static void setWaitKey(RustyKey *key);

    /**
     * @brief Releases the key blocking caused by RKP_T9 mode.
     *
     * This function clears the currently pressed key in RKP_T9 mode, allowing other keys
     * to be scanned again. It effectively resets the state by releasing the key that
     * was blocking further input due to the RKP_T9 mode's single key press restriction.
     */
    static void resetWaitKey();

    /**
     * @brief Checks if a delete key is currently assigned.
     *
     * This function returns `true` if a key has been set to act as the delete key on the keyboard.
     * It helps to determine whether any key is currently being used for delete operations.
     *
     * @return bool `true` if a delete key is assigned, `false` otherwise.
     */
    static bool hasDeleteKey();

    /**
     * @brief Retrieves the delete key character.
     *
     * This static function returns a copy of the character that is set as the delete key.
     * The returned value is const, preventing modification to the original delete key.
     *
     * @return char A copy of the delete key character.
     */
    static char getDeleteKey();

    /**
     * @brief Appends a character to the `keypad_data` at the current cursor position.
     *
     * This static function adds the character entered from the keypad to the `keypad_data` string
     * at the position specified by `keypad_data_cursor`. The cursor is automatically updated after the
     * character is inserted. This method is typically triggered by the `RKP_KEY_UP` event, indicating that
     * a key has been released.
     *
     * @param key The character to be appended to `keypad_data`.
     *
     * @note The cursor position (`keypad_data_cursor`) is incremented after the key is appended.
     */
    static void appendKey(char key);

    /**
     * @brief Deletes a character from the text based on the cursor position.
     *
     * This function removes a character from the text input at the current cursor position.
     * It adjusts the text accordingly, ensuring that the remaining characters are
     * correctly repositioned after the deletion. This function is typically used
     * in conjunction with cursor navigation to manage text editing operations.
     */
    static void deleteChar();

    /**
     * @brief Sets the state of the buzzer.
     *
     * This static function allows you to enable or disable the buzzer by changing its state.
     * When `state` is set to `true`, the buzzer will be activated, and when set to `false`,
     * the buzzer will be turned off.
     *
     * @param state A boolean value indicating the desired state of the buzzer.
     *              - `true` to activate the buzzer
     *              - `false` to deactivate the buzzer
     *
     * @note Ensure that the buzzer pin is properly configured before calling this function.
     */
    static void setBuzzerState(bool state);

    /**
     * @brief Manages the buzzer state and behavior.
     *
     * This static function is responsible for checking the current state of the buzzer
     * and managing its activation and deactivation based on the set conditions.
     * It handles the timing for beeping, including checking if the beep duration has
     * expired and whether to silence the buzzer if the beep count has reached zero.
     *
     * @note This method should be called regularly within the main loop to ensure
     * that the buzzer operates as expected.
     */
    static void checkBuzzer();

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
     * It determines the behavior and mode of the keypad, such as `RKP_INTEGER`, `RKP_FLOAT`, or `RKP_T9`.
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

    /**
     * @brief A static constant 2D array representing the factory keypad layout.
     *
     * This array defines the default key mappings for the keypad interface,
     * with each entry corresponding to a specific key configuration.
     * As a static member, it ensures consistent access across all instances
     * of the class.
     */
    static const char *keypadFactoryMap[MAX_KEYPAD_MATRIX_SIZE][MAX_KEYPAD_MATRIX_SIZE];

    /**
     * @brief Holds the last key pressed in RKP_T9 mode.
     *
     * In RKP_T9 mode, multiple key presses are not allowed. This variable stores
     * the reference to the last key that was pressed and prevents any other
     * key detection until the current key is released.
     * It ensures that only one key is processed at a time,
     * maintaining the integrity of input during typing.
     */
    static RustyKey *waitKey;

    /**
     * @brief Indicates whether a delete key has been set.
     *
     * This variable is used to track if a specific key has been designated as the delete key.
     * It is set to `true` if a delete key has been defined, allowing the system to recognize
     * and handle delete operations. If no delete key has been assigned, this will remain `false`.
     */
    static bool has_delete_key;

    /**
     * @brief Stores the designated delete key.
     *
     * This variable holds the key that has been assigned as the delete key.
     * If a specific key has been set to perform delete operations, its value
     * is stored here. It allows the system to recognize which key is used
     * for deleting inputs.
     */
    static char delete_key;

    /**
     * @brief Maximum length of text input from the keypad.
     *
     * This variable defines the maximum number of characters that can be inputted
     * from the keypad. The default length is set to 20 characters. This limit
     * helps to ensure that the text input remains manageable and avoids buffer overflow.
     */
    static uint8_t max_text_length;

    /**
     * @brief Indicates whether to use the stored text from key presses.
     *
     * This static variable holds a boolean value that determines if the characters pressed on the keyboard
     * should be stored in a `String` variable. This functionality can simplify operations by maintaining a
     * record of the input.
     *
     * The stored text is limited to the number of characters defined by `max_text_length`.
     */
    static bool use_stored_text;

    /**
     * @brief Enables or disables password masking for keypad input.
     *
     * This static boolean variable controls whether the characters entered on the keypad are masked
     * (e.g., shown as '*' characters) to hide sensitive information such as passwords. When enabled,
     * the entered text will not be displayed directly, but as masked characters.
     *
     * @note This is useful when implementing secure input for passwords or PINs.
     */
    static bool use_password_mask;

    /**
     * @brief Indicates whether an enter key has been assigned.
     *
     * This static variable holds a boolean value that signifies if an enter key has
     * been set. If true, it means a specific key has been designated as the enter key.
     * If false, no enter key has been assigned.
     *
     * @note This variable can be used in conjunction with the `setEnterKey` function
     * to check the status of the enter key assignment.
     */
    static bool has_enter_key;

    /**
     * @brief Represents the designated enter key.
     *
     * This static variable holds the character associated with the enter key. You can assign
     * a specific key as the enter key, and if that key represents multiple characters,
     * only the first character will be stored in this variable.
     *
     * @note Make sure to set this variable using the `setEnterKey` function to ensure
     * that it accurately reflects the intended enter key.
     */
    static char enter_key;

    /**
     * @brief Static variable representing the pin connected to the buzzer.
     *
     * This static variable holds the GPIO pin number that is assigned to control the buzzer.
     * Being static, it is shared across all instances of the class, meaning it doesn't belong to
     * any specific instance of the class but to the class itself.
     *
     * The pin number should be set using the appropriate method before any operations involving the buzzer.
     *
     * @note The pin must be correctly initialized and configured for output to properly control the buzzer.
     */
    static uint8_t buzzer_pin;

    /**
     * @brief Static flag to enable or disable the buzzer functionality.
     *
     * This static boolean variable determines whether the buzzer feature is active or not.
     * When set to `true`, the system will allow the use of the buzzer to provide audible feedback.
     * When set to `false`, the buzzer will be disabled, and no sound will be triggered.
     *
     * This variable is shared across all instances of the class and controls the global behavior
     * of the buzzer.
     *
     * @note Ensure the `buzzer_pin` is properly set before enabling this feature.
     */
    static bool use_buzzer;

    /**
     * @brief Static variable to indicate the current state of the buzzer.
     *
     * This static boolean variable shows whether the buzzer is currently sounding (true) or silent (false).
     * It is used to track if the buzzer is active or inactive at any given moment.
     *
     * This variable helps manage the buzzer's operation within the system and can be used
     * to ensure that the buzzer is only activated when necessary.
     */
    static bool buzzer_state;

    /**
     * @brief Static variable to store the timestamp of the last buzzer activation.
     *
     * This static unsigned long variable keeps track of the time (in milliseconds) when the buzzer
     * was last activated. It can be used to implement timing logic, such as preventing the buzzer
     * from sounding continuously or for a specified duration.
     *
     * This variable is essential for managing the buzzer's behavior in relation to time-sensitive actions,
     * allowing for more controlled and efficient use of the buzzer.
     */
    static unsigned long last_buzzer_activate_ts;

    /**
     * @brief Static variable to define the duration of the buzzer beep.
     *
     * This static unsigned long variable specifies the length of time (in milliseconds) that the buzzer
     * should sound when activated. It allows for customization of the beep duration, enabling various
     * auditory feedback patterns in the system.
     *
     * This variable is crucial for ensuring consistent and controlled buzzer behavior, making it easier
     * to manage user notifications or alerts based on time intervals.
     */
    static unsigned long buzzer_beep_duration;

    /**
     * @brief Checks if the beep duration for the buzzer has elapsed.
     *
     * This static function compares the current time against the last activation timestamp
     * of the buzzer to determine if the specified beep duration has passed. It returns `true`
     * if the duration has exceeded, indicating that the buzzer can be activated again or
     * that the previous beep has completed.
     *
     * @return A boolean value:
     *         - `true` if the beep duration is over,
     *         - `false` if the beep duration is still active.
     */
    static bool isBeepDurationOver();

    /**
     * @brief Counts the number of beeps to determine when to silence the buzzer.
     *
     * This static variable holds the count of how many times the buzzer is allowed to beep
     * before it silences. Each time the buzzer beeps, this count is decremented. When the
     * count reaches zero, the buzzer will be turned off.
     *
     * @note Ensure to decrement this count each time the buzzer beeps. Once it reaches zero,
     * the buzzer should be disabled to prevent further sounds until the count is reset.
     */
    static uint8_t buzzer_beep_count;
};
#endif