#include <rusty_key_list.h>

RustyKeyList::RustyKeyList()
{
    head = nullptr;
}

RustyKeyList::~RustyKeyList()
{
    clear();
}


RustyKeyNode& RustyKeyNode::operator=(const RustyKeyNode& other) {
    if (this == &other) {
        return *this; 
    }    
    delete data;
    data=nullptr;
    data = new RustyKey(*other.data); 
    next = other.next; 

    return *this;
}

RustyKeyNode::RustyKeyNode(const RustyKeyNode& other)
    : data(new RustyKey(*other.data)), next(other.next) {}

void RustyKeyList::append(const char * key, uint8_t row_pin, uint8_t col_pin)
{
    RustyKeyNode *newNode = new RustyKeyNode(key, row_pin, col_pin);

    if (head == nullptr)
    {
        head = newNode;
        return;
    }

    RustyKeyNode *temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = newNode;
}

void RustyKeyList::clear()
{
    RustyKeyNode *current = head;
    while (current != nullptr)
    {
        RustyKeyNode *next = current->next;
        delete current;
        current = nullptr;
        current = next;
    }
    head = nullptr;
}

void RustyKeyList::disable()
{
    RustyKeyNode *temp = head;
    while (temp != nullptr)
    {
        temp->data->disable();
        temp = temp->next;
    }
}

RustyKeyNode *RustyKeyList::getHead() const
{
    return head;
}