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

    RustyKeyNode *temp = KeyList->getHead();
    bool change = false;
    String pressed_keys = "";
    while (temp != nullptr)
    {
        if (waitKey != nullptr)
        {
            if (!temp->data->isEqual(waitKey))
            {
                temp = temp->next;
                continue;
            }
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
            if (getType() == T9)
            {
                waitKey = temp->data;
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
    case KeypadEventTypes::KEY_DOWN:
        if (keyDownListener != NULL)
        {
            keyDownListener(key->getKeyCode());
        }
        break;
    case KeypadEventTypes::KEY_UP:
        if (keyUpListener != NULL)
        {
            keyUpListener(key->getKeyCode());
        }
        waitKey = nullptr;
        break;
    case KeypadEventTypes::LONG_PRESS:
        if (longPressListener != NULL)
        {
            longPressListener(key->getKeyCode());
        }
        waitKey = nullptr;
        break;

    default:
        break;
    }
    return true;
}