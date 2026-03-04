#include <stdio.h>
#include <stdlib.h>
#include <new>

/**
 * @brief A node in the linked list.
 */
template <typename T>
struct node
{
    node *next;
    T data;
};

/**
 * @brief A singly linked list structure.
 */
template <typename T>
struct linked_list
{
    node<T> *first;
    node<T> *last;
};

/**
 * @brief Create a new empty linked list.
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
 */
template <typename T>
void add_node(linked_list<T> *list, T data){
    node<T> *new_node = (node<T> *)malloc(sizeof(node<T>));
    new (&new_node->data) T();
    new_node->data = data;
    new_node->next = nullptr;

    if (list->first == nullptr){
        list->first = new_node;
        list->last = new_node;
    }
    else{
        list->last->next = new_node;
        list->last = new_node;
    }
}

/**
 * @brief Print all values in the list.
 */
template <typename T>
void print_list(linked_list<T> *list){
    node<T> *current = list->first;
    while (current != nullptr)
    {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

/**
 * @brief Delete the entire linked list and free its memory.
 */
template <typename T>
void delete_linked_list(linked_list<T> *list)
{
    node<T> *current = list->first;
    while (current != nullptr)
    {
        node<T> *next = current->next;
        current->data.~T();
        free(current);
        current = next;
    }

    free(list);
}

/**
 * @brief Remove a node by value (first match).
 */
template <typename T>
void delete_value(linked_list<T> *list, T value)
{
    node<T> *current = list->first;
    node<T> *previous = nullptr;

    while (current != nullptr && current->data != value)
    {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) return; // not found

    if (previous == nullptr)
    {
        // deleting first node
        list->first = current->next;
    }
    else
    {
        previous->next = current->next;
    }

    if (current == list->last)
    {
        list->last = previous;
    }

    current->data.~T();
    free(current);
}

/**
 * @brief Insert a value at a given position (0 = beginning).
 */
template <typename T>
void insert_at(linked_list<T> *list, T value, int position)
{
    node<T> *new_node = (node<T> *)malloc(sizeof(node<T>));
    new (&new_node->data) T();
    new_node->data = value;
    new_node->next = nullptr;

    if (position <= 0 || list->first == nullptr)
    {
        // Insert at beginning
        new_node->next = list->first;
        list->first = new_node;
        if (list->last == nullptr) list->last = new_node;
        return;
    }

    node<T> *current = list->first;
    int index = 0;
    while (current->next != nullptr && index < position - 1)
    {
        current = current->next;
        index++;
    }

    new_node->next = current->next;
    current->next = new_node;

    if (new_node->next == nullptr)
    {
        list->last = new_node;
    }
}

/**
 * @brief Demonstration of linked list usage with a menu.
 */
int main()
{
    linked_list<int> *list = new_linked_list<int>();
    int choice, value, pos;

    do
    {
        printf("\n=== Linked List Menu ===\n");
        printf("1. View values\n");
        printf("2. Add value to end\n");
        printf("3. Delete value\n");
        printf("4. Insert value at position\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            print_list(list);
            break;

        case 2:
            printf("Enter value to add: ");
            scanf("%d", &value);
            add_node(list, value);
            break;

        case 3:
            printf("Enter value to delete: ");
            scanf("%d", &value);
            delete_value(list, value);
            break;

        case 4:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            printf("Enter position (0 = start): ");
            scanf("%d", &pos);
            insert_at(list, value, pos);
            break;

        case 5:
            delete_linked_list(list);
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
