/*
 * RustyKeyList Class
 * 
 * Author: Aras TAŞKIRAN
 * Email: aras@arastaskiran.com
 * Date: 2024-09-2024 
 * 
 * Description:
 * 
 * The key list is stored within this class. Instead of a standard matrix scan,
 * the objects scan themselves, which I found to be more logical. This approach may seem unusual,
 * but it aligns with my preference. As the structure suggests,
 * this class is implemented as a linked list, so caution is advised when working with it.
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