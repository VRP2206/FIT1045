max_student = 20

def read_integer_limit(prompt, min_val, max_val):
    """Prompt the user for an integer input within a given range."""
    while True:
        try:
            user_input = int(input(prompt))
            if min_val <= user_input <= max_val:
                return user_input
            print("Please enter a valid number")
        except ValueError:
            print("Please enter a valid number")

def add_stu_grade(grades):
    """Add a student grade to the list."""
    grade = read_integer_limit("Enter the grade: ", 0, 100)
    grades.append(grade)
    print("Grade added")

def avg_grade(grades, no_stu):
    """Print the average grade of the students."""
    total = sum(grades[:no_stu])
    print(f"The average grade is: {total // no_stu}")

def pass_rate(grades, no_stu):
    """Print the percentage of students who passed (grade >= 50)."""
    pass_count = sum(1 for grade in grades[:no_stu] if grade >= 50)
    rate = (pass_count / no_stu) * 100
    print(f"The pass rate is: {rate}")

def high_disc_rate(grades, no_stu):
    """Print the percentage of students with high distinction (grade >= 80)."""
    disc_count = sum(1 for grade in grades[:no_stu] if grade >= 80)
    rate = (disc_count / no_stu) * 100
    print(f"The high distinction rate is: {rate}")

def main():
    grades = []
    no_stu = read_integer_limit("Enter the number of students: ", 1, max_student)
    
    for _ in range(no_stu):
        add_stu_grade(grades)
    
    
    avg_grade(grades, no_stu)
    print()
    pass_rate(grades, no_stu)
    print()
    high_disc_rate(grades, no_stu)
    print()

if __name__ == "__main__":
    main()