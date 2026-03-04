#include "splashkit.h"

/**
 * Find the equivalance sequence value for index n in the fibonacci sequence
 * @param n the index of the value to be find
 */
int loopfibonacci(int n)
{
    int sum = 1;
    int to_add = 0;
    int temp;

    for (int i = 1; i < n; i++)
    {
        temp = sum;    // store the current sequence value
        sum += to_add; // get the next value of the  sequence
        to_add = temp; // it takes the prior value of sequence
    }
    return sum;
}

/**
 * Find the equivalance sequence value for index n in the fibonacci sequence
 * @param n the index of the value to be find
 */
int fibonacci(int n)
{
    if (n < 2)
    {
        return n;
    }
    else
    {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main()
{
    int val;
    write("Enter n: ");
    val = stoi(read_line());
    write_line("loop method: " + std::to_string(loopfibonacci(val)));
    write_line("recursive method: " + std::to_string(fibonacci(val)));

    return 0;
}