#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "node.h"
#include "student.h"
#include <iostream>

//Comment for second commit

class hashTable {
public:
    hashTable(int size = 100);
    ~hashTable();

    void Add(Student* student);
    void Print();
    void Delete(int id);
    void Resize();
    int hashFunction(int id); //Hash function to hash the student id's
    bool exists(int id);


private:
    Node** table; //Array of linked lists
    int tableSize; //Size of table (duh!)
    int studentCount; //Tracking number of students for resizing


};



#endif //HASHTABLE_H
