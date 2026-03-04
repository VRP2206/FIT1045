#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
using std::string;

/**
 * Read a string from the user
 *
 * @param prompt the message to show the user
 * @returns the string entered
 */
string read_string(string prompt);

/**
 * Read an integer from the user
 *
 * @param prompt the message to show the user
 * @returns the integer entered
 */
int read_integer(string prompt);

/**
 * Read an integer within a range from the user
 *
 * @param prompt the message to show the user
 * @param lower_limit included lower value that can be enter by the user
 * @param lower_limit included upper value that can be enter by the user
 * @returns the integer entered
 */
int read_integer_limit(string prompt,int lower_limit, int upper_limit);

#endif