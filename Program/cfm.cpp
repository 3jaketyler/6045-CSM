#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <unordered_map>
#include <chrono>
#include "person.h"
#include "searchNSort.h"

using namespace std;
using namespace std::chrono;

//////////////////////////////////////////////
//                                          //
//     Function Forward Declarations        //
//                                          //
//////////////////////////////////////////////
void welcomeMsg();                          // prints welcome message
void instructionMsg();
void aboutMsg();
void choices();
vector<Person> readData(string filename, vector<Person>& people);   // get data from file
void balanceDebts(vector<Person>& people);
void settleDebts(vector<Person>& people);   // calculates who should pay who
void printPeople(const vector<Person>& people);
void specialTesting(vector<Person>& people);
vector<Person> emptyVector();
vector<Person> addPeople(string filename, vector<Person>& people);
string divider();



//////////////////////////////////////////////
//                                          //
//             Main Function                //
//                                          //
//////////////////////////////////////////////
int main() {
    welcomeMsg();
    aboutMsg();
    instructionMsg();

    vector<Person> people;

    char choice;

    while (choice != 'x') {
        choices();

        string choiceString;
        cin >> choiceString;
        choice = tolower(choiceString[0]);

        string filename;

        switch(choice) {
            case 'a':
                cout << "\nEnter the name of your data file: ";
                cin >> filename;
                people = addPeople(filename, people);
                break;
            case 'v':
                aboutMsg();
                break;
            case 'i':
                instructionMsg();
                break;
            case 'b':
                balanceDebts(people);
                break;
            case 's':
                settleDebts(people);
                break;
            case 't':
                printPeople(people);
                break;
            case 'p': 
                specialTesting(people);
                break;
            case 'c':
                people = emptyVector();
                break;
            case 'x':
                cout << "Exiting... \n";
                break;
            default:
                cout << "Please choose a valid menu option.\n";
        }
    }

    return 0;
}




//////////////////////////////////////////////
//                                          //
//          Function Definitions            //
//                                          //
//////////////////////////////////////////////
void welcomeMsg() {     // welcome message
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
         << "+                                                  +\n"
         << "+        Welcome to the Cash Flow Minimizer        +\n"
         << "+                                                  +\n"
         << "++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
}

void instructionMsg() {
    cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
         << "+                                                  +\n"
         << "+         You will enter a file containing         +\n"
         << "+                 debt information.                +\n"
         << "+                                                  +\n"
         << "+                   File Format                    +\n"
         << "+                                                  +\n"
         << "+ (number of people) (number of debts)             +\n"
         << "+ (debt amount) (debtor name) (creditor name)      +\n"
         << "+ (debt amount) (debtor name) (creditor name)      +\n"
         << "+ (debt amount) (debtor name) (creditor name)      +\n"
         << "+                                                  +\n"
         << "+                   Example                        +\n"
         << "+                                                  +\n"
         << "+ 3 4                                              +\n"
         << "+ 25.00 Alice Bob                                  +\n"
         << "+ 30.00 Bob Charlie                                +\n"
         << "+ 15.25 Charlie Alice                              +\n"
         << "+ 7.89 Bob Alice                                   +\n"
         << "+                                                  +\n"
         << "++++++++++++++++++++++++++++++++++++++++++++++++++++\n"; 
}

void aboutMsg() {
    cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
         << "+                                                  +\n"
         << "+     This program will take the data provided     +\n"
         << "+     about the debt between a group of people     +\n"
         << "+     and determine an efficient way to settle     +\n"
         << "+                  all of the debt                 +\n"
         << "+                                                  +\n"
         << "++++++++++++++++++++++++++++++++++++++++++++++++++++\n"; 
}

void choices() {
    cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
         << "+                                                  \n"
         << "+                   Menu Options:                  \n"
         << "+ (a)dd people and debts                           \n"
         << "+ (v)iew program information                       \n"
         << "+ (i)nstructions for data format                   \n"
         << "+ (b)alance each persons debt and credit           \n"
         << "+ (s)ettle all debts between people                \n"
         << "+ (t)otal debt and credit for each person          \n"
         << "+ s(p)ecial testing case                           \n"
         << "+ (c)lear data                                     \n"
         << "+ e(x)it the program                               \n"
         << "+                                                  \n"
         << "+ Enter your choice: "; 
}

