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

/**
 * @brief Node structure for a linked list of `RustyKey` objects.
 *
 * This structure represents a node in a linked list used to manage `RustyKey` objects. Each node
 * contains a pointer to a `RustyKey` object and a pointer to the next node in the list.
 */
struct RustyKeyNode
{
    RustyKey *data;     /**< Pointer to the `RustyKey` object stored in this node. */
    RustyKeyNode *next; /**< Pointer to the next node in the linked list. */

    /**
     * @brief Constructor for initializing a `RustyKeyNode` with given parameters.
     *
     * Constructs a `RustyKeyNode` by creating a new `RustyKey` object with the provided key, row pin,
     * and column pin. Initializes the `next` pointer to `nullptr`.
     *
     * @param key The key associated with this node.
     * @param row_pin The row pin for the `RustyKey` object.
     * @param col_pin The column pin for the `RustyKey` object.
     */
    RustyKeyNode(const char *key, uint8_t row_pin, uint8_t col_pin)
        : data(new RustyKey(key, row_pin, col_pin)), next(nullptr) {}

    /**
     * @brief Assignment operator for copying
     *
     * This operator is used to assign one RustyKeyNode object to another. It manages the existing resources
     * and performs dynamic memory operations to prevent memory leaks.
     *
     * @param other Reference to another RustyKeyNode object used for the assignment.
     * @return RustyKeyNode& Reference to the current object.
     */
    RustyKeyNode &operator=(const RustyKeyNode &other);

    /**
     * @brief Copy constructor
     *
     * Constructs a new RustyKeyNode object by copying data from another RustyKeyNode object.
     *
     * @param other Reference to the RustyKeyNode object to be copied.
     */
    RustyKeyNode(const RustyKeyNode &other);

    /**
     * @brief Destructor for cleaning up the `RustyKeyNode`.
     *
     * Deletes the `RustyKey` object pointed to by `data` and sets the pointer to `nullptr` to avoid
     * dangling references. The `next` pointer is not explicitly set to `nullptr` in the destructor
     * as it is managed by the linked list structure.
     */
    ~RustyKeyNode()
    {
        delete data;
        data = nullptr;
    }
};

/**
 * @class RustyKeyList
 * @brief A linked list class for managing `RustyKey` nodes.
 *
 * This class provides a linked list structure for storing and managing `RustyKey` objects. It supports
 * appending new nodes, clearing the list, disabling operations, and retrieving the head of the list.
 */
class RustyKeyList
{
private:
    RustyKeyNode *head; /**< Pointer to the first node in the linked list. */

public:
    /**
     * @brief Default constructor for initializing an empty `RustyKeyList`.
     *
     * Constructs a new `RustyKeyList` instance with an empty list by initializing the `head` pointer to `nullptr`.
     */
    RustyKeyList();

    /**
     * @brief Destructor for cleaning up the `RustyKeyList`.
     *
     * Deletes all nodes in the linked list, freeing up memory allocated for each `RustyKeyNode` object.
     */
    ~RustyKeyList();

    /**
     * @brief Appends a new `RustyKey` to the list.
     *
     * Creates a new `RustyKeyNode` with the provided key, row pin, and column pin, and adds it to the
     * end of the linked list.
     *
     * @param key The key associated with the new `RustyKey` node.
     * @param row_pin The row pin for the new `RustyKey` node.
     * @param col_pin The column pin for the new `RustyKey` node.
     */
    void append(const char *key, uint8_t row_pin, uint8_t col_pin);

    /**
     * @brief Clears all nodes from the list.
     *
     * Deletes all `RustyKeyNode` objects in the list and resets the `head` pointer to `nullptr`.
     * This method effectively empties the list.
     */
    void clear();

    /**
     * @brief Disables all `RustyKey` elements in the list.
     *
     * This method iterates through all `RustyKeyNode` objects in the list and calls a method to
     * disable each `RustyKey` element. It effectively marks all elements in the list as inactive or
     * non-operational.
     *
     * @note The specific implementation of disabling the `RustyKey` elements depends on the internal
     *       logic of the `RustyKey` class.
     */
    void disable();
    
    /**
     * @brief Enables all `RustyKey` elements in the list.
     *
     * This method iterates through all `RustyKeyNode` objects in the list and calls a method to
     * enable each `RustyKey` element. It effectively marks all elements in the list as active or
     * operational.
     *
     * @note The specific implementation of enabling the `RustyKey` elements depends on the internal
     *       logic of the `RustyKey` class.
     */
    void enable();

    /**
     * @brief Retrieves the head node of the list.
     *
     * Returns a pointer to the first `RustyKeyNode` in the linked list. This can be used to iterate
     * over the list or access the first element.
     *
     * @return Pointer to the head node of the list.
     */
    RustyKeyNode *getHead() const;
};

#endif