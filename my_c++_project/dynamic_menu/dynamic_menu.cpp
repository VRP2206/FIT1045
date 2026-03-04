#include "splashkit.h"

/**
 * @brief Prompt the user and return a string.
 *
 * @param prompt The message displayed to the user
 * @return The string entered by the user
 */
string read_string(string prompt)
{
    write(prompt);
    return read_line();
}

/**
 * @brief Prompt the user and return an integer.
 *
 * Keeps asking until a valid integer is entered.
 *
 * @param prompt The message displayed to the user
 * @return The integer entered by the user
 */
int read_integer(string prompt){
    string line = read_string(prompt);
    
    while (!is_integer(line))
    {
        write_line("Please enter a integer number.");
        line = read_string(prompt);
    }
    return stoi(line);
}

/**
 * @brief Abstract base class for all user actions.
 *
 * Defines the interface for showing menu options and executing actions.
 */
class UserAction
{
public:
    virtual ~UserAction() {}
    virtual void show(int optionNumber) const = 0;
    virtual void run() = 0;
    virtual bool selectable() const { return true; }
};


/**
 * @brief A non-selectable divider used for menu formatting.
 */
class DividerAction : public UserAction
{
    string text;

public:
    DividerAction(string t = "----------------") : text(t) {}
    void show(int) const override
    {
        write_line("   " + text);
    }
    void run() override {} // does nothing
    bool selectable() const override { return false; }
};

/**
 * @brief Action: Prompt the user’s name and greet them.
 */
class SayHelloAction : public UserAction
{
public:
    void show(int optionNumber) const override
    {
        write_line(std::to_string(optionNumber) + ": Say Hello");
    }

    void run() override
    {
        string name = read_string("Enter your name: ");
        write_line("Hello, " + name + "! Nice to meet you.");
    }
};

/**
 * @brief Action: Simple math quiz (addition).
 */
class SimpleMathAction : public UserAction
{
public:
    void show(int optionNumber) const override
    {
        write_line(std::to_string(optionNumber) + ": Simple Math Test");
    }

    void run() override
    {
        int a = rnd(1, 10);
        int b = rnd(1, 10);
        int answer = read_integer("What is " + std::to_string(a) + " + " + std::to_string(b) + "? ");
        if (answer == a + b)
            write_line("Correct!");
        else
            write_line("Oops, the correct answer was " + std::to_string(a + b));
    }
};

/**
 * @brief Action: Guess the roll of a die.
 */
class GuessDieRollAction : public UserAction
{
public:
    void show(int optionNumber) const override
    {
        write_line(std::to_string(optionNumber) + ": Guess the Die Roll");
    }

    void run() override
    {
        int roll = rnd(1, 6);
        int guess = read_integer("Guess the die roll (1-6): ");
        if (guess == roll)
            write_line("Wow! You guessed it right!");
        else
            write_line("Sorry, the die rolled " + std::to_string(roll) + ".");
    }
};

/**
 * @brief A dynamic array class for storing UserAction pointers.
 *
 * Automatically resizes when capacity is exceeded.
 */
class ActionArray
{
private:
    UserAction **data;
    int capacity;
    int length;

    void resize()
    {
        int newCap = capacity * 2;
        UserAction **newData = new UserAction *[newCap];
        for (int i = 0; i < length; i++)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCap;
    }

public:
    ActionArray(int initialCap = 4)
    {
        capacity = initialCap;
        length = 0;
        data = new UserAction *[capacity];
    }

    ~ActionArray()
    {
        for (int i = 0; i < length; i++)
            delete data[i];
        delete[] data;
    }

    void add(UserAction *action)
    {
        if (length == capacity)
            resize();
        data[length++] = action;
    }

    int size() const { return length; }

    UserAction *get(int index) const { return data[index]; }
};

/**
 * @brief Show a menu of actions and let the user choose and run them.
 *
 * @param actions Reference to an ActionArray containing menu actions
 */
void choose_and_run(ActionArray &actions)
{
    while (true)
    {
        write_line("\n=== Menu ===");
        int optionNumber = 1;

        int mapSize = actions.size();
        int *indexMap = new int[mapSize];
        int mapCount = 0;

        for (int i = 0; i < actions.size(); i++)
        {
            if (actions.get(i)->selectable())
            {
                actions.get(i)->show(optionNumber);
                indexMap[mapCount++] = i;
                optionNumber++;
            }
            else
            {
                actions.get(i)->show(-1);
            }
        }

        write_line("-1: Quit");
        int choice = read_integer("Option: ");

        if (choice == -1)
        {
            delete[] indexMap;
            break;
        }

        if (choice > 0 && choice <= mapCount)
        {
            actions.get(indexMap[choice - 1])->run();
        }
        else
        {
            write_line("Invalid option, try again.");
        }

        delete[] indexMap;
    }
}

/**
 * @brief Program entry point.
 */
int main()
{
    ActionArray actions;
    actions.add(new SayHelloAction());
    actions.add(new SimpleMathAction());
    actions.add(new DividerAction("=== Games ==="));
    actions.add(new GuessDieRollAction());

    choose_and_run(actions);

    write_line("Goodbye!");
    return 0;
}
