#include "splashkit.h"
#include <stdio.h>
 
/**
 * struct to store statistical information about a dataset
 *
 * @field numdata - the number of data values in the dataset
 * @field max     - the maximum value in the dataset
 * @field sum     - the total sum of all data values
 * @field mean    - the arithmetic average of the dataset
 */
struct data_info
{
    int numdata;
    double max;
    double sum;
    double mean;
};

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

/** procedure to populate(fill) an array.
 * @param data an array of data type double
 * @param dinfo passed by constant reference of data type dinfo; contain information about the group of data
 * 
 */
void populate_array(double data[], const data_info &dinfo)
{

    for (int i = 0; i < dinfo.numdata; i++)
    {
        data[i] = read_double("Please enter the value no. " + std::to_string(i + 1) + ": ");
    }
}


/** Procedure to process the data; I.e., to get the mean, maximum value and sum of all values
 * @param data array of double value
 * @param dinfo of data type data_info, passed by reference; contain information about the group of data
 */
void process(double data[], data_info &dinfo)
{
    dinfo.max = data[0];
    dinfo.sum = 0;   // start from 0

    for (int i = 0; i < dinfo.numdata; i++)  // include all values
    {
        if (data[i] > dinfo.max)
        {
            dinfo.max = data[i];
        }
        dinfo.sum += data[i];
    }

    dinfo.mean = dinfo.sum / dinfo.numdata;
}


int main()
{

    data_info dinfo;
    dinfo.numdata = read_integer("How many value do you want to add: ");
    double data[dinfo.numdata];

    populate_array(data, dinfo);
    process(data, dinfo);
    write_line();

    printf("The maximum values is %.2f, the sum of value is %.2f and the mean is %.2f.", dinfo.max, dinfo.sum, dinfo.mean);
}