/*
||
|| @file rusty_key_list.h
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
#ifndef RUSTY_KEYPAD_LIST_H
#define RUSTY_KEYPAD_LIST_H
#include <rusty_key.h>


struct RustyKeyNode {
    RustyKey* data;        
    RustyKeyNode* next; 

    
    RustyKeyNode(const char * key, uint8_t row_pin, uint8_t col_pin) 
        : data(new RustyKey(key, row_pin, col_pin)), next(nullptr) {}

    // Destructor
    ~RustyKeyNode() {
        delete data; 
        data=nullptr;
    }
};

class RustyKeyList {
private:
    RustyKeyNode* head;      

public:
    RustyKeyList();    
    ~RustyKeyList();
    void append(const char * key, uint8_t row_pin, uint8_t col_pin);    
    void clear();
    void disable();
    RustyKeyNode* getHead() const;

   
};

#endif