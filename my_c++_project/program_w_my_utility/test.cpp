#include "utilities.h"
#include "splashkit.h"

using std::to_string;

int main()
{
  string name;
  name = read_string("Please enter your name: ");

  int age;
  age = read_integer("Please enter your age: ");

  write_line("Hello " + name + " " + to_string(age));
}