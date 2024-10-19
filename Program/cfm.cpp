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
void settleDebts(vector<Person> people);                   // calculates who should pay who

int main() {
    

    welcomeMsg();

    string filename;
    cout << "\nEnter the name of your data file: ";
    cin >> filename;

    vector<Person> people;
    while (people.empty()) {      // prompts user for data 
        people = readData(filename);
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
        people.clear();
        people.resize(0);
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
            people.clear();
            people.resize(0);
            return people;
        }

        int dIndex = findName(people, debtor);      // searches vector for the debtors index
        int cIndex = findName(people, creditor);    // searches vector for the creditors index

        if (dIndex == -1) {         // adds new person to list
            Person newPerson(debtor, debt, 0);
            people.push_back(newPerson);
        } else {                    // modifies debt parameter for new debt
            people[dIndex].addDebt(debt);
        }

        if (cIndex == -1) {         // adds new person to list
            Person newPerson(creditor, 0, debt);
            people.push_back(newPerson);
        } else {                    // modifies credit parameter for new credit
            people[cIndex].addCredit(debt);
        }
    }
}

void settleDebts(vector<Person> people) {
    // cancels out each persons debt and credit with themselves
    cout << "\nCancelling out everyone's debt and credit:\n";
    int s = people.size();
    for (int i = 0; i < s; i++) {
        if (people[i].getCredit() < people[i].getDebt()) {
            people[i].subDebt(people[i].getCredit());
            cout << people[i].getName() << "'s credit cancels out. They will not get paid. They still owe $" << people[i].getDebt() << ".\n";
        } else if (people[i].getDebt() < people[i].getCredit()) {
            people[i].subCredit(people[i].getDebt());
            cout << people[i].getName() << "'s debt cancels out. They will not pay anyone. They still are owed $" << people[i].getCredit() << ".\n";
        } else {
            cout << people[i].getName() << "'s debt and credit cancels out. They will not pay anyone or get paid\n";
            people.erase(people.begin() + i);
        }
    }

    // iterating through list to determine who will pay who
    
}