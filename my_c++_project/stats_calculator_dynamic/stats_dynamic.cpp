#include "splashkit.h"
#include "dynamic_array.h"
#include <stdio.h>

/** function to read an integer greater than 1
 * @param prompt - passed by value, of data type string; contain the output message for the user to know what to input
 *
 * @return a positive interger greater than 0
 */
int read_integer(string prompt)
{
    write(prompt);
    string line = read_line();
    bool flag = false;
    int num;
    do
    {
        while (!is_integer(line))
        {
            write("Please enter number greater than 0: ");
            write(prompt);
            line = read_line();
        }
        num = stoi(line);
        if (num > 0)
        {
            flag = true;
        }

    } while (!flag);
    return num;
}

/** function to read an real(double) value
 * @param prompt passed by value, of data type string; contain the output message for the user to know what to input
 *
 * @return a double value
 */
double read_double(string prompt)
{
    write(prompt);
    string line = read_line();
    bool flag = false;
    double num;
    while (!is_double(line))
    {
        write("Please enter a number: ");
        write(prompt);
        line = read_line();
    }
    num = convert_to_double(line);
    return num;
}

/**
 * procedure to fill the array
 * 
 * @param *data a pointer to the dynamic array
 */
void populate_array(d_arr<double> *data)
{
    int numdata = read_integer("How many values do you want to add: ");
    for (int i = 0; i < numdata; i++)
    {
        add(data, read_double("Enter value no. " + std::to_string(i + 1) + ": "));
    }
}

/**
 * procedure to print the array
 * 
 * @param *data a pointer to the dynamic array
 */
void print_array(const d_arr<double> *data)
{
    for (int i = 0; i < (int)data->size; i++)
    {
        printf("%d: %lf\n", i, get(data, i));
    }
}

/**
 * function for return the maximum
 * 
 * @param *data a pointer to the dynamic array
 * 
 * @return maximum - a double value
 */
double maximum(const d_arr<double> *data)
{
    double max_val = get(data, 0);
    for (int i = 1; i < (int)data->size; i++){
        double val = get(data, i);
        if (val > max_val){
            max_val = val;
        }
    }
    return max_val;
}

/**
 * function for return the sum
 * 
 * @param *data a pointer to the dynamic array
 * 
 * @return sum - a double value
 */
double sum(const d_arr<double> *data)
{
    double total = 0;
    for (int i = 0; i < (int)data->size; i++){
        total += get(data, i);
    }
    return total;
}

/**
 * function for return the mean
 * 
 * @param *data a pointer to the dynamic array
 * 
 * @return mean - a double value
 */
double mean(const d_arr<double> *data)
{
    if (data->size == 0)
        return 0;
    return sum(data) / data->size;
}

/**
 * procedure for print an element of the dynamics array
 * 
 * @param *data a pointer to the dynamic array
 * 
 */
void print(const d_arr<double> *data)
{
    for (int i = 0; i < data->size; i++)
    {
        printf("%d: %lf\n", i, get(data, i));
    }
}

/**
 * procedure for add data to the dynamic array
 *  
 * @param *data a pointer to the dynamic array
 * 
 */
void add_data(d_arr<double> *data)
{
    double value = read_double("Enter a value to add: ");
    if (!add(data, value))
    {
        printf("Sorry, out of memory\n");
    }
}

/**
 * procedure to remove an elenent from the dynamic array
 * 
 * @param *data a pointer to the dynamic array
 * 
 */
void remove_data(d_arr<double> *data)
{
    print(data);

    int index = read_integer("Enter the index of the value to remove: ");

    if (index >= 0 && index < data->size)
    {
        for (int i = index; i < data->size - 1; i++)
        {
            set(data, i, get(data, i + 1));
        }
        resize(data, data->size - 1);
    }
    else
    {
        printf("Sorry, that is not a valid indez.\n");
    }
}

int main()
{
    d_arr<double> *data = new_dynamic_array<double>(10);

    populate_array(data);
    print_array(data);

    double max_val = maximum(data);
    double total = sum(data);
    double avg = mean(data);

    printf("\nThe maximum value is %.2f, the sum is %.2f, and the mean is %.2f.\n", max_val, total, avg);

    add_data(data);
    print(data);
    write_line("");
    remove_data(data);
    write_line("");
    print(data);

    delete_dynamic_array(data);
    data = nullptr;

    return 0;
}
