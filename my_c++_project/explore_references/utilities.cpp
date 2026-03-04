#include "utilities.h"
#include "splashkit.h"

string read_string(string prompt)
{
    write(prompt);
    return read_line();
}

int read_integer(string prompt)
{
    string line = read_string(prompt);
    while (!is_integer(line))
    {
        write_line("Please enter a whole number.");
        line = read_string(prompt);
    }
    return stoi(line);
}

int read_integer_limit(string prompt, int lower_limit, int upper_limit)
{
    string line = read_string(prompt);
    bool flag = false;
    int num;
    do
    {
        while (!is_integer(line))
        {
            write_line("Please enter a whole number.");
            line = read_string(prompt);
        }
        num = stoi(line);
        if (num >= lower_limit && num <= upper_limit)
        {
            flag = true;
        }

    } while (!flag);
    return num;
}