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
    RKP_KEY_IDLE,

    /** The key has just been pressed down. */
    RKP_KEY_DOWN,

    /** The key has been released. */
    RKP_KEY_UP,

    /** The key is held down for a long press. */
    RKP_LONG_PRESS,

    /** The key is RKP_WAITing for the next interaction. */
    RKP_WAIT,

    /** The delete key press event. */
    RKP_PRESS_DELETE,

    /** The delete key release event. */
    RKP_RELEASE_DELETE,

    /** Clears the screen, for example, when a specific key combination is pressed. */
    RKP_CLEAR_SCREEN
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

    /**
     * @brief Destructor for cleaning up the `RustyKey` object.
     *
     * Frees any resources allocated for the `RustyKey` instance.
     */
    ~RustyKey();

    /**
     * @brief Checks the current state of the key.
     *
     * Evaluates the current state of the key and determines if it meets certain conditions.
     *
     * @return True if the key meets the conditions, otherwise false.
     */
    bool check();

    /**
     * @brief Resets the state of the key.
     *
     * This method clears the `char_index` and `current_state` variables, and marks the key as IDLE.
     * It effectively resets the key to its default state, allowing for a fresh start for any key interactions.
     */
    void reset();

    /**
     * @brief Determines if the key is currently pressed.
     *
     * Checks whether the key is in a pressed state.
     *
     * @return True if the key is pressed, otherwise false.
     */
    bool isPressed();

    /**
     * @brief Disables the key functionality.
     *
     * Marks the key as inactive, preventing further interactions.
     */
    void disable();

    /**
     * @brief Enables the key functionality.
     *
     * Marks the key as active, allowing interactions to be processed.
     */
    void enable();

    /**
     * @brief Reads the current state of the key.
     *
     * This method retrieves the current state of the key, determining whether it is active or not.
     * It evaluates the key's status based on its internal logic and returns true if the key is active,
     * otherwise false.
     *
     * @return True if the key is currently active, otherwise false.
     */
    bool read();

    /**
     * @brief Retrieves the current event type of the key.
     *
     * This method returns the current event associated with the key, which can be used to determine
     * the state or action performed on the key. The event types are defined in the `KeypadEventTypes` enum
     * and may include states such as RKP_KEY_IDLE, RKP_KEY_DOWN, RKP_KEY_UP, RKP_LONG_PRESS, and RKP_WAIT.
     *
     * @return The current `KeypadEventTypes` enum value representing the key's event.
     */
    KeypadEventTypes getCurrentEvent() const;

    /**
     * @brief Gets the key code associated with this key.
     *
     * Retrieves the character or value of the key.
     *
     * @return The key code as a character.
     */
    char getKeyCode() const;

    /**
     * @brief Retrieves the first key code from the key map.
     *
     * This function returns the key code associated with the first character
     * in the key map. It provides a way to access the initial input value
     * from the keypad configuration.
     *
     * @return char The first key code from the key map.
     */
    char getFirstKeyCode() const;

    /**
     * @brief Compares the current key with another key for equality.
     *
     * This function checks if the current `RustyKey` object is equal to
     * the provided `RustyKey` pointer. Equality is determined based on
     * the relevant attributes of the keys, such as their values or properties.
     *
     * @param key A pointer to the `RustyKey` object to compare against.
     * @return bool `true` if the keys are equal, `false` otherwise.
     */
    bool isEqual(const RustyKey *key);

