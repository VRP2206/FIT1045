#include <cstdio>
#include <cstdlib>
#include "utilities.h"
#include "d_arr_v2.hpp"

/**
 * Populate the array with values entered by the user
 *
 * @param data the array the array of values (passed by refrences)
 */
void populate_array(dynamic_array<double> &data)
{

    for (int i = 0; i < data.size; i++)
    {
        data[i] = read_double("Enter value: ");
    }
}

/**
 * output the values in the array
 *
 * @param data the array of values
 */
void print(const dynamic_array<double> &data)
{
    for (int i = 0; i < data.size; i++)
    {
        printf("%d: %lf\n", i, data[i]);
    }
}

/**
 * calculate the sum of the values in the array
 *
 * @param data the array of values
 * @return the sum of the values
 */
double sum(const dynamic_array<double> &data)
{
    int i;
    double result = 0;

    for (i = 0; i < data.size; i++)
    {
        result += data[i];
    }
    return result;
}

/**
 * calculate the mean of the values in the array
 *
 * @param data the array of values
 * @returns the mean of the values
 */
double mean(const dynamic_array<double> &data)
{
    if (data.size > 0)
    {
        return sum(data) / data.size;
    }
    else
    {
        return 0;
    }
}

/**
 * Calculate the largest value in the array
 *
 * @param data the array of values
 * @returns the largest value, or 0 if there are no values
 */
double max(const dynamic_array<double> &data)
{
    if (data.size == 0)
    {
        return 0;
    }

    double result = data[0];

    for (int i = 1; i < data.size; i++)
    {
        if (data[i] > result)
        {
            result = data[i];
        }
    }
    return result;
}

/**
 * add a value from the array
 *
 * @param data the array of values
 */
void add_data(dynamic_array<double> &data)
{
    double value = read_double("Enter a value to add: ");
    data.add(value);
}

/**
 * remove a value from the array
 *
 * @param data the array of values
 */
void remove_value(dynamic_array<double> &data)
{
    print(data);

    int index = read_integer("Enter the index of the values to remove: ");

    if (index >= 0 && index < data.size)
    {
        for (int i = index; i < data.size - 1; i++)
        {
            data[i] = data[i + 1];
        }
        data.size--;
    }
    else
    {
        printf("Sorry, that is not a valid index\n");
    }
}

/**
 * print the menu of option
 */
void print_menu()
{
    printf("\nMenu\n");
    printf("1. Add a value\n");
    printf("2. Remove a value\n");
    printf("3. Print the value\n");
    printf("4. Calculte stats\n");
    printf("5. Quit\n");
}

/**
 * The main entry point
 */
int main()
{
    dynamic_array<double> data = {{}, 0};
    int option;

    populate_array(data);

    print_menu();
    option = read_integer_limit("Enter an option: ", 1, 5);

    while (option != 5)
    {
        switch (option)
        {
        case 1:
            add_data(data);
            break;

        case 2:
            remove_value(data);
            break;

        case 3:
            printf("\nYou entered... \n\n");
            print(data);
            break;

        case 4:
            printf("\nCalculating statistics...\n\n");
            printf("sum:   %4.2lf\n", sum(data));
            printf("mean:  %4.2lf\n", mean(data));
            printf("Max:   %4.2lf\n", max(data));
            break;

        case 5:
            return 0;
            break;
        }
        read_string("Press enter to continue...");

        print_menu();
        option = read_integer_limit("Enter an option: ", 1, 5);
    }

    return 0;
}