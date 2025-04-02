#include "hashtable.h"
using namespace std;
//Comment for second commit

//Constructor
hashTable::hashTable(int size) {
    tableSize = size;
    studentCount = 0;
    table = new Node*[tableSize];

    for (int i = 0; i < tableSize; ++i) {
        table[i] = nullptr;
    }
}

//Destructor
hashTable::~hashTable() {
    //Delete all the nodes in each linked list
    for (int i = 0; i < tableSize; ++i) {
        Node* current = table[i];
        while (current) {
            Node* next = current->getNext();
            delete current;
            current = next;
        }
    }
    delete[] table; //Free up the space for the table
}

//Hash function
int hashTable::hashFunction(int id) {
    return id % tableSize;
}

//Add function
void hashTable::Add(Student* student) {
    int index = hashFunction(student->getID());

    Node* newNode = new Node(student);
    newNode->setNext(table[index]); //Points to the head of the list
    table[index] = newNode; //New node is now the head

    studentCount++;

    Node* current = table[index]; //Checks if resizing is necessary
    int chainLength = 0;
    while (current) {
        chainLength++;
        current = current->getNext();
    }

    if (chainLength > 3) {
        Resize();
    }
}

//Print function
void hashTable::Print(){
    if (studentCount == 0) {
        cout << "There are no students to print!" << endl;
        return;
    }
    for (int i = 0; i < tableSize; ++i) {
        Node* current = table[i];

        while (current != nullptr) { //While running through the hashtable, if the current node is not a nullptr, do this code
            Student* s = current->getStudent(); //Get the details associated with the student
            cout << "ID: " << s->getID() << ", First Name: " << s->getFName() << ", Last Name: "
            << s->getLName() << ", GPA: " << s->getGPA() << endl;
            current = current->getNext();
        }
    }
}

//Delete function
void hashTable::Delete(int id) {
    int index = hashFunction(id);
    Node* current = table[index];
    Node* prev = nullptr;

    if (studentCount == 0) {
        cout << "There are no students to delete!" << endl;
        return;
    }

    while (current) {
        if (current->getStudent()->getID() == id) {
            if (prev) { //If not the first node, bypass this current node
                prev->setNext(current->getNext());
            }
            else { //If this is the first node in the chain, update the table index
                table[index] = current->getNext();
            }

            delete current; //Free the memory as well
            cout << "ID: " << id << " has been deleted." << endl;
            return;
        }

        prev = current; //Move previous forward
        current = current->getNext(); //Move current forward
    }
    //If you finish the loop without finding the student with given ID
    cout << "Student with ID: " << id << " not found." << endl;
}


//Rehash/Resize function
void hashTable::Resize() {
    int newSize = tableSize * 2;
    Node** newTable = new Node*[newSize];

    // Initialize the new table
    for (int i = 0; i < newSize; ++i) {
        newTable[i] = nullptr;
    }

    for (int i = 0; i < tableSize; ++i) {
        Node* current = table[i];
        while (current) {
            Student* oldStudent = current->getStudent();

            // Create a copy of student
            Student* newStudent = new Student(
                oldStudent->getFName(),
                oldStudent->getLName(),
                oldStudent->getID(),
                oldStudent->getGPA()
            );

            // Calculate new hash index directly
            int newIndex = newStudent->getID() % newSize;

            // Add to new table
            Node* newNode = new Node(newStudent);
            newNode->setNext(newTable[newIndex]);
            newTable[newIndex] = newNode;

            // Move to next node
            current = current->getNext();
        }
    }

    // Fixed deletion of old table nodes
    for (int i = 0; i < tableSize; ++i) {
        Node* current = table[i];
        while (current) {
            Node* temp = current;
            current = current->getNext();
            delete temp;
        }
    }

    delete[] table;
    table = newTable;
    tableSize = newSize;

    cout << "Resized hash table to " << tableSize << " slots." << endl;
}
bool hashTable::exists(int id) {
    int index = hashFunction(id);
    Node* current = table[index];
    while (current != nullptr) {
        if (current->getStudent()->getID() == id) {
            return true;
        }
        current = current->getNext();
    }
    return false;
}