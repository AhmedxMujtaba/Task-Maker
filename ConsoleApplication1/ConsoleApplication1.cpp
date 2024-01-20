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
void displaySpecificPersonTask(int index);
void displayAllPersonsTasks();
void displayAllPersons();
void markTaskStatus();


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
        cout << "3-Mark task Status: " << endl;
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
            markTaskStatus();
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

    cout << setw(5) << "ID" << setw(15) << "Name" << endl;
    cout << setw(5) << personVector[i].id << setw(15) << personVector[i].name << endl;
    cout << endl;

    for (size_t j = 0; j < personVector[i].tasksVector.size(); j++) {
        Task task = personVector[i].tasksVector[j];
        cout << setw(5) << "Task-" << j + 1 << setw(15) << task.description << setw(10) << "Status:" << setw(5) << (task.isCompleted == true ? "O" : "X") << endl;
    }
}

void displaySpecificPersonTask(int index) {
    int i = index;

    cout << setw(5) << "ID" << setw(15) << "Name" << endl;
    cout << setw(5) << personVector[i].id << setw(15) << personVector[i].name << endl;
    cout << endl;

    for (size_t j = 0; j < personVector[i].tasksVector.size(); j++) {
        Task task = personVector[i].tasksVector[j];
        cout << setw(5) << "Task-" << j + 1 << setw(15) << task.description << setw(10) << "Status:" << setw(5) << (task.isCompleted == true ? "O" : "X") << endl;
    }
}

void displayAllPersonsTasks() {
    cout << setw(5) << "ID" << setw(15) << "Name" << endl;

    for (size_t i = 0; i < personVector.size(); i++) {
        cout << setw(5) << personVector[i].id << setw(15) << personVector[i].name << endl;
        cout << endl;

        for (size_t j = 0; j < personVector[i].tasksVector.size(); j++) {
            Task task = personVector[i].tasksVector[j];
            cout << setw(5) << "Task-" << j + 1 << setw(15) << task.description << setw(10) << "Status:" << setw(5) << (task.isCompleted == true ? "O" : "X") << endl;
        }
    }
}

void displayAllPersons() {
    cout << setw(5) << "ID" << setw(15) << "Name" << endl;

    for (size_t i = 0; i < personVector.size(); i++) {
        cout << setw(5) << personVector[i].id << setw(15) << personVector[i].name << endl;
    }
}

void markTaskStatus()
{
    //first we need to get the tasks for the person
    int index = indexFinder();
    displaySpecificPersonTask(index);

    cout << "Select Task Number to Mark as Completed/Incomplete:" << endl;
    cout << "Task Number: " << endl;

    Person person = personVector[index];
    vector <Task> currentTaskVector = person.tasksVector;
    
    int taskNumber;
    cin >> taskNumber;
    
    if(taskNumber > currentTaskVector.size())
    {
        cout << "Invalid Task Number:" << endl;
        return;
    }

    //reducing 1 because index beign from 0 of the Task vecotor containing tasks of the person.
    taskNumber -= 1;

    Task currentTask = currentTaskVector[taskNumber];
    
    cout << "Mark Task as: " << endl;
    cout << "1- Complete: " << endl;
    cout << "2- Incomplete: " << endl;
    cout << "0- Cancel: " << endl;

    int option;
    cin >> option;

    switch (option)
    {
    case 0:
        break;
    case 1:
        currentTask.isCompleted = true;
        cout << "Task Completed " << endl;
        break;
    case 2:
        currentTask.isCompleted = false;
        cout << "Task Incomplete " << endl;
        break;
    default:
        cout << "Invalid Option " << endl;
        break;
    }
}
