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
 * Read an integer value from the user
 *
 * @param prompt the message to show the user
 * @returns the integer value entered
 */
int read_integer(string prompt);

/**
 * Read a double value from the user
 *
 * @param prompt the message to show the user
 * @returns the double value entered
 */
double read_double(string prompt);

#endif