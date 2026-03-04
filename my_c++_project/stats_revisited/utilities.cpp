#include "utilities.h"
#include "splashkit.h"

string read_string(string prompt)
{
    write(prompt);
    return read_line();
}

int read_integer(string prompt){
    
    string line = read_string(prompt);
   
    while (!is_integer(line))
    {
        write_line("Please enter a whole number.");
        line = read_string(prompt);
    }
    return stoi(line);


}


int read_integer_limit(string prompt, int min, int max)
{
    string line = read_string(prompt);
    int temp = min -1;
    while (temp < min || temp > max)
    {
        while (!is_integer(line))
        {
            write_line("Please enter a whole number.");
            line = read_string(prompt);
        }
        temp = stoi(line);

    }
    
    return temp;
}

double read_double(string prompt)
{
    string line = read_string(prompt);
    while (!is_double(line))
    {
        write_line("Please enter a double number.");
        line = read_string(prompt);
    }

    return convert_to_double(line);
}