#include "splashkit.h"
#include "utilities.h"

using std::to_string;

const int NUM_DAYS = 7;

enum day
{
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
};

day read_day(string prompt)
{
    int day_number;
    write_line(prompt);

    for (int i =0; i< NUM_DAYS;i++)
    {
        day current_day = (day)i;
        write_line(to_string(i+1)+ ": " + to_string(current_day));
    }
    day_number= read_integer("Enter a day number (1-7): ")-1;
    return (day)day_number;
}

string to_string(day d)
{
    switch(d)
    {
        case MONDAY:
        return "Monday";
        case TUESDAY:
        return "Tuesday";
        case WEDNESDAY:
        return "wednesday";
        case THURSDAY:
        return "Thursday";
        case FRIDAY:
        return "Friday";
        case SATURDAY:
        return "Satuday";
        case SUNDAY:
        return "Sunday";
        default:
        return "Invalid day";
    }
}

int main()
{
    day today;
    today = read_day("what day is it today? ");

    write_line("Today is day " + to_string(today));
    return 0;
}
