import random
from abc import ABC, abstractmethod

def read_string(prompt):
    """Prompt the user and return a string."""
    return input(prompt)

def read_integer(prompt):
    """Prompt the user and return an integer. Keeps asking until valid."""
    while True:
        try:
            return int(input(prompt))
        except ValueError:
            print("Please enter a integer number.")

class UserAction(ABC):
    """Abstract base class for all user actions."""
    
    @abstractmethod
    def show(self, option_number):
        pass
    
    @abstractmethod
    def run(self):
        pass
    
    def selectable(self):
        return True

class DividerAction(UserAction):
    """A non-selectable divider used for menu formatting."""
    
    def __init__(self, text="----------------"):
        self.text = text
    
    def show(self, option_number):
        print(f"   {self.text}")
    
    def run(self):
        pass  # does nothing
    
    def selectable(self):
        return False

class SayHelloAction(UserAction):
    """Action: Prompt the user's name and greet them."""
    
    def show(self, option_number):
        print(f"{option_number}: Say Hello")
    
    def run(self):
        name = read_string("Enter your name: ")
        print(f"Hello, {name}! Nice to meet you.")

class SimpleMathAction(UserAction):
    """Action: Simple math quiz (addition)."""
    
    def show(self, option_number):
        print(f"{option_number}: Simple Math Test")
    
    def run(self):
        a = random.randint(1, 10)
        b = random.randint(1, 10)
        answer = read_integer(f"What is {a} + {b}? ")
        if answer == a + b:
            print("Correct!")
        else:
            print(f"Oops, the correct answer was {a + b}")

class GuessDieRollAction(UserAction):
    """Action: Guess the roll of a die."""
    
    def show(self, option_number):
        print(f"{option_number}: Guess the Die Roll")
    
    def run(self):
        roll = random.randint(1, 6)
        guess = read_integer("Guess the die roll (1-6): ")
        if guess == roll:
            print("Wow! You guessed it right!")
        else:
            print(f"Sorry, the die rolled {roll}.")

class NumberGuessingAction(UserAction):
    """Action: Guess a random number between 1-20."""
    
    def __init__(self):
        self.high_score = 0
    
    def show(self, option_number):
        print(f"{option_number}: Number Guessing Game")
    
    def run(self):
        number = random.randint(1, 20)
        attempts = 0
        print("I'm thinking of a number between 1 and 20!")
        
        while True:
            attempts += 1
            guess = read_integer(f"Attempt {attempts} - Your guess: ")
            
            if guess == number:
                print(f"Correct! You got it in {attempts} attempts!")
                if self.high_score == 0 or attempts < self.high_score:
                    self.high_score = attempts
                    print(f"New best score: {self.high_score} attempts!")
                break
            elif guess < number:
                print("Too low!")
            else:
                print("Too high!")

def choose_and_run(actions):
    """Show a menu of actions and let the user choose and run them."""
    while True:
        print("\n=== Menu ===")
        option_number = 1
        index_map = []
        
        for i, action in enumerate(actions):
            if action.selectable():
                action.show(option_number)
                index_map.append(i)
                option_number += 1
            else:
                action.show(-1)
        
        print("-1: Quit")
        choice = read_integer("Option: ")
        
        if choice == -1:
            break
        
        if 1 <= choice <= len(index_map):
            actions[index_map[choice - 1]].run()
        else:
            print("Invalid option, try again.")

def main():
    """Program entry point."""
    actions = [
        SayHelloAction(),
        SimpleMathAction(),
        DividerAction("=== Games ==="),
        GuessDieRollAction(),
        NumberGuessingAction(),
        DividerAction("=== End ===")
    ]
    
    choose_and_run(actions)
    print("Goodbye!")

if __name__ == "__main__":
    main()