protected:
private:
    /**
     * @brief Timestamp of the last key activity.
     *
     * This variable stores the time (in milliseconds) when the last activity was detected for the key.
     * It is used to track the timing of key presses, releases, and other interactions. This timestamp
     * helps in managing time-based behaviors, such as detecting idle periods or handling long presses.
     */
    unsigned long last_activity_ts;

    /**
     * @brief The current event type for the key.
     *
     * This variable holds the current event associated with the key, represented by the `KeypadEventTypes` enum.
     * It indicates the key's current state or action, such as being idle, pressed down, released, long-pressed, or RKP_WAITing.
     * The event type helps in managing and responding to various key interactions during operation.
     */
    KeypadEventTypes current_event;

    /**
     * @brief The character code associated with the key.
     *
     * This variable holds the character code or string representing the key's value. It is used to identify
     * the key's output or function. For instance, if the key represents the letter 'A', `key_code` would point
     * to a string containing "A". This value is used in key handling and event processing.
     */
    const char *key_code;

    /**
     * @brief The GPIO pin number for the key's row output.
     *
     * This variable specifies the GPIO pin used for the row where the key is located. It is used to connect
     * the key's row to the microcontroller, allowing for the detection of key presses and interactions.
     * The pin number corresponds to the physical pin on the microcontroller or development board.
     */
    uint8_t row_out_pin;

    /**
     * @brief The GPIO pin number for the key's column input.
     *
     * This variable specifies the GPIO pin used for the column where the key is located. It is used to connect
     * the key's column to the microcontroller, allowing for the detection of key presses and interactions.
     * The pin number corresponds to the physical pin on the microcontroller or development board.
     */
    uint8_t col_in_pin;

    /**
     * @brief The index of the current character associated with the key.
     *
     * This variable holds the index of the character that is currently selected or active on the key.
     * In RKP_T9 mode, where each key represents multiple characters, this index tracks which character
     * is being displayed or used based on the duration of the key press. The index changes as the key
     * is held down to cycle through the available characters.
     */
    uint8_t char_index;

    /**
     * @brief Indicates whether the key is enabled or disabled.
     *
     * This variable holds a flag that determines if the key is currently active and responsive to interactions.
     * When `enabled` is true, the key can be pressed, and its events can be processed. When `enabled` is false,
     * the key is inactive and will not respond to presses or other interactions.
     */
    bool enabled;

    /**
     * @brief Activates the row pin for key scanning.
     *
     * This method sets the row digital output pin to the appropriate level based on the input configuration.
     * If the row pins are configured as `INPUT_PULLUP`, this method pulls the row pin to ground (LOW).
     * Otherwise, it sets the pin to a high state (HIGH). This activation is necessary for scanning the key matrix
     * and detecting key presses.
     */
    void rowActive();
    /**
     * @brief Deactivates the row pin for key scanning.
     *
     * This method sets the row digital output pin to a passive state based on the input configuration.
     * If the input pins are configured as `INPUT_PULLUP`, this method sets the row pin to a high state (HIGH).
     * Otherwise, it sets the pin to ground (LOW). This deactivation is essential for properly managing the
     * key matrix during scanning and detecting key presses.
     */
    void rowPassive();

    /**
     * @brief The current state of the key.
     *
     * This variable holds the current state of the key, indicating whether it is pressed or not.
     * The state is used to determine the key's interaction status and to manage the key's event processing.
     * It helps in differentiating between key being actively pressed or in its idle state.
     */
    bool current_state;

    /**
     * @brief Analyzes the current state of the key to determine the event type.
     *
     * This method determines whether the key event is a KeyUp or a LongPress when the key is released.
     * It uses the `last_activity_ts` timestamp and the `long_press_duration` to make this determination.
     * If the keyboard is configured in RKP_T9 mode, this method will always return a KeyUp event because
     * pressing and holding the key is required to cycle through the alternative characters associated with the key.
     */
    void analyzeState();

    /**
     * @brief Checks if the key press has timed out and performs actions based on the keyboard mode.
     *
     * This method determines if the key has been pressed for a duration that triggers specific actions
     * based on the current keyboard mode:
     *
     * - **RKP_T9 Mode:** If the key is held down long enough, it will advance to the next character in the
     *   sequence associated with the key. This is done by incrementing the `char_index` and triggering
     *   a `RKP_KEY_DOWN` event. The method uses `t9_duration` and `last_activity_ts` to check if the timeout
     *   threshold has been reached.
     *
     * - **Other Modes:** In standard modes, holding the key for a set duration simulates releasing and
     *   pressing the key again. When the timeout threshold is exceeded, it first triggers a `RKP_KEY_UP` event,
     *   followed by a `RKP_KEY_DOWN` event in the next loop iteration. This behavior is controlled using
     *   `keydown_timeout` and `last_activity_ts`.
     *
     * @return `true` if the timeout condition is met and actions are performed, `false` otherwise.
     */
    bool checkTimeout();

    /**
     * @brief Sets the event type for the key and resets the activity timestamp.
     *
     * This method assigns a specific event type to the key, such as `RKP_KEY_DOWN`, `RKP_KEY_UP`, `RKP_LONG_PRESS`, etc.
     * Additionally, it resets the `last_activity_ts` timestamp to the current time, marking the moment when
     * the event was set. This helps in tracking the time of the last key interaction and managing subsequent
     * key events accurately.
     *
     * @param e The event type to be assigned to the key, of type `KeypadEventTypes`.
     */
    void setEvent(KeypadEventTypes e);

    /**
     * @brief Checks if a key scan is available by filtering out noise during key presses.
     *
     * This method uses a delay to filter out noise and prevent erroneous key detections during key presses.
     * The delay period is defined by the constant `RUSTY_KEYPAD_KEY_FILTER_MILLIS`, which has a default value
     * of 20 milliseconds. The method ensures that key scans are only performed if the noise level is below
     * the defined threshold, thus improving the accuracy of key detection.
     *
     * @return `true` if the key scan is available and noise is filtered out, `false` otherwise.
     */
    bool isScanAvailable();

    /**
     * @brief Sets the next character index for RKP_T9 mode.
     *
     * This method updates the character index to the next character in the sequence associated with the key
     * when the keyboard is in RKP_T9 mode. It is used to cycle through the characters that a key represents,
     * allowing users to select the desired character by pressing and holding the key.
     */
    void nextCharIndex();

    /**
     * @brief Resets the activity timer for the key.
     *
     * This method resets the `last_activity_ts` timestamp, which tracks the time of the last key interaction.
     * By resetting this timestamp, the method effectively refreshes the activity timer, allowing the system
     * to accurately track new key events and interactions from the point of the reset.
     */
    void resetActivityTimer();

    /**
     * @brief Checks if the key press duration exceeds the RKP_T9 threshold.
     *
     * This function determines whether the duration for which a key has been held down
     * surpasses the predefined threshold for RKP_T9 input. It is used to manage input
     * behavior in RKP_T9 mode by ensuring that prolonged key presses are handled appropriately.
     *
     * @return bool `true` if the key press duration exceeds the RKP_T9 threshold, `false` otherwise.
     */
    bool isOverT9Duration();

    /**
     * @brief Checks if the key press duration exceeds the RKP_KEY_DOWN threshold.
     *
     * This function determines whether the duration for which a key has been held down
     * exceeds the predefined threshold for RKP_KEY_DOWN events. It is used to manage input
     * behavior by identifying if a prolonged key press has occurred.
     *
     * @return bool `true` if the key press duration exceeds the RKP_KEY_DOWN threshold, `false` otherwise.
     */
    bool isOverKeyDownDuration();

    /**
     * @brief Checks if the key press duration has exceeded the long press threshold.
     *
     * This function determines whether the duration for which a key has been held down
     * has surpassed the predefined threshold for a long press action. If the duration
     * exceeds the threshold, it returns true, indicating a long press.
     *
     * @return true if the key press duration exceeds the long press threshold, otherwise false.
     */
    bool isOverLongPressDuration();

    /**
     * @brief Analyzes and handles button actions based on the current and new states.
     *
     * This function determines the appropriate action when a button is held down, depending on
     * the specific configuration. If the button is in the same state (`new_state` is the same as
     * the current state), the function will decide the next step, such as whether to trigger a
     * long press action or ignore further input.
     *
     * @param new_state The new state of the button (true if pressed, false if not).
     * @return A boolean value indicating if the state has changed or if an action needs to be performed.
     */
    bool analyzeSameState(bool new_state);

    /**
     * @brief Checks if the current event is related to a delete action.
     *
     * This function determines whether the current keypad event is associated with
     * a delete action, such as pressing or releasing the delete key.
     *
     * @return true if the current event is related to a delete action, otherwise false.
     */
    bool isEventDeleteRelation();

    /**
     * @brief Compares the specified event with the current event.
     *
     * This function checks whether the provided keypad event type `e` matches the current event
     * being processed. It helps to determine if a specific event is occurring.
     *
     * @param e The event type to compare with the current event.
     * @return true if the specified event matches the current event, otherwise false.
     */
    bool isEvent(KeypadEventTypes e);
};
#endif