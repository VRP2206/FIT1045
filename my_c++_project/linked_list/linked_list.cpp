#include <stdio.h>
#include <stdlib.h>
#include <new>

/**
 * @brief A node in the linked list.
 *
 * Each node stores a value of type T and a pointer to the next node.
 *
 * @tparam T the type of data stored in the node
 * @field data the stored data of type T
 * @field next a pointer to the next node in the list
 */
template <typename T>
struct node
{
    node *next;
    T data;
};

/**
 * @brief A singly linked list structure.
 *
 * The list maintains a pointer to the first and last nodes
 * to support efficient insertion at the end.
 *
 * @tparam T the type of data stored in the list
 * @field first pointer to the first node of the list
 * @field last pointer to the last node of the list
 */
template <typename T>
struct linked_list
{
    node<T> *first;
    node<T> *last;
};

/**
 * @brief Create a new empty linked list.
 *
 * Allocates memory for a new linked_list and sets
 * its first and last pointers to nullptr.
 *
 * @tparam T the type of data stored in the linked list
 * @return linked_list<T>* a pointer to the newly created list
 */
template <typename T>
linked_list<T> *new_linked_list()
{
    linked_list<T> *list = (linked_list<T> *)malloc(sizeof(linked_list<T>));
    list->first = nullptr;
    list->last = nullptr;
    return list;
}

/**
 * @brief Add a new node with the given data to the end of the list.
 *
 * A new node is created and appended to the list. If the list
 * is empty, the new node becomes both the first and last node.
 *
 * @tparam T the type of data stored in the linked list
 * @param list the list to add the node to
 * @param data the value to store in the new node
 */
template <typename T>
void add_node(linked_list<T> *list, T data)
{
    node<T> *new_node = (node<T> *)malloc(sizeof(node<T>));

    new (&new_node->data) T();

    new_node->data = data;
    new_node->next = nullptr;

    if (list->first == nullptr)
    {
        list->first = new_node;
        list->last = new_node;
    }
    else
    {
        list->last->next = new_node;
        list->last = new_node;
    }
}

/**
 * @brief Delete the entire linked list and free its memory.
 *
 * Traverses the list, destroys each node’s data, and frees
 * the memory allocated for each node. Finally, the list itself
 * is freed and its pointers reset to nullptr.
 *
 * @tparam T the type of data stored in the linked list
 * @param list the linked list to delete
 */
template <typename T>
void delete_lined_list(linked_list<T> *list)
{
    node<T> *current = list->first;
    while (current != nullptr)
    {
        node<T> *next = current->next;

        current->data.~T();
        current->next = nullptr;
        current = next;
    }

    list->first = nullptr;
    list->last = nullptr;
    free(list);
}


/**
 * @brief Remove a specific node from the linked list.
 *
 * Adjusts the previous node’s pointer to bypass the node,
 * updates the list’s first/last pointers if necessary,
 * destroys the node’s data, and frees its memory.
 *
 * @tparam T the type of data stored in the linked list
 * @param list the linked list to remove the node from
 * @param node_to_remove the node to remove
 */
template <typename T>
void remove_node(linked_list<T> *list, node<T> *node_to_remove)
{

    node<T> *privious = nullptr;

    if (list->first == node_to_remove)
    {
        list->first = node_to_remove->next;
    }
    else
    {
        node<T> *current = list->first;
        while (current != node_to_remove && current != nullptr)
        {
            privious = current;
            current = current->next;
        }

        if (current == nullptr)
            return;

        privious->next = node_to_remove->next;
    }

    if (list->last == node_to_remove)
    {
        list->last = privious;
    }

    node_to_remove->next = nullptr;
    node_to_remove->data.~T();
    free(node_to_remove);
}

/**
 * @brief Demonstration of linked list usage.
 *
 * Creates a linked list of integers, adds elements,
 * prints them, removes one element, prints again,
 * and deletes the list.
 */
int main()
{
    linked_list<int> *list = new_linked_list<int>();
    add_node(list, 1);
    add_node(list, 2);
    add_node(list, 3);
    add_node(list, 4);

    node<int> *current = list->first;
    while (current != nullptr)
    {
        printf("%d->", current->data);
        current = current->next;
    }
    printf("\n");

    remove_node(list, list->first->next->next);

    current = list->first;
    while (current != nullptr)
    {
        printf("%d->", current->data);
        current = current->next;
    }
    printf("\n");

    delete_lined_list(list);
}