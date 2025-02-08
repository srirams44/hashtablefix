#include <iostream>
#include "hashtable.h"
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;

int main() {
    char answer[100];
    hashTable myTable;
    char trash[100];

    while (true) {
        cout << "What would you like to do? (ADD/PRINT/DELETE/GENERATE/QUIT): ";
        cin.getline(answer, 100);

        if (strcasecmp(answer, "ADD") == 0) {
            cout << "Please enter: (firstname) (lastname) (studentid) (GPA)" << endl;
            char fname[100], lname[100];
            int id;
            float gpa;
            cin >> fname >> lname >> id >> gpa;
            cin.getline(trash, 100); // To remove any lingering input
            Student* myStudent = new Student(fname, lname, id, gpa);
            myTable.Add(myStudent);
        }
        else if (strcasecmp(answer, "PRINT") == 0) {
            myTable.Print();
        }
        else if (strcasecmp(answer, "DELETE") == 0) {
            int id;
            cout << "Please enter a student ID to delete: " << endl;
            cin >> id;
            cin.getline(trash, 100); // To clear the buffer
            myTable.Delete(id);
        }
        else if (strcasecmp(answer, "GENERATE") == 0) {
    // Read first names from firstnames.txt
    char fnames[100][50];
    int firstCount = 0;
    ifstream MyReadFile("/Users/sriram/Downloads/FIRSTNAME.txt");
    if (!MyReadFile) {
        cout << "Error opening firstnames.txt" << endl;
        continue;
    }
    int i = 0;
    while (i < 100 && MyReadFile.getline(fnames[i], 50)) {
        fnames[i][49] = '\0'; // Ensure null-terminated
        i++;
    }
    MyReadFile.close();
    firstCount = i;

    // Read last names from lastname.txt
    char lnames[100][50];
    int lastCount = 0;
    ifstream MyReadFile2("/Users/sriram/Downloads/LASTNAME.txt");
    i = 0;
    while (i < 100 && MyReadFile2.getline(lnames[i], 50)) {
        lnames[i][49] = '\0'; // Ensure null-terminated
        i++;
    }
    MyReadFile2.close();
    lastCount = i;

    if (firstCount == 0 || lastCount == 0) {
        cout << "No names found in files." << endl;
        continue;
    }

    // Prompt for number of students to generate
    int times;
    cout << "How many students would you like to generate? ";
    cin >> times;
    cin.ignore(100, '\n'); // Clear input buffer

    srand(time(0)); // Seed random number generator

    static int checkid = 100000; // Retains value between GENERATE commands

    for (int x = 0; x < times; x++) {
        // Generate random indices for names
        int firstIndex = rand() % firstCount;
        int lastIndex = rand() % lastCount;

        // Find next available ID
        while (myTable.exists(checkid)) {
            checkid++;
        }

        // Generate GPA between 0.0 and 4.0
        float gpa = static_cast<float>(rand()) / RAND_MAX * 4.0f;

        // Create and add student
        Student* newStudent = new Student(fnames[firstIndex], lnames[lastIndex], checkid, gpa);
        myTable.Add(newStudent);

        // Output generated student info
        cout << "Generated: " << fnames[firstIndex] << " " << lnames[lastIndex]
             << ", ID: " << checkid << ", GPA: " << fixed << setprecision(2) << gpa << endl;

        checkid += 100000; // Move to next ID
    }
}
        else if (strcasecmp(answer, "QUIT") == 0) {
            cout << "Thank you." << endl;
            return 0;
        }
        else {
            cout << "This is invalid." << endl;
        }
    }
}