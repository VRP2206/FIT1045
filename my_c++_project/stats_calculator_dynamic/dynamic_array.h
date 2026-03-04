#ifndef dynamic_array_h
#define dynamic_array_h

#include <string>
#include <cstdlib>
using std::string;

/**
 * @brief A dynamic array struct that contains the size, capacity,
 *        and data pointer used to implement this dynamic structure.
 *
 * @tparam T the type (typename) of data to store in the dynamic array
 * @field data a pointer to the data in the dynamic array on the heap
 * @field size the number of elements used in the dynamic array
 * @field capacity the number of elements the dynamic array can hold
 */
template<typename T>
struct d_arr
{
    T *data;
    unsigned int size;
    unsigned int capacity;
};

/**
 * @brief Create a new dynamic array with the indicated initial capacity.
 *        This will return a nullptr if the array cannot be allocated.
 *
 * @tparam T the type of data the array will store
 * @param capacity its initial capacity, with a default value of 50
 * @return dynamic_array<T>* a pointer to the new dynamic array
 */
template <typename T>
d_arr<T> *new_dynamic_array(unsigned int capacity = 50);

/**
 * @brief Free the memory allocated to the dynamic array. Once freed
 *        the data in the array will no longer be accessible.
 *
 * @tparam T the data type of the dynamic array
 * @param array a pointer to the dynamic array to free
 */
template <typename T>
void delete_dynamic_array(d_arr<T> *array);

/**
 * @brief Resize the capacity of the dynamic array.
 *
 * If the new capacity is smaller than the current size, the size
 * will be updated to match the new capacity.
 *
 * @tparam T the type of data in the dynamic array
 * @param array the dynamic array to grow
 * @param new_capacity the new capacity of the dynamic array
 * @returns true if this succeeded, or false if it could not reallocate memory
 */
template <typename T>
bool resize(d_arr<T> *arr, unsigned int new_capacity);

/**
 * @brief Add an element to the end of the dynamic array
 *
 * @tparam T the type of data in the dynamic array
 * @param value the value to add to the end of the dynamic array
 * @param array the dynamic array to add the value to
 * @returns true if this succeeded, false if we cannot resize to fit the new element
 */
template <typename T>
bool add(d_arr<T> *array, T value);

/**
 * @brief read and return the value of the indicated element from the dynamic array.
 *
 * If the array is not allocated or the index is out of bounds, the function will throw a string exception message.
 *
 * @tparam T the type of data in the dynamic array
 * @param array the dynamic array to remove the element from
 * @param index the index of the element to remove
 * @throws a string message if the array is not allocated or the index is invalid
 */
template <typename T>
T get(const d_arr<T> *array, unsigned int index);

/**
 * @brief set the value of the indicated element from the dynamic array.
 *
 * If the index is out of bounds, the function will throw an string exception.
 *
 * @tparam T the type of data in the dynamic array
 * @param array the dynamic array to set the element in
 * @param index the index of the element to change
 * @param value the value to set the element to
 */
template <typename T>
void set(d_arr<T> *array, unsigned int index, T value);


#include "dynamic_array.hpp"

#endif