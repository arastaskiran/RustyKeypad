/*
 * RustyKeypad Class
 * 
 * Author: Aras TAŞKIRAN
 * Email: aras@arastaskiran.com
 * Date: 2024-09-2024 
 * 
 * Description:
 * 
 * Welcome to the RustyKeypad library. One weekend, I was really bored,
 * so I decided to write a library for the keypad I had on hand.
 * All the existing libraries are very useful, but they didn't fully meet my needs,
 * and I found myself repeating code for many tasks. Mine isn't perfect either,
 * but it serves my purpose. Feel free to use it if it helps you,
 * and you're welcome to contribute as you wish.
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

#ifndef RUSTY_KEYPAD_H
#define RUSTY_KEYPAD_H

#include <base_keypad.h>

class RustyKeypad: public BaseRustyKeypad {

public:
    static void scan();

private:
    static bool checkKey(RustyKey* key);


};
#endif