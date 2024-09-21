#include <base_keypad.h>
/*INITIAL VALUES*/

uint8_t BaseRustyKeypad::pins_mode{INPUT_PULLUP};
uint8_t BaseRustyKeypad::row_size{4};
uint8_t BaseRustyKeypad::col_size{3};
uint8_t BaseRustyKeypad::max_text_length{20};
unsigned int BaseRustyKeypad::keypad_data_cursor{0};
char BaseRustyKeypad::float_char{'*'};
char BaseRustyKeypad::delete_key{'*'};
char BaseRustyKeypad::enter_key{'#'};
KeypadTypes BaseRustyKeypad::keypad_type{KeypadTypes::RKP_INTEGER};
bool BaseRustyKeypad::enabled{false};
bool BaseRustyKeypad::interrupted{false};
bool BaseRustyKeypad::has_delete_key{true};
bool BaseRustyKeypad::has_enter_key{false};
bool BaseRustyKeypad::use_stored_text{true};
bool BaseRustyKeypad::use_password_mask{false};
const char *BaseRustyKeypad::keypadFactoryMap[MAX_KEYPAD_MATRIX_SIZE][MAX_KEYPAD_MATRIX_SIZE] = {
    {"1.,?!'\"-()@/:_", "2ABCabc", "3DEFdef"},
    {"4GHIghiİ", "5JKLjkl", "6MNOmnoÖö"},
    {"7PQRSpqrsŞş", "8TUVtuvÜü", "9WXYZwxyz"},
    {"*", "0 +", "#"},
};
RustyKey *BaseRustyKeypad::waitKey{nullptr};

String BaseRustyKeypad::keypad_data{""};
unsigned long BaseRustyKeypad::keydown_timeout{1500};
unsigned long BaseRustyKeypad::long_press_duration{5000};
unsigned long BaseRustyKeypad::idle_timeout{30000};
unsigned long BaseRustyKeypad::last_activity_ts{0};
unsigned long BaseRustyKeypad::t9_duration{600};
RustyKeyList *BaseRustyKeypad::KeyList{nullptr};
uint8_t *BaseRustyKeypad::row_out_pins{nullptr};
void (*BaseRustyKeypad::keyDownListener)(char){0};

void (*BaseRustyKeypad::keyUpListener)(char){0};
void (*BaseRustyKeypad::longPressListener)(char){0};
void (*BaseRustyKeypad::onEnterListener)(String){0};
void (*BaseRustyKeypad::onDeleteListener)(char){0};
void (*BaseRustyKeypad::multipleKeyListener)(String){0};
void (*BaseRustyKeypad::textChangeListener)(String){0};

void BaseRustyKeypad::keyboardSetup(const char *map[MAX_KEYPAD_MATRIX_SIZE][MAX_KEYPAD_MATRIX_SIZE],
                                    const uint8_t row_pins[MAX_KEYPAD_MATRIX_SIZE],
                                    const uint8_t col_pins[MAX_KEYPAD_MATRIX_SIZE],
                                    uint8_t row,
                                    uint8_t col,
                                    uint8_t mode)
{

    last_activity_ts = millis();
    if (KeyList != nullptr)
    {
        KeyList->clear();
    }
    else
    {
        KeyList = new RustyKeyList();
    }

    resizeRowPins(row);
    for (uint8_t i = 0; i < row; ++i)
    {
        row_out_pins[i] = row_pins[i];
        for (uint8_t j = 0; j < col; ++j)
        {
            KeyList->append(map[i][j], row_pins[i], col_pins[j]);
        }
    }
    row_size = row;
    col_size = col;
    pins_mode = mode;
    reset();
}

void BaseRustyKeypad::reset()
{

    clearScreen();
    interrupted = true;
    waitKey = nullptr;
}
void BaseRustyKeypad::clearScreen()
{
    keypad_data = "";
    keypad_data_cursor = 0;
    if (textChangeListener != NULL)
    {
        textChangeListener(getKeypadData());
    }
}

void BaseRustyKeypad::enable()
{
    if (!enabled)
    {
        enabled = true;
        reset();
    }
}

void BaseRustyKeypad::disable()
{
    if (enabled)
    {
        enabled = false;
        reset();
        KeyList->disable();
    }
}

void BaseRustyKeypad::appendKey(char key)
{
    if (keypad_data.length() >= max_text_length || !use_stored_text)
    {
        return;
    }
    if (keypad_data.length() == keypad_data_cursor)
    {
        keypad_data = keypad_data + String(key);
    }

    keypad_data_cursor++;
    if (textChangeListener != NULL)
    {
        textChangeListener(getKeypadData());
    }
}

void BaseRustyKeypad::deleteChar()
{
    if (keypad_data.length() == 0 || !use_stored_text)
    {
        return;
    }
    if (keypad_data_cursor < keypad_data.length())
    {
        keypad_data.remove(keypad_data_cursor, 1);
    }
    else
    {
        keypad_data.remove(keypad_data.length() - 1);
    }

    keypad_data_cursor--;
    if (textChangeListener != NULL)
    {
        textChangeListener(getKeypadData());
    }
}

void BaseRustyKeypad::setFactoryConfig()
{
    uint8_t rows[MAX_KEYPAD_MATRIX_SIZE] = {2U, 3U, 4U, 5U};
    uint8_t cols[MAX_KEYPAD_MATRIX_SIZE] = {6U, 7U, 8U};
    keyboardSetup(
        keypadFactoryMap,
        rows,
        cols,
        (uint8_t)4,
        (uint8_t)3,
        INPUT_PULLUP);
}

void BaseRustyKeypad::resizeRowPins(size_t size)
{
    if (row_out_pins != nullptr)
    {
        free(row_out_pins);
    }
    row_out_pins = static_cast<uint8_t *>(malloc(size * sizeof(uint8_t)));
}

void BaseRustyKeypad::addKeyDownListener(void (*listener)(char))
{
    keyDownListener = listener;
}

void BaseRustyKeypad::addKeyUpListener(void (*listener)(char))
{
    keyUpListener = listener;
}

void BaseRustyKeypad::addLongPressListener(void (*listener)(char))
{
    longPressListener = listener;
}

void BaseRustyKeypad::addEnterActionListener(void (*listener)(String))
{
    onEnterListener = listener;
}

void BaseRustyKeypad::addDeleteActionListener(void (*listener)(char))
{
    onDeleteListener = listener;
}

void BaseRustyKeypad::addMultipleKeyListener(void (*listener)(String))
{
    multipleKeyListener = listener;
}

void BaseRustyKeypad::addTextChangeListener(void (*listener)(String))
{
    textChangeListener = listener;
}

bool BaseRustyKeypad::isEnabled()
{
    return enabled;
}

void BaseRustyKeypad::setType(KeypadTypes type)
{
    keypad_type = type;
}

KeypadTypes BaseRustyKeypad::getType()
{
    return keypad_type;
}

bool BaseRustyKeypad::hasWaitKey()
{
    return waitKey != nullptr;
}

bool BaseRustyKeypad::checkWaitKey(RustyKey *key)
{
    if (!hasWaitKey())
        return false;

    return !key->isEqual(waitKey);
}

void BaseRustyKeypad::setWaitKey(RustyKey *key)
{
    waitKey = key;
}

void BaseRustyKeypad::resetWaitKey()
{
    waitKey = nullptr;
}

bool BaseRustyKeypad::isDeleteKey(char key)
{
    if (!hasDeleteKey())
        return false;
    return key == delete_key;
}

char BaseRustyKeypad::getDeleteKey()
{
    return delete_key;
}

void BaseRustyKeypad::ignoreDeleteKey()
{
    has_delete_key = false;
}

void BaseRustyKeypad::useDeleteKey(char key)
{
    delete_key = key;
    has_delete_key = true;
}

bool BaseRustyKeypad::hasDeleteKey()
{
    return has_delete_key;
}

void BaseRustyKeypad::setStoredText(bool state)
{
    use_stored_text = state;
}

void BaseRustyKeypad::setMaxTextLength(uint8_t len)
{
    max_text_length = len;
}

String BaseRustyKeypad::getKeypadData()
{
    if (!use_password_mask || keypad_data.length() == 0)
    {
        return keypad_data;
    }

    String asterisks = "";
    for (size_t i = 0; i < keypad_data.length(); i++)
    {
        asterisks += '*';
    }
    return asterisks;
}

bool BaseRustyKeypad::isKeypadEqual(String text)
{
    return keypad_data == text;
}

bool BaseRustyKeypad::hasPasswordMask()
{
    return use_password_mask;
}

void BaseRustyKeypad::setPasswordMask(bool state)
{
    use_password_mask = state;
}

void BaseRustyKeypad::setEnterKey(char key)
{
    enter_key = key;
    has_enter_key = true;
}

bool BaseRustyKeypad::isEnterKey(char key)
{
    if (!has_enter_key)
        return false;
    return key == enter_key;
}

bool BaseRustyKeypad::hasEnterKey()
{
    return has_enter_key;
}

void BaseRustyKeypad::ignoreEnterKey()
{
    has_enter_key = false;
}