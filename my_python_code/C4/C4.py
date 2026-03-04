import streamlit as st   
import csv
import unittest
import io
import os
import statistics


STUDENT_FILE = "students.csv"   #file path, create it if not found.

def init_student_file():
    """Ensure the student CSV file exists with headers."""
    if not os.path.exists(STUDENT_FILE):
        with open(STUDENT_FILE, "w", newline="") as f:
            writer = csv.DictWriter(f, fieldnames=["name", "age", "grade"])
            writer.writeheader()


def load_students():
    """Load students from the constant CSV file."""
    students = []
    init_student_file()
    with open(STUDENT_FILE, "r") as f:
        reader = csv.DictReader(f)
        for row in reader:
            students.append({"name": row["name"], "age": int(row["age"]), "grade": float(row["grade"])})
    return students


def save_student(student):
    """Append a single student to the CSV file."""
    init_student_file()
    with open(STUDENT_FILE, "a", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=["name", "age", "grade"])
        writer.writerow(student)


def format_student(student):
    """Return a nicely formatted string for a student dict."""
    return f"👩‍🎓 {student['name']:<15} | Age: {student['age']:<2} | Grade: {student['grade']}%"


def add_student(students, name, age, grade):
    """Add a new student to the list and save to file."""
    student = {"name": name, "age": int(age), "grade": float(grade)}
    students.append(student)
    save_student(student)
    return students


def compute_stats(students):
    """Compute average, highest and lowest grade student."""
    if not students:
        return None, None, None

    avg = statistics.mean([s["grade"] for s in students])
    top_student = max(students, key=lambda s: s["grade"])
    bottom_student = min(students, key=lambda s: s["grade"])
    return avg, top_student, bottom_student


#class testing- it would have been it own sperate file if the file submission was not limited to 1.
class TestStudentLog(unittest.TestCase):

    def test_add_student(self):
        students = []
        updated = add_student(students, "Alice", 20, 90)
        self.assertEqual(updated[-1]["name"], "Alice")

    def test_format_student(self):
        student = {"name": "Bob", "age": 18, "grade": 75}
        formatted = format_student(student)
        self.assertIn("Bob", formatted)
        self.assertIn("75", formatted)


def run_tests():
    """Run unittest inside the Streamlit app and return results as a string."""
    buffer = io.StringIO()
    runner = unittest.TextTestRunner(stream=buffer, verbosity=2)
    suite = unittest.TestLoader().loadTestsFromTestCase(TestStudentLog)
    runner.run(suite)
    return buffer.getvalue()


#UI start here, usually it would be in it own file but since the file submission is limited to 1, I have included it here.
st.title("📘 Student Log Application")

# Sidebar for options
st.sidebar.header("Options")
menu = st.sidebar.radio("Choose Action", ["Student Log", "Run Unit Tests"])

if menu == "Student Log":
    # Initialize students from file
    if "students" not in st.session_state:
        st.session_state.students = load_students()

    # Create tabs
    tab1, tab2 = st.tabs(["📝 Student List", "📊 Stats"])

    with tab1:
        # Add new student
        st.subheader("➕ Add a New Student")
        with st.form("student_form"):
            name = st.text_input("Name")
            age = st.number_input("Age", min_value=5, max_value=100, step=1)
            grade = st.number_input("Grade (%)", min_value=0, max_value=100, step=1)
            submitted = st.form_submit_button("Add Student")

            if submitted and name:
                st.session_state.students = add_student(st.session_state.students, name, age, grade)
                st.success(f"Student {name} added and saved!")

        # Display students
        st.subheader("📋 Student List")
        if st.session_state.students:
            for s in st.session_state.students:
                st.write(format_student(s))
        else:
            st.info("No students yet. Add some!")

        # Search
        st.subheader("🔍 Search Student")
        search_name = st.text_input("Enter name to search:")
        if search_name:
            results = [s for s in st.session_state.students if search_name.lower() in s["name"].lower()]
            if results:
                st.success("Found:")
                for s in results:
                    st.write(format_student(s))
            else:
                st.error("No student found.")

    with tab2:
        st.subheader("📊 Student Statistics")
        avg, top, bottom = compute_stats(st.session_state.students)
        if avg is None:
            st.info("No data available.")
        else:
            st.write(f"📈 **Average Grade:** {avg:.2f}%")
            st.write(f"🥇 **Top Student:** {top['name']} ({top['grade']}%)")
            st.write(f"🥉 **Lowest Student:** {bottom['name']} ({bottom['grade']}%)")

elif menu == "Run Unit Tests":
    st.subheader("🧪 Running Unit Tests")
    result_text = run_tests()
    st.text(result_text)
