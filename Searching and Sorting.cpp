/*
Consider a student database of SEIT class (at least 15 records). Database contains different fields of
every student like Roll No, Name and SGPA.(array of structure)
a) Design a roll call list, arrange list of students according to roll numbers in ascending order (Use
Bubble Sort)
b) Arrange list of students alphabetically. (Use Insertion sort)
c) Arrange list of students to find out first ten toppers from a class. (Use Quick sort)
d) Search students according to SGPA. If more than one student having same SGPA, then print list
of all students having same SGPA.
e) Search a particular student according to name using binary search without recursion. (all the student records having the presence of search key should be displayed)
*/
#include <iostream>
#include <cstring>
using namespace std;

struct Student {
    int roll_no;
    char name[50];
    float SGPA;
};
Student students[15] = {
    {101, "Pratik", 8.5},
    {102, "Varun", 7.2},
    {103, "Aniket", 9.1},
    {104, "Nikhil", 8.0},
    {105, "Narendra", 7.5},
    {106, "Vedant", 8.2},
    {107, "Paritosh", 9.4},
    {108, "Sahil", 6.8},
    {109, "Rahul", 7.9},
    {110, "Yash", 8.3},
    {111, "Arjun", 6.7},
    {112, "Roshan", 9.0},
    {113, "Ishaan", 7.6},
    {114, "Virat", 8.1},
    {115, "Rohit", 9.3}
};

void SortByRollNo(Student students[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (students[j].roll_no > students[j+1].roll_no) {
                Student temp = students[j];
                students[j] = students[j+1];
                students[j+1] = temp;
            }
        }
    }
}

void SortByName(Student students[], int n) {
    for (int i = 1; i < n; i++) {
        Student key = students[i];
        int j = i - 1;
        while (j >= 0 && strcmp(students[j].name, key.name) > 0) {
            students[j + 1] = students[j];
            j = j - 1;
        }
        students[j + 1] = key;
    }
}

int partition(Student students[], int low, int high) {
    float pivot = students[high].SGPA;
    int i = (low - 1);  
    for (int j = low; j < high; j++) {
        if (students[j].SGPA > pivot) {  
            i++;
            Student temp = students[i];
            students[i] = students[j];
            students[j] = temp;
        }
    }
    Student temp = students[i + 1];
    students[i + 1] = students[high];
    students[high] = temp;
    return (i + 1);
}

void quickSort(Student students[], int low, int high) {
    if (low < high) {
        int pi = partition(students, low, high);
        quickSort(students, low, pi - 1);
        quickSort(students, pi + 1, high);
    }
}

void getTopToppers(Student students[], int n) {
    quickSort(students, 0, n-1);
    cout << "Top 10 Students based on SGPA:" << endl;
    for (int i = 0; i < 10 && i < n; i++) {
        cout << students[i].name << " - " << students[i].SGPA << endl;
    }
}

void searchBySGPA(Student students[], int n, float searchSGPA) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (students[i].SGPA == searchSGPA) {
            cout << students[i].name << " - " << students[i].SGPA << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No student found with SGPA " << searchSGPA << endl;
    }
}

void SearchByName(Student students[], int n, const char* searchName) {
    int low = 0;
    int high = n - 1;
    bool found = false;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int result = strcmp(students[mid].name, searchName);
        if (result == 0) {
            cout << "Found: " << students[mid].name << " - " << students[mid].SGPA << endl;
            found = true;
            int left = mid - 1;
            while (left >= low && strcmp(students[left].name, searchName) == 0) {
                cout << "Found: " << students[left].name << " - " << students[left].SGPA << endl;
                left--;
            }
            int right = mid + 1;
            while (right <= high && strcmp(students[right].name, searchName) == 0) {
                cout << "Found: " << students[right].name << " - " << students[right].SGPA << endl;
                right++;
            }
            break;
        }
        if (result < 0)
            low = mid + 1;
        else
            high = mid - 1;
    }
    if (!found)
        cout << "Student with name " << searchName << " not found." << endl;
}

int main() {
    int n = 15;  
    SortByRollNo(students, n);
    cout << "Students sorted by Roll No:" << endl;
    for (int i = 0; i < n; i++) {
        cout << students[i].roll_no << " " << students[i].name << " " << students[i].SGPA << endl;
    }
    SortByName(students, n);
    cout << "\nStudents sorted alphabetically by name:" << endl;
    for (int i = 0; i < n; i++) {
        cout << students[i].roll_no << " " << students[i].name << " " << students[i].SGPA << endl;
    }
    getTopToppers(students, n);
    cout << "\nSearch students with SGPA 8.5:" << endl;
    searchBySGPA(students, n, 8.5);
    cout << "\nSearch for student named 'Bob':" << endl;
    SearchByName(students, n, "Bob");
    return 0;
}
