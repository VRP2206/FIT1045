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
    int temp;
    string line;

    while (true)
    {
        line = read_string(prompt);

        if (!is_integer(line)) {
            write_line("Please enter a whole number.");
            continue;
        }

        temp = stoi(line);

        if (temp < min || temp > max) {
            write_line("Please enter a number between " + std::to_string(min) + " and " + std::to_string(max) + ".");
            continue;
        }

        return temp;  
    }
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