vector<Person> readData(string filename, vector<Person>& people) {      // reads data from file
    auto beg = high_resolution_clock::now();
    ifstream f(filename);     // opens file

    if (!f.is_open()) {   // error checking, returns empty vector if no data
        cout << "There was an error opening the file. Please try again\n";
        return people;
    }

    int numPeople, numDebts;
    f >> numPeople >> numDebts;
    if (f.fail()) {          // error checking
        cout << "Invalid input format on line 1. Please try again.\n";
        f.clear();               // Clear the error flags
        f.ignore(numeric_limits<streamsize>::max(), '\n');
        return people;
    }

    unordered_map<string, Person> peopleMap;
    for (const auto& person : people) {
        peopleMap[person.getName()] = person;
    }

    for (int i = 0; i < numDebts; i++) {
        string debtor, creditor;            // stores names of debtor and creditor
        double debt;                        // amount of debt
        f >> debt >> debtor >> creditor;    // extracts information
        if (f.fail()) {          // error checking
            cout << "Invalid input format on line " << i + 2 << ". Please try again.\n";
            f.clear();               // Clear the error flags
            f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return people;
        }

        if (peopleMap.find(debtor) == peopleMap.end()) {
            peopleMap[debtor] = Person(debtor, debt, 0);
        } else {
            peopleMap[debtor].addDebt(debt);
        }

        if (peopleMap.find(creditor) == peopleMap.end()) {
            peopleMap[creditor] = Person(creditor, 0, debt);
        } else {
            peopleMap[creditor].addCredit(debt);
        }
    }

    people.clear();
    for (const auto& [name, person] : peopleMap) {
        people.push_back(person);
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - beg);

    string filename2 = "times";
    ofstream file;
    file.open(filename2, ios::app);
    if (file.is_open()) {
        file << "Adding " << numPeople << " people (" << numDebts << " debts) took " << duration.count() << " microseconds.\n";
    } else {
        cerr << "Times file failed\n";
    }
    file.close();
    return people;
}

void balanceDebts(vector<Person>& people) {
    auto beg = high_resolution_clock::now();
    // cancels out each person's debt and credit with themselves
    cout << "\nCancelling out everyone's debt and credit:\n";
    size_t s = people.size();  // Correct type

    for (size_t i = s; i > 0; --i) {  // Reverse loop to erase elements safely
        size_t idx = i - 1;  // Correct index when using size_t in reverse loop
        if (people[idx].getCredit() < people[idx].getDebt()) {
            people[idx].subDebt(people[idx].getCredit());
            people[idx].setCredit(0);
            cout << people[idx].getName() << "'s credit cancels out. They will not get paid. They still owe $" << people[idx].getDebt() << ".\n";
        }
        else if (people[idx].getDebt() < people[idx].getCredit()) {
            people[idx].subCredit(people[idx].getDebt());
            people[idx].setDebt(0);
            cout << people[idx].getName() << "'s debt cancels out. They will not pay anyone. They still are owed $" << people[idx].getCredit() << ".\n";
        }
        else {
            cout << people[idx].getName() << "'s debt and credit cancels out. They will not pay anyone or get paid.\n";
            people.erase(people.begin() + idx);  // Safely erase while iterating backward
        }
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - beg);

    string filename = "times";
    ofstream file;
    file.open(filename, ios::app);
    if (file.is_open()) {
        file << "Balancing each persons debt and credit took " << duration.count() << " microseconds.\n";
    } else {
        cerr << "Times file failed\n";
    }
    file.close();
}

