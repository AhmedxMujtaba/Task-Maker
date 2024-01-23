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
void deletePerson();
void deleteTask();


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
            deleteTask();
            break;
        case 5:
            deletePerson();
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
            return;
            break;
        default:
            cout << "Invalid Option!!";
            break;
        }
    }
}

string idGenerator() {
    string newID, lastID, lastIdNumberString;

    if (personVector.empty()) {
        // If the vector is empty, generate the first ID
        newID = "ID-1";
    }
    else {
        // Get the last ID in personVector
        lastID = personVector.back().id;
        // Extract the numeric part from the last ID
        lastIdNumberString = lastID.substr(3);
        // Convert the numeric part to an integer
        int lastIdNumber = stoi(lastIdNumberString);
        // Increment the numeric part
        lastIdNumber += 1;
        // Generate the new ID
        newID = "ID-" + to_string(lastIdNumber);
    }

    return newID;
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Name: ";
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
    char option;

    do {
        string taskDescription;
        cout << "Enter Task: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, taskDescription);

        Task task;
        task.description = taskDescription;
        task.isCompleted = false;

        personVector[index].tasksVector.push_back(task);
        cout << "Create another task? (Y/N): ";
        cin >> option;
       

    } while (tolower(option) == 'y');
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
        cout <<"---------------------------------------------------------------------------"<< endl;
        cout << setw(5) << personVector[i].id << setw(15) << personVector[i].name << endl;
        cout << endl;

        for (size_t j = 0; j < personVector[i].tasksVector.size(); j++) {
            Task task = personVector[i].tasksVector[j];
            cout << setw(5) << "Task-" << j + 1 << setw(15) << task.description << setw(10) << "Status:" << setw(5) << (task.isCompleted == true ? "O" : "X") << endl;
            
        }
        cout << "---------------------------------------------------------------------------" << endl;
        cout << endl;
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

    personVector[index].tasksVector[taskNumber].isCompleted = currentTask.isCompleted;
}
void deletePerson() {

    int index = indexFinder();
    displaySpecificPersonTask(index);
    string name;
    personVector[index].name == name;
    cout << endl;
    cout<< "Remove '"<< name <<"' from the Database?\nPress 1 to Confirm, 0 to Cancel" << endl;
    int option;
    cin >> option;
    if (option == 1) {
        // Check if the index is valid
        if (index >= 0 && index < personVector.size()) {
            personVector.erase(personVector.begin() + index);

        }
        else 
        {
            std::cout << "Invalid index.\n";
        }
    }
    else
    {
        cout << "Cancled.\n";
    }
}

void deleteTask() {

    int index = indexFinder();
    displaySpecificPersonTask(index);

    cout << "Select Task Number to Delete" << endl;
    cout << "Task Number: " << endl;
    int taskNumber;
    cin >> taskNumber;

    Person person = personVector[index];
    vector <Task> currentTaskVector = person.tasksVector;

    

    if (taskNumber > currentTaskVector.size())
    {
        cout << "Invalid Task Number:" << endl;
        return;
    }

    //reducing 1 because index beign from 0 of the Task vecotor containing tasks of the person.
    taskNumber -= 1;

    cout << "Confirm To Delete Task: " << endl;
    cout << "1- Confirm: " << endl;
    cout << "0- Cancel: " << endl;

    int option;
    cin >> option;

    if (option == 1){
        currentTaskVector.erase(currentTaskVector.begin() + taskNumber);
        personVector[index].tasksVector = currentTaskVector;
        cout << "Task-" << taskNumber + 1 << " Deleted " <<endl;

    }
    else {
        cout << "Cancelling" << endl;
        return;
    }

    personVector[index].tasksVector = currentTaskVector;
}