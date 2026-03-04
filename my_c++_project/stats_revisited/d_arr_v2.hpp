#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H 
#include <cstdlib>


/**
 * @brief A dynamic array struct taht contains the size, capcity, and data pointer used to implement thsi dynamic structure.
 * 
 * @tparam T the type of data to store in the dynamic array
 * @field data a pointer to the data in the dynamic arrayon the heap
 * @field size the number of elements used in the dynamic array
 * @field capacity the number of elements the dynamic array can hold
 * @field default_value to use when getting an element
 */
template<typename T>
struct dynamic_array
{
    unsigned int size;
    unsigned int capacity;
    T *data;
    T default_value;



    /**
     * @brief Create a new dynamic array with the indicated initial capacity.
     * 
     * @param capacity its initial capacity
     * @param default_value the value to return if the index is out of bounds
     */
    dynamic_array(unsigned int capacity, T default_value){
        data = (T *)malloc(sizeof(T) * capacity);
        size = 0;
        this->default_value = default_value; 
 
        if (data == nullptr){
            this->capacity = 0;
        }
        else{
            this->capacity = capacity;
        }

        for (int i = 0; i < capacity; i++){
            new(&this->data[i]) T();
        }
    }


    /**
     * @brief free the memory allocated to the dynamic array. once freed the data in the array will no longer be acceddible
     */
    ~dynamic_array(){
        size = 0;

        for (int i = 0; i < capacity; i++){
            data[i].~T();
        }
        capacity = 0;

        free(data);
        data = nullptr;
    }

    /**
     * @brief resize the capacity of the dynamic array
     * 
     * If the new capacity is smaller than the current size, the size will be updated to match the new capacity
     * 
     * @param new_capacity the new capacity of the dynamic array
     * @return true if this succeeded, or false if it could not reallocate memory
     */
    bool resize(unsigned int new_capacity){
        for(int i = capacity -1; i >=(int)new_capacity; i--)
        {
            data[i].~T();
        }

        T *new_data = (T *)realloc(data, sizeof(T) * new_capacity);

        if (new_data == nullptr){
            return false;
        }

        for (int i = capacity; i < new_capacity; i++){
            new(&new_data[i]) T();
        }

        data = new_data;
        capacity = new_capacity;

        if (new_capacity < size)
        {
            size = new_capacity;
        }
        return true;
    }


    /**
     * @brief Add an element to the end of the dynamic array
     * 
     * @param value the value to the add to the end of the dynamic 
     */
    bool add(T value){
        
        if (size >= capacity && !resize(capacity * 2+1))
        {
            return false;
        }

        data[size] = value;
        size++;

        return true;
    }


    /**
     * @brief read and return the value of the indicated element from the dynamic array.
     * 
     * if the index is out of bounds, the function will return the indicated default value
     * 
     * @param index the index of the element to remove
     */
    T &get(unsigned int index){
        return (*this)[index];
    }


    /**
     * provide array style access to the dynamic array
     * 
     * @param index the index of the element to get
     * @return T& the element at the given index
     */
    const T &operator[](unsigned int index) const{
        if (index >= size){
            return default_value;
        } 
        return data[index];
    }

    /**
     * provide array style access to the dynamic array
     * 
     * @param index the index of the element to get
     * @return T& the element at the given index
     */
    T &operator[](unsigned int index){
        if (index >= size){
            return default_value;
        } 
    return data[index];
    }

    /**
     * @brief set the value of the indicated element from the dynamic array
     * 
     * if the index is out of bounds, the function will do nothings and return false
     * 
     * @param index the index of the element to change
     * @param value the value to set the element to
     * @return true when the value is set, or false if this failed 
     */
    bool set(unsigned int index, T value){
        if(index >= size){
            return false;
        }

        data[index] = value;
        return true;
    }   
};

#endif
