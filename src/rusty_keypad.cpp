#include <rusty_keypad.h>

void RustyKeypad::scan()
{

    if (!isEnabled())
    {
        return;
    }

    if (KeyList == nullptr)
    {
        setFactoryConfig();
    }

    interrupted = false;
    checkBuzzer();
    RustyKeyNode *temp = KeyList->getHead();
    bool change = false;
    String pressed_keys = "";
    while (temp != nullptr)
    {
        if (checkWaitKey(temp->data))
        {
            temp = temp->next;
            continue;
        }

        if (checkKey(temp->data))
        {
            change = !interrupted;
        }
        if (interrupted)
            break;
        if (temp->data->isPressed())
        {
            pressed_keys += String(temp->data->getKeyCode());
            if (getType() == RKP_T9)
            {
                setWaitKey(temp->data);
                break;
            }
        }

        temp = temp->next;
    }
    if (!change)
        return;
    if (pressed_keys.length() > 1 && multipleKeyListener != NULL)
        multipleKeyListener(pressed_keys);
}

bool RustyKeypad::checkKey(RustyKey *key)
{
    if (!key->check())
    {
        return false;
    }
    switch (key->getCurrentEvent())
    {
    case KeypadEventTypes::RKP_KEY_DOWN:
        if (keyDownListener != NULL)
        {
            keyDownListener(key->getKeyCode());
        }
        beepBuzzer(1);
        break;
    case KeypadEventTypes::RKP_KEY_UP:
        appendKey(key->getKeyCode());
        if (keyUpListener != NULL)
        {
            keyUpListener(key->getKeyCode());
        }
        resetWaitKey();
        break;
    case KeypadEventTypes::RKP_LONG_PRESS:
        if (longPressListener != NULL)
        {
            longPressListener(key->getKeyCode());
        }
        resetWaitKey();
        break;

    case KeypadEventTypes::RKP_PRESS_DELETE:
        setWaitKey(key);
        deleteChar();
        if (onDeleteListener != NULL)
        {
            onDeleteListener(getDeleteKey());
        }
        beepBuzzer(2);
        break;
    case KeypadEventTypes::RKP_RELEASE_DELETE:
        resetWaitKey();
        break;
    case KeypadEventTypes::RKP_CLEAR_SCREEN:
        clearScreen();
        beepBuzzer(5);
        break;
    case KeypadEventTypes::RKP_PRESS_ENTER:
        setWaitKey(key);
        if (onEnterListener != NULL)
        {
            onEnterListener(getKeypadData());
        }
        beepBuzzer(10);
        break;
    case KeypadEventTypes::RKP_RELEASE_ENTER:
        resetWaitKey();
        clearScreen();
        break;
    default:
        break;
    }
    return true;
}