/*
Department maintains student’s database. The file contains roll number, name, division and address.
Write a program to create a sequential file to store and maintain student data. It should allow the
user to add, delete information of student. Display information of particular student. If record of
student does not exist an appropriate message is displayed. If student record is found it should
display the student details.
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    int rollNo;
    string name;
    string division;
    string address;
};

class StudentDatabase {
public:
    void addStudent() {
        ofstream outFile("students.dat", ios::app | ios::binary);
        Student student;

        cout << "Enter roll number: ";
        cin >> student.rollNo;
        cin.ignore();

        cout << "Enter name: ";
        getline(cin, student.name);

        cout << "Enter division: ";
        getline(cin, student.division);

        cout << "Enter address: ";
        getline(cin, student.address);

        outFile.write(reinterpret_cast<char*>(&student), sizeof(student));
        outFile.close();
        cout << "Student added successfully!" << endl;
    }

    void deleteStudent() {
        int rollNo;
        cout << "Enter roll number of student to delete: ";
        cin >> rollNo;

        ifstream inFile("students.dat", ios::binary);
        ofstream outFile("temp.dat", ios::binary);

        Student student;
        bool found = false;

        while (inFile.read(reinterpret_cast<char*>(&student), sizeof(student))) {
            if (student.rollNo == rollNo) {
                found = true;
            } else {
                outFile.write(reinterpret_cast<char*>(&student), sizeof(student));
            }
        }

        inFile.close();
        outFile.close();

        if (found) {
            remove("students.dat");
            rename("temp.dat", "students.dat");
            cout << "Student record deleted!" << endl;
        } else {
            cout << "Student not found!" << endl;
        }
    }

    void displayStudent() {
        int rollNo;
        cout << "Enter roll number of student to display: ";
        cin >> rollNo;

        ifstream inFile("students.dat", ios::binary);

        Student student;
        bool found = false;

        while (inFile.read(reinterpret_cast<char*>(&student), sizeof(student))) {
            if (student.rollNo == rollNo) {
                found = true;
                cout << "Student Details:" << endl;
                cout << "Roll Number: " << student.rollNo << endl;
                cout << "Name: " << student.name << endl;
                cout << "Division: " << student.division << endl;
                cout << "Address: " << student.address << endl;
                break;
            }
        }

        inFile.close();

        if (!found) {
            cout << "Student not found!" << endl;
        }
    }
};

int main() {
    StudentDatabase db;
    int choice;

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Delete Student" << endl;
        cout << "3. Display Student" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                db.addStudent();
                break;
            case 2:
                db.deleteStudent();
                break;
            case 3:
                db.displayStudent();
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
