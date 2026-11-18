
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <sstream>

using namespace std;

// Function to validate marks
void validateMark(int mark) {
    if (mark < 0 || mark > 100) {
        throw invalid_argument("Marks must be between 0 and 100.");
    }
}

// Function to read valid integer input
int readInt(const string& prompt) {
    int value;
    string line;

    while (true) {
        cout << prompt;
        getline(cin, line);

        stringstream ss(line);
        char extra;

        if (ss >> value && !(ss >> extra)) {
            return value;
        }

        cout << "Invalid input. Please enter an integer.\n";
    }
}

// Function to read student name
string readName() {
    string name;

    while (true) {
        cout << "Enter student name: ";
        getline(cin, name);

        if (!name.empty()) {
            return name;
        }

        cout << "Name cannot be empty.\n";
    }
}

// Base class
class Student {
protected:
    int rollNumber;
    string name;

public:
    Student(int roll, string n)
        : rollNumber(roll), name(n) {}

    virtual void display() const {
        cout << "Roll Number: " << rollNumber << endl;
        cout << "Name: " << name << endl;
    }

    int getRollNumber() const {
        return rollNumber;
    }

    string getName() const {
        return name;
    }

    virtual ~Student() {}
};

// Derived class
class Result : public Student {
private:
    array<int, 5> marks;

public:
    Result(int roll, string n, array<int, 5> m)
        : Student(roll, n), marks(m) {

        for (int mark : marks) {
            validateMark(mark);
        }
    }

    int getTotal() const {
        int total = 0;

        for (int mark : marks) {
            total += mark;
        }

        return total;
    }

    double getPercentage() const {
        return getTotal() / 5.0;
    }

    bool isPassed() const {
        for (int mark : marks) {
            if (mark < 35) {
                return false;
            }
        }

        return true;
    }

    // Runtime polymorphism
    void display() const override {
        Student::display();

        cout << "Subject Marks: ";

        for (int mark : marks) {
            cout << mark << " ";
        }

        cout << "\nTotal Marks: " << getTotal() << "/500";

        cout << fixed << setprecision(2);
        cout << "\nPercentage: " << getPercentage() << "%";

        cout << "\nResult: "
             << (isPassed() ? "PASS" : "FAIL") << endl;

        cout << "-----------------------------\n";
    }

    const array<int, 5>& getMarks() const {
        return marks;
    }
};

// Function to add student records
void addStudent(vector<Result>& records) {
    int roll = readInt("Enter roll number: ");

    if (roll <= 0) {
        cout << "Roll number must be positive.\n";
        return;
    }

    bool exists = any_of(records.begin(), records.end(),
        [roll](const Result& r) {
            return r.getRollNumber() == roll;
        });

    if (exists) {
        cout << "A student with this roll number already exists.\n";
        return;
    }

    string name = readName();

    array<int, 5> marks;

    cout << "\nEnter marks for five subjects:\n";

    for (int i = 0; i < 5; i++) {
        while (true) {
            int mark = readInt("Subject " + to_string(i + 1) + ": ");

            try {
                validateMark(mark);
                marks[i] = mark;
                break;
            }
            catch (const invalid_argument& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    }

    try {
        records.emplace_back(roll, name, marks);
        cout << "\nStudent record added successfully!\n";
    }
    catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }
}

// Function to display all student records
void displayStudents(const vector<Result>& records) {
    if (records.empty()) {
        cout << "No student records available.\n";
        return;
    }

    cout << "\n===== STUDENT RECORDS =====\n";

    for (const Result& record : records) {
        const Student* ptr = &record;
        ptr->display();
    }
}

// Function to search students scoring above specified marks
void searchStudents(const vector<Result>& records) {
    if (records.empty()) {
        cout << "No student records available.\n";
        return;
    }

    int threshold = readInt(
        "Enter minimum total marks to search (out of 500): ");

    int count = 0;

    cout << "\n===== STUDENTS ABOVE "
         << threshold << " MARKS =====\n";

    for_each(records.begin(), records.end(),
        [threshold, &count](const Result& r) {

            if (r.getTotal() > threshold) {
                r.display();
                count++;
            }
        });

    if (count == 0) {
        cout << "No students found above the specified marks.\n";
    }
    else {
        cout << "Total students found: " << count << endl;
    }
}

// Function to save records to a file
void saveToFile(const vector<Result>& records) {
    ofstream file("student_records.txt");

    if (!file) {
        cout << "Error opening file for writing.\n";
        return;
    }

    for (const Result& r : records) {
        file << r.getRollNumber() << " "
             << quoted(r.getName()) << " ";

        for (int mark : r.getMarks()) {
            file << mark << " ";
        }

        file << endl;
    }

    file.close();

    cout << "Student records saved successfully!\n";
}

// Function to retrieve records from a file
void loadFromFile(vector<Result>& records) {
    ifstream file("student_records.txt");

    if (!file) {
        cout << "Unable to open student_records.txt.\n";
        return;
    }

    vector<Result> loadedRecords;

    int roll, m1, m2, m3, m4, m5;
    string name;

    while (file >> roll >> quoted(name)
                >> m1 >> m2 >> m3 >> m4 >> m5) {

        try {
            array<int, 5> marks = {m1, m2, m3, m4, m5};

            loadedRecords.emplace_back(roll, name, marks);
        }
        catch (const invalid_argument& e) {
            cout << "Skipping invalid record: "
                 << e.what() << endl;
        }
    }

    records = loadedRecords;

    file.close();

    cout << loadedRecords.size()
         << " student record(s) retrieved successfully!\n";
}

// Main function
int main() {
    vector<Result> records;

    int choice;

    do {
        cout << "\n====================================\n";
        cout << "   STUDENT RESULT MANAGEMENT SYSTEM\n";
        cout << "====================================\n";

        cout << "1. Add Student Record\n";
        cout << "2. Display All Student Records\n";
        cout << "3. Search Students Above Specified Marks\n";
        cout << "4. Save Records to File\n";
        cout << "5. Retrieve Records from File\n";
        cout << "6. Exit\n";

        cout << "====================================\n";

        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1:
                addStudent(records);
                break;

            case 2:
                displayStudents(records);
                break;

            case 3:
                searchStudents(records);
                break;

            case 4:
                saveToFile(records);
                break;

            case 5:
                loadFromFile(records);
                break;

            case 6:
                cout << "Exiting Student Result Management System.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}
