import random

def read_integer(prompt):
    """Function to input an integer"""
    while True:
        try:
            return int(input(prompt))
        except ValueError:
            print("Please enter a integer number.")

def read_integer_limit(prompt, min_val, max_val):
    """Function to input an integer within a range"""
    while True:
        value = read_integer(prompt)
        if min_val <= value <= max_val:
            return value
        print("Please enter a integer number in the correct range.")

class Dice:
    def __init__(self, die_face):
        """constructor of the class dice"""
        self.face = die_face
        self.current_value = 0

    def print_die(self):
        """Prints the value obtain after rolling"""
        print(f"{self.face} sides: value is {self.current_value}")

    def roll_die(self):
        """Rolls the dice"""
        self.current_value = random.randint(1, self.face)

def menu():
    print("\n1: Roll die")
    print("2: Get new die")
    print("3: Quit")

def main():
    die = Dice(read_integer("Sides: "))
    
    while True:
        menu()
        choice = read_integer_limit("> ", 1, 3)
        
        if choice == 1:
            die.roll_die()
            die.print_die()
        elif choice == 2:
            die = Dice(read_integer("Sides: "))
        elif choice == 3:
            break

if __name__ == "__main__":
    main()