#include "splashkit.h"
#include <vector>

const int days_max = 20;

/**
 * @brief Reads a line of text input from the user.
 *
 * Prompts the user with the given message and then returns
 * the entered string.
 *
 * @param prompt The message shown to the user before input.
 * @return The string entered by the user.
 */
string read_string(string prompt){
    string line;
    write(prompt);
    line = read_line();
    return line;
}

/**
 * @brief Reads and validates a double number from the user.
 *
 * Continues to prompt until the user enters a valid number.
 *
 * @param prompt The message shown to the user before input.
 * @return The number entered by the user as a double.
 */
double read_double(string prompt)
{
    string line;
    line = read_string(prompt);
    while (!is_double(line))
    {
        write_line("Please enter a valid number");
        line = read_string(prompt);
    }
    return convert_to_double(line);    
}

/**
 * @brief Prompts the user to enter a temperature value.
 *
 * @return The temperature entered by the user.
 */
double read_data()
{
    return read_double("Enter the temperature: ");
}

/**
 * @brief Displays the maximum and minimum values in an array.
 *
 * Iterates through the readings and finds the largest and smallest values.
 *
 * @param array The vector of readings.
 * @param days_readings The number of readings to process.
 */
void display_max_min(const std::vector<double> &array, const int &days_readings)
{
    double max = array[0];
    double min = array[0];
    for (int i = 0; i < days_readings; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
        if (array[i] < min)
        {
            min = array[i];
        }
    }
    write_line("Max: " + std::to_string(max));
    write_line("Min: " + std::to_string(min));
}

/**
 * @brief Calculates the average of an array of values.
 *
 * @param array The vector of readings.
 * @param days_readings The number of readings to process.
 * @return The average value.
 */
double average(const std::vector<double> &array, const int &days_readings)
{
    double avg = 0;
    for (int i = 0; i < days_readings; i++)
    {
        avg += array[i];
    }
    avg /= days_readings;
    return avg;
}

/**
 * @brief Displays all values above the average.
 *
 * Iterates through the readings and prints any value greater than the average.
 *
 * @param array The vector of readings.
 * @param days_readings The number of readings to process.
 */
void above_average(const std::vector<double> &array, const int &days_readings)
{
    double avg = average(array, days_readings);
    for (int i = 0; i < days_readings; i++)
    {
        if (array[i] > avg)
        {
            write_line(std::to_string(array[i]));
        }
    }
}

/**
 * @brief Program entry point.
 *
 * Allows the user to enter up to 20 temperature readings.
 * After input is complete, it calculates and displays:
 * - The average value
 * - The maximum and minimum values
 * - All values above the average
 *
 * @return 0 when the program exits successfully.
 */
int main()
{
    int days_readings = 0;
    string choose = "y";
    std::vector<double> array;
    
    while (choose != "n" && days_readings < 20)
    {
        array.push_back(read_data());
        choose = read_string("Do you want to enter the number of readings? (y/n): ");
        days_readings++;
        if (days_readings == 20)
        {
            write_line("You have reached the maximum number of readings.");
            break;
        }
    }
    
    write_line("");
    write("The average is ");
    write_line(std::to_string(average(array, days_readings)));
    write_line("");
    display_max_min(array, days_readings);
    write_line("");
    write_line("Above average: ");
    above_average(array, days_readings);
    return 0;
}


