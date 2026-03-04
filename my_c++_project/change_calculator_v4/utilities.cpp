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