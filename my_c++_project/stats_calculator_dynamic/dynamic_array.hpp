#include "splashkit.h"
#include "dynamic_array.h"
#include <new>
#include <cstdlib>



template<typename T>
d_arr<T> *new_dynamic_array(unsigned int capacity)
{
    d_arr<T> *result = (d_arr<T>*)malloc(sizeof(d_arr<T>));

    if (result == nullptr){
        return result;
    }
    result->data = (T*)malloc(sizeof(T)*capacity);
    result->size = 0;

    if (result->data == nullptr){
        result->capacity = 0;

    }
    else{
        result->capacity= capacity;

    }

    for (int i = 0; i < capacity; i++){
        new(&result->data[i]) T();
    }
    return result;
}

template<typename T>
void delete_dynamic_array(d_arr<T> *array){
    if (!array) return;

    for (int i =0; i< array->capacity; i++){
        array->data[i].~T();
    }

    array->size = 0;
    array->capacity = 0;

    free(array->data);

    free(array);
}

template<typename T>
bool resize(d_arr<T> *arr, unsigned int new_capacity){
    if (!arr) return false;
    for (int i = arr->capacity - 1 ; i>=(int)new_capacity; i--){
        arr->data[i].~T();
    }

    T* new_data = (T*)realloc(arr->data, sizeof(T)* new_capacity);
    if(new_data == nullptr){
        return false;
    }

    arr->data = new_data;
    arr->capacity = new_capacity;

    if (new_capacity < arr->size){
        arr->size = new_capacity;
    }
    return true;
}

template<typename T>
bool add(d_arr<T> *array, T value){
    if (!array) return false;

    if (array->size >= array->capacity && !resize(array, array->capacity *2+1)){
        return false;
    }

    array->data[array->size]= value;
    array->size++;

    return true;
}

template <typename T>
T get(const d_arr<T> *array, unsigned int index){
    if (!array) throw string("Array is not allocated");

    if (index >= array->size){
        throw string ("Index out of bounds");
    }
    return array->data[index];
}


template<typename T>
void set(d_arr<T> * array, unsigned int index, T value){
    if (!array) throw string ("Array is not allocated");

    if (index >= array->size){
        throw string("Index out of bounds");
    }
    array->data[index]= value;
}
;
