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
 * read an integer from the user
 * 
 * @param prompt the message to show the user
 * 
 * @returns the integer entered
 */
int read_integer(string prompt);


/**
 * Read an integer from the user
 *
 * @param prompt the message to show the user
 * @param min minimum value accepted
 * @param max maximum value accepted
 * @returns the integer entered
 */
int read_integer_limit(string prompt, int min, int max);


/**
 * Read an double from the user
 *
 * @param prompt the message to show the user
 * @returns the double entered
 */
double read_double(string prompt);

#endif
