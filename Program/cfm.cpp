#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include "person.h"
#include "searchNSort.h"

using namespace std;

void welcomeMsg();                          // prints welcome message
vector<Person> readData(string filename);   // get data from file
void settleDebts(vector<Person>& people);   // calculates who should pay who
int findName(const vector<Person>& people, const string& name);  // helper function to find a person by name

int main() {
    welcomeMsg();

    string filename;
    cout << "\nEnter the name of your data file: ";
    cin >> filename;

    vector<Person> people = readData(filename);

    if (people.empty()) {
        cout << "Failed to load data or no valid data found in file. Exiting program.\n";
        return 1;  // Exit the program if no data is found
    }

    cout << "Calculating who should pay whom..." << endl;
    settleDebts(people);

    return 0;
}

void welcomeMsg() {     // welcome message
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
        << "+                                                  +\n"
        << "+        Welcome to the Cash Flow Minimizer        +\n"
        << "+                                                  +\n"
        << "++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
}

vector<Person> readData(string filename) {      // reads data from file
    vector<Person> people;

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

        int dIndex = findName(people, debtor);      // searches vector for the debtor's index
        int cIndex = findName(people, creditor);    // searches vector for the creditor's index

        if (dIndex == -1) {         // adds new person to list
            Person newPerson(debtor, debt, 0);
            people.push_back(newPerson);
        }
        else {                    // modifies debt parameter for new debt
            people[dIndex].addDebt(debt);
        }

        if (cIndex == -1) {         // adds new person to list
            Person newPerson(creditor, 0, debt);
            people.push_back(newPerson);
        }
        else {                    // modifies credit parameter for new credit
            people[cIndex].addCredit(debt);
        }
    }
    return people;
}

int findName(const vector<Person>& people, const string& name) {
    for (size_t i = 0; i < people.size(); ++i) {  // Changed int to size_t to match the type of people.size()
        if (people[i].getName() == name) {
            return i;  // return the index of the person if found
        }
    }
    return -1;  // return -1 if the person is not found
}

void settleDebts(vector<Person>& people) {
    // cancels out each person's debt and credit with themselves
    cout << "\nCancelling out everyone's debt and credit:\n";
    size_t s = people.size();  // Correct type

    for (size_t i = s; i > 0; --i) {  // Reverse loop to erase elements safely
        size_t idx = i - 1;  // Correct index when using size_t in reverse loop
        if (people[idx].getCredit() < people[idx].getDebt()) {
            people[idx].subDebt(people[idx].getCredit());
            cout << people[idx].getName() << "'s credit cancels out. They will not get paid. They still owe $" << people[idx].getDebt() << ".\n";
        }
        else if (people[idx].getDebt() < people[idx].getCredit()) {
            people[idx].subCredit(people[idx].getDebt());
            cout << people[idx].getName() << "'s debt cancels out. They will not pay anyone. They still are owed $" << people[idx].getCredit() << ".\n";
        }
        else {
            cout << people[idx].getName() << "'s debt and credit cancels out. They will not pay anyone or get paid.\n";
            people.erase(people.begin() + idx);  // Safely erase while iterating backward
        }
    }

    // Additional logic for settling remaining debts/credits can be implemented here
}
