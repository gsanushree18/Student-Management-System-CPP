#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

struct Student {
    int id;
    string name;
    int age;
    float marks;
};

vector<Student> students;

// Save data to file
void saveToFile() {
    ofstream file("students.txt");

    if (!file) {
        cout << "Error: Unable to open file for saving!\n";
        return;
    }

    for (const auto& s : students) {
        file << s.id << " "
             << s.name << " "
             << s.age << " "
             << s.marks << endl;
    }

    file.close();
}

// Load data from file
void loadFromFile() {
    ifstream file("students.txt");

    if (!file) {
        return;
    }

    Student s;

    while (file >> s.id >> s.name >> s.age >> s.marks) {
        students.push_back(s);
    }

    file.close();
}

// Check whether ID already exists
bool idExists(int id) {
    for (const auto& s : students) {
        if (s.id == id) {
            return true;
        }
    }

    return false;
}

// Add student
void addStudent() {
    Student s;

    cout << "Enter ID: ";
    cin >> s.id;

    if (idExists(s.id)) {
        cout << "Student ID already exists!\n";
        return;
    }

    cout << "Enter Name: ";
    cin >> s.name;

    cout << "Enter Age: ";
    cin >> s.age;

    cout << "Enter Marks: ";
    cin >> s.marks;

    students.push_back(s);
    saveToFile();

    cout << "Student added successfully!\n";
}

// Display students
void displayStudents() {
    if (students.empty()) {
        cout << "No students found!\n";
        return;
    }

    cout << "\n--- Student List ---\n";

    for (const auto& s : students) {
        cout << "ID: " << s.id
             << ", Name: " << s.name
             << ", Age: " << s.age
             << ", Marks: " << s.marks
             << endl;
    }
}

// Search student
void searchStudent() {
    int id;

    cout << "Enter ID to search: ";
    cin >> id;

    for (const auto& s : students) {
        if (s.id == id) {
            cout << "\nStudent Found!\n";
            cout << "ID: " << s.id << endl;
            cout << "Name: " << s.name << endl;
            cout << "Age: " << s.age << endl;
            cout << "Marks: " << s.marks << endl;
            return;
        }
    }

    cout << "Student not found!\n";
}

// Delete student
void deleteStudent() {
    int id;

    cout << "Enter ID to delete: ";
    cin >> id;

    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->id == id) {
            students.erase(it);
            saveToFile();

            cout << "Student deleted successfully!\n";
            return;
        }
    }

    cout << "Student not found!\n";
}

// Update student
void updateStudent() {
    int id;

    cout << "Enter ID to update: ";
    cin >> id;

    for (auto& s : students) {
        if (s.id == id) {
            cout << "Enter new name: ";
            cin >> s.name;

            cout << "Enter new age: ";
            cin >> s.age;

            cout << "Enter new marks: ";
            cin >> s.marks;

            saveToFile();

            cout << "Student updated successfully!\n";
            return;
        }
    }

    cout << "Student not found!\n";
}

// Sort students by marks
void sortStudents() {
    if (students.empty()) {
        cout << "No students found!\n";
        return;
    }

    sort(students.begin(), students.end(),
         [](const Student& a, const Student& b) {
             return a.marks > b.marks;
         });

    saveToFile();

    cout << "Students sorted by marks successfully!\n";
}

// Menu
void menu() {
    cout << "\n===== Student Management System =====\n";
    cout << "1. Add Student\n";
    cout << "2. Display Students\n";
    cout << "3. Search Student\n";
    cout << "4. Delete Student\n";
    cout << "5. Update Student\n";
    cout << "6. Sort by Marks\n";
    cout << "7. Exit\n";
}

// Main function
int main() {

    loadFromFile();

    int choice;

    while (true) {

        menu();

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                deleteStudent();
                break;

            case 5:
                updateStudent();
                break;

            case 6:
                sortStudents();
                break;

            case 7:
                saveToFile();
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
