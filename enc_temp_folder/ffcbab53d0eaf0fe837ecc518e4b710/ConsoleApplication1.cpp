#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cctype>
#include <iomanip>

using namespace std;

struct Task {
    string description;
    bool isCompleted = false;
};
struct Person {
    string id;
    string name;
    vector<Task> tasksVector;
};

//vector of people
vector <Person> personVector = {};

void addPerson();
void addTask(int index);
void addTaskHandler();
void displayMenu();
void display(string option);
void displaySpecificPersonTask();
void displayAllPersonsTasks();
void displayAllPersons();


int main() {
    // Program to enter a person, assign them tasks, and then save data to a text file
    displayMenu();

    return 0;
}

void displayMenu() {
    int option;
    while (true) {
        cout << endl;
        cout << "Select the option: " << endl;
        cout << "1-Add person: " << endl;
        cout << "2-Add task for person: " << endl;
        cout << "3-Mark task as done: " << endl;
        cout << "4-Delete task: " << endl;
        cout << "5-Delete person: " << endl;
        cout << "6-Display all persons" << endl;
        cout << "7-Display a persons task " << endl;
        cout << "8-Display all persons task " << endl;
        cout << "9-Exit " << endl;
        cout << "Option number: ";

        cin >> option;

        switch (option) {
        case 1:
            addPerson();
            break;
        case 2:
            addTaskHandler();
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            display("people");
            break;
        case 7:
            display("specific person");
            break;
        case 8:
            display("all tasks");
            break;
        case 9:
            
            break;
        default:
            cout << "Invalid Option!!";
            break;
        }
    }
}

string idGenerator() {

    //generation of IDs
    string id, idNum;
    bool idExists = false;
    do {
        // Generate a new ID
        idNum = to_string(rand() % 1000 + 1); // Generates a random number between 1 and 1000
        id = "ID-" + idNum;
        // Check if the ID already 
        for (size_t i = 0; i < personVector.size(); i++) {

            if (personVector[i].id == id) {
                id = idGenerator();
                break;
            }
        }
        idExists = true;

    } while (!idExists); // Keep generating a new ID until a unique one is found

    return id;
}

int indexFinder() {
    cout << "Select person by: " << endl;
    cout << "1- Name " << endl;
    cout << "2- ID " << endl;

    int option;
    cin >> option;
    string name, id, checkedID;

    switch (option) {
    case 1:
        cout << "Enter Name: ";
        cin.ignore();  // Ignore the newline character left in the buffer
        getline(cin, name);

        for (size_t i = 0; i < personVector.size(); i++) {
            if (personVector[i].name == name)
            {
                checkedID = personVector[i].id;
                return i;
                break;
            }
        }

        if (checkedID.empty()) 
        {
            cout << "The Person Name does not exist." << endl;
            return -1;
        }
        break;

    case 2:
        cout << "Enter ID: ";
        cin >> id;

        for (int i = 0; i < personVector.size(); i++) {
            if (personVector[i].id == id) {
                checkedID = personVector[i].id;
                return i;
                break;
            }
        }
        cout << "The ID does not exist." << endl;
        return -1;
        break;

    default:
        cout << "Invalid Option." << endl;
        return -1;
        break;
    }

}

int indexFinderByID(string id) {
    string checkedID;
    for (size_t i = 0; i < personVector.size(); i++) {
        if (personVector[i].id == id) {
            checkedID = personVector[i].id;
            return i;
        }
    }
    return -1;
}

void addPerson() {
    cout << "Enter user name: ";
    string name;
    cin >> name;

    string id = idGenerator();

    Person person;
    person.id = id;
    person.name = name;
    personVector.push_back(person);

    cout << "Person Name: " << name << endl << "Person ID: " << id << endl;
}

void addTaskHandler() {
    
    int index = indexFinder();
    if (index == -1) 
    {
        return;
    }
    else
    {
        addTask(index);
    }

}

void addTask(int index) {

    
        string taskDescription;
        cout << "Enter Task: ";

        getline(cin, taskDescription);
        
        Person person;
        Task task;

        task.description = taskDescription;
        task.isCompleted = false;

        personVector[index].tasksVector.push_back(task);

        cout << "Create another task? (Y/N): ";
        char option;
        cin >> option;

        switch (tolower(option)) {
        case 'y':
            addTask(index);
            break;
        case 'n':
            return; // Exit the loop
        default:
            cout << "Invalid Option" << endl;
            return; // Exit the loop
        }
    
}

void display(string option) {

    //display all people in the list
    //display tasks for a single person
    //display tasks for a all people

    
    if (option == "people") {
        displayAllPersons();
    }
    else if (option == "all tasks")
    {
        displayAllPersonsTasks();
    }
    else if (option == "specific person")
    {
        displaySpecificPersonTask();
    }
    
}

void displaySpecificPersonTask() {

    int i = indexFinder();

    cout << "ID" << setw(10) << "Name" << endl;
    cout << personVector[i].id << setw(10) << personVector[i].name << endl;
    cout << endl;

    for (size_t j = 0; j < personVector[i].tasksVector.size(); j++)
    {
        Task task = personVector[i].tasksVector[j];
        cout << "Task-" << j + 1 << setw(3) << task.description << "Status:" << setw(3) << (task.isCompleted == true ? "Completed" : "Incomplete") << endl;
    }
}
void displayAllPersonsTasks(){

    for (size_t i = 0; i < personVector.size(); i++)
    {
        cout << "ID" << setw(10) << "Name" << endl;
        cout << personVector[i].id << setw(10) << personVector[i].name << endl;
        cout << endl;
        for (size_t j = 0; j < personVector[i].tasksVector.size(); j++) 
        {
            Task task = personVector[i].tasksVector[j];
            cout << "Task-" << j + 1 << setw(3) << task.description << "Status:" << setw(3) << (task.isCompleted == true ? "Completed" : "Incomplete") << endl;
        }
    }
}

void displayAllPersons(){

    cout << setw(10) << "ID" << setw(10) << "Name"<< endl;
    for (size_t i = 0; i < personVector.size(); i++)
    {
        cout << personVector[i].id << setw(10) << personVector[i].name << endl;
    }
}


