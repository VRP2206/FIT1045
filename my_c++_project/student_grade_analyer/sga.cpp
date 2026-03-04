#include "splashkit.h"
#include <vector>

const int max_student = 20;

/**
 * @brief Reads a string from user input.
 *
 * @param prompt The message shown to the user.
 * @return The entered string.
 */
string read_string(string prompt){
    string line;
    write(prompt);
    line = read_line();
    return line;
}

/**
 * @brief Reads and validates an integer within a given range.
 *
 * Keeps asking until the user enters an integer between min and max.
 *
 * @param prompt The message to display before input.
 * @param min The minimum valid value.
 * @param max The maximum valid value.
 * @return A validated integer.
 */
int read_int_limit(string prompt, int min, int max){
    string line = read_string(prompt);
    while (!is_integer(line) || stoi(line) < min || stoi(line) > max){
        write_line("Please enter a valid number");
        line = read_string(prompt);
    } 
    return stoi(line);
}

/**
 * @brief Adds a new student grade to the grade list.
 *
 * Prompts for a grade (0–100) and stores it in the vector.
 *
 * @param grades A vector storing all student grades.
 */
void add_stu_grade(vector<int> &grades){
    int grade;
    grade = read_int_limit("Enter the grade: ", 0, 100);
    grades.push_back(grade);
    write_line("Grade added");
}

/**
 * @brief Calculates and prints the average grade.
 *
 * @param grades A vector storing all student grades.
 * @param no_stu Number of students.
 */
void avg_grade(vector<int> &grades, int no_stu){
    int total = 0;
    for (int i = 0; i < no_stu; i++){
        total += grades[i];
    }
    write_line("The average grade is: " + std::to_string(total/no_stu));
}

/**
 * @brief Calculates and prints the pass rate (grades >= 50).
 *
 * @param grades A vector storing all student grades.
 * @param no_stu Number of students.
 */
void pass_rate(vector<int> &grades, int no_stu){
    int pass = 0;
    for (int i = 0; i < no_stu; i++){
        if (grades[i] >= 50){
            pass +=1;
        }
    }

    write_line("p= " + std::to_string(pass));
    double pass_rate = convert_to_double(std::to_string(pass))/convert_to_double(std::to_string(no_stu)) * 100;
    write_line("The pass rate is: " + std::to_string(pass_rate));
}

/**
 * @brief Calculates and prints the high distinction rate (grades >= 80).
 *
 * @param grades A vector storing all student grades.
 * @param no_stu Number of students.
 */
void high_disc_rate(vector<int> &grades, const int &no_stu){
    int disc = 0;
    for (int i = 0; i < no_stu; i++){
        if (grades[i] >= 80){
            disc +=1;
        }
    }
    write_line("hd= " + std::to_string(disc));
    double high_disc = convert_to_double(std::to_string(disc))/convert_to_double(std::to_string(no_stu)) * 100; 
    write_line("The high distinction rate is: " + std::to_string(high_disc));
}

/**
 * @brief Entry point for the student grade analyzer program.
 *
 * Prompts for the number of students, collects grades, and prints:
 * - The average grade
 * - The pass rate
 * - The high distinction rate
 */
int main(){
    vector<int> grades;
    int no_stu;
    no_stu = read_int_limit("Enter the number of students: ", 1, max_student);
    for (int i = 0; i < no_stu; i++){
        add_stu_grade(grades);
    }
    write_line("stu: " + std::to_string(no_stu));
    write_line("");
    avg_grade(grades, no_stu);
    write_line("");
    pass_rate(grades, no_stu);
    write_line("");
    high_disc_rate(grades, no_stu);
    write_line("");
    return 0;
}