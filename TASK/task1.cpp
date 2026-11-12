
#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int rollNo;
    float marks;

    static int studentCount;

public:
    // Parameterized constructor
    Student(string n, int r, float m) {
        name = n;
        rollNo = r;
        marks = m;
        studentCount++;
    }

    // Destructor
    ~Student() {
        studentCount--;
    }

    // Overloaded display functions
    void display() const {
        cout << "\nName: " << name;
        cout << "\nRoll Number: " << rollNo;
        cout << "\nMarks: " << marks << endl;
    }

    void display(bool showMarks) const {
        cout << "\nName: " << name;
        cout << "\nRoll Number: " << rollNo;

        if (showMarks) {
            cout << "\nMarks: " << marks;
        }

        cout << endl;
    }

    // Static member function
    static int getStudentCount() {
        return studentCount;
    }

    // Friend function declaration
    friend void compareMarks(const Student &s1,
                             const Student &s2);

    // Overloading the > operator
    bool operator>(const Student &s) const {
        return marks > s.marks;
    }
};

// Definition of static data member
int Student::studentCount = 0;

// Definition of friend function
void compareMarks(const Student &s1, const Student &s2) {
    cout << "\nFriend Function Comparison:\n";

    if (s1.marks > s2.marks) {
        cout << s1.name << " scored higher than "
             << s2.name << ".\n";
    }
    else if (s1.marks < s2.marks) {
        cout << s2.name << " scored higher than "
             << s1.name << ".\n";
    }
    else {
        cout << "Both students scored equal marks.\n";
    }
}

int main() {
    string name;
    int rollNo;
    float marks;

    cout << "Enter details of Student 1:\n";
    cout << "Name: ";
    getline(cin, name);
    cout << "Roll Number: ";
    cin >> rollNo;
    cout << "Marks: ";
    cin >> marks;

    Student s1(name, rollNo, marks);

    cin.ignore();

    cout << "\nEnter details of Student 2:\n";
    cout << "Name: ";
    getline(cin, name);
    cout << "Roll Number: ";
    cin >> rollNo;
    cout << "Marks: ";
    cin >> marks;

    Student s2(name, rollNo, marks);

    cin.ignore();

    cout << "\nEnter details of Student 3:\n";
    cout << "Name: ";
    getline(cin, name);
    cout << "Roll Number: ";
    cin >> rollNo;
    cout << "Marks: ";
    cin >> marks;

    Student s3(name, rollNo, marks);

    // Display student details
    cout << "\n--- Student Details ---\n";

    s1.display();
    s2.display();
    s3.display(false);

    // Display total number of students
    cout << "\nTotal Students: "
         << Student::getStudentCount() << endl;

    // Friend function demonstration
    compareMarks(s1, s2);

    // Operator overloading demonstration
    cout << "\nOperator Overloading Comparison:\n";

    if (s1 > s3) {
        cout << "Student 1 scored higher than Student 3.\n";
    }
    else if (s3 > s1) {
        cout << "Student 3 scored higher than Student 1.\n";
    }
    else {
        cout << "Both students scored equal marks.\n";
    }

    return 0;
}
