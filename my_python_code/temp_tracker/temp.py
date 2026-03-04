days_max = 20

def read_double(prompt):
    """Read and return a valid float number"""
    while True:
        try:
            return float(input(prompt))
        except ValueError:
            print("Please enter a valid number")

def read_data():
    """Read data from user"""
    return read_double("Enter the temperature: ")

def display_max_min(array):
    """Display max and min temperature"""
    if len(array) == 0:
        print("No data entered")
        return
    print(f"Max: {max(array)}")
    print(f"Min: {min(array)}")

def average(array, day_readings):
    """Return the avarage temperature of the entered temperature"""
    return sum(array) / day_readings

def above_average(array, day_readings):
    """Display any temperature that is above the average temperature"""
    avg = average(array, day_readings)
    for temp in array:
        if temp > avg:
            print(temp)

def main():
    days_readings = 0
    choose = "y"
    array = []
    while choose != "n" and days_readings<20:
        array.append(read_data())
        choose = input("Do you want to enter the number of readings? (y/n): ").lower()
        days_readings += 1
        if days_readings == 20:
            print("You have reached the maximum number of readings.")
            break
    print()
    print(f"The average is {average(array, days_readings)}")
    print()
    display_max_min(array)
    print()
    print("Above average: ")
    above_average(array, days_readings)
    

if __name__ == "__main__":
    main()