void settleDebts(vector<Person>& people) {
    auto beg = high_resolution_clock::now();
    size_t j = 0;      // iterator from beginning of vector
    int transactionCounter = 0;

    for (size_t i = people.size(); i > 0; --i) {
        size_t idx = i - 1;
        while (people[idx].getCredit() != 0) {
            if (people[j].getDebt() == 0) {
                j++;
                if (j >= people.size()) {
                    break;
                }
                continue;
            }
            if (idx == j) {
                if (people[j].getDebt() == 0) {
                    j++;
                    if (j >= people.size()) {
                        break;
                    }
                    continue;
                } else {
                    cout << people[j].getName() << " will pay " << people[idx].getName() << " $" << people[j].getDebt() << endl;
                    transactionCounter++;
                    people[idx].subCredit(people[j].getDebt());
                    people[j].setDebt(0);
                    j++;
                    break;
                }
            }
            if (people[j].getDebt() < people[idx].getCredit()) {
                cout << people[j].getName() << " will pay " << people[idx].getName() << " $" << people[j].getDebt() << endl;
                transactionCounter++;
                people[idx].subCredit(people[j].getDebt());
                people[j].setDebt(0);
            } else if (people[j].getDebt() >= people[idx].getCredit()) {
                cout << people[j].getName() << " will pay " << people[idx].getName() << " $" << people[idx].getCredit() << endl;
                transactionCounter++;
                people[j].subDebt(people[idx].getCredit());
                people[idx].setCredit(0);
            }
            if (people[j].getDebt() == 0 && j < people.size()) {
                j++;
            }
        }
        if (j >= people.size()) {
            break;
        }

    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - beg);

    string filename = "times";
    ofstream file;
    file.open(filename, ios::app);
    if (file.is_open()) {
        file << transactionCounter << " transactions must occur." << endl;
        file << "Settling everyone's debt took " << duration.count() << " microseconds.\n";
    } else {
        cerr << "Times file failed\n";
    }
    file.close();
}

void printPeople(const vector<Person>& people) {        // function to print each person and their debt and credit
    auto beg = high_resolution_clock::now();
    int s = people.size();
    for (int i = 0; i < s; i++) {
        cout << people[i].getName() << "'s debt: " << people[i].getDebt() << endl 
             << people[i].getName()  << "'s credit: " << people[i].getCredit() << endl;
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - beg);

    cout << "Printing each persons debt and credit took " << duration.count() << " microseconds.\n";
}

vector<Person> addPeople(string filename, vector<Person>& people) {
    vector<Person> newPeople = readData(filename, people);

    if (people.empty()) {
        cout << "Failed to load data or no valid data found in file. Please try again.\n";
    }

    auto beg = high_resolution_clock::now();

    mergeSortByCredit(people, 0, people.size() - 1);
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - beg);

    string filename2 = "times";
    ofstream file;
    file.open(filename2, ios::app);
    if (file.is_open()) {
        file << "Merge sort took " << duration.count() << " microseconds.\n";
    } else {
        cerr << "Times file failed\n";
    }

    return newPeople;
}

vector<Person> emptyVector() {
    vector<Person> clearedVector;
    return clearedVector;
}

void specialTesting(vector<Person>& people) {
    int numCases;
    int numIterations;

    cout << "\nHow many test cases: ";
    cin >> numCases;
    cout << "\nHow many iterations: ";
    cin >> numIterations;

    vector<string> fileNames(numCases);

    for (int i = 0; i < numCases; i++) {
        cout << "\nEnter filename " << i + 1 << ": ";
        cin >> fileNames[i];
    }

    string filename = "times";
    ofstream file;
    file.open(filename, ios::app);
    if (!file.is_open()) {
        cerr << "Times file failed to open.\n";
        return;
    }

    for (int j = 0; j < numIterations; j++) {
        cout << "\nIteration: " << j + 1 << endl;

        for (int i = 0; i < numCases; i++) {
            cout << "Processing file: " << fileNames[i] << endl;

            file << divider();
            file << "\n" << fileNames[i] << " with individual balancing:\n";
            file.flush();

            addPeople(fileNames[i], people);
            balanceDebts(people);
            settleDebts(people);
            people.clear();
            people.shrink_to_fit(); 

            file << divider();
            file << "\n" << fileNames[i] << " without individual balancing:\n";
            file.flush();

            addPeople(fileNames[i], people);
            settleDebts(people);
            people.clear();
            people.shrink_to_fit(); 
        }
    }

    file.close();
}


string divider() {
    return "\n++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
}