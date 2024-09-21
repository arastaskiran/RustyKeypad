#include <base_keypad.h>
/*INITIAL VALUES*/

uint8_t BaseRustyKeypad::pins_mode{INPUT_PULLUP};
uint8_t BaseRustyKeypad::row_size{4};
uint8_t BaseRustyKeypad::col_size{3};
unsigned int BaseRustyKeypad::keypad_data_cursor{0};
char BaseRustyKeypad::float_char{'*'};
KeypadTypes BaseRustyKeypad::keypad_type{KeypadTypes::INTEGER};
bool BaseRustyKeypad::enabled{false};
bool BaseRustyKeypad::interrupted{false};
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
void (*BaseRustyKeypad::multipleKeyListener)(String){0};

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
}

void BaseRustyKeypad::reset()
{

    clearScreen();
    interrupted = true;
}
void BaseRustyKeypad::clearScreen()
{
    keypad_data = "";
    keypad_data_cursor = 0;
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
    if (keypad_data.length() == keypad_data_cursor)
    {
        keypad_data = keypad_data + String(key);
    }

    keypad_data_cursor++;
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

void BaseRustyKeypad::addMultipleKeyListener(void (*listener)(String))
{
    multipleKeyListener = listener;
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