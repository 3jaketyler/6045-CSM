#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <unordered_map>
#include "person.h"
#include "searchNSort.h"

using namespace std;

//////////////////////////////////////////////
//                                          //
//     Function Forward Declarations        //
//                                          //
//////////////////////////////////////////////
void welcomeMsg();                          // prints welcome message
vector<Person> readData(string filename);   // get data from file
void settleDebts(vector<Person>& people);   // calculates who should pay who
void printPeople(const vector<Person>& people);



//////////////////////////////////////////////
//                                          //
//             Main Function                //
//                                          //
//////////////////////////////////////////////
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

    cout << "\nCalculating who should pay whom..." << endl;

    mergeSortByCredit(people, 0, people.size() - 1);

    settleDebts(people);
    printPeople(people);

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

vector<Person> readData(string filename) {      // reads data from file
    vector<Person> peopleInitial;       // placeholder empty vector for error checking

    ifstream f(filename);     // opens file

    if (!f.is_open()) {   // error checking, returns empty vector if no data
        cout << "There was an error opening the file. Please try again\n";
        return peopleInitial;
    }

    int numPeople, numDebts;
    f >> numPeople >> numDebts;
    if (f.fail()) {          // error checking
        cout << "Invalid input format on line 1. Please try again.\n";
        f.clear();               // Clear the error flags
        f.ignore(numeric_limits<streamsize>::max(), '\n');
        return peopleInitial;
    }

    unordered_map<string, Person> peopleMap;

    for (int i = 0; i < numDebts; i++) {
        string debtor, creditor;            // stores names of debtor and creditor
        double debt;                        // amount of debt
        f >> debt >> debtor >> creditor;    // extracts information
        if (f.fail()) {          // error checking
            cout << "Invalid input format on line " << i + 2 << ". Please try again.\n";
            f.clear();               // Clear the error flags
            f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return peopleInitial;
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

    vector<Person> people;
    for (const auto& [name, person] : peopleMap) {
        people.push_back(person);
    }

    return people;
}

void settleDebts(vector<Person>& people) {
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

    size_t j = 0;      // iterator from beginning of vector

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
                    people[idx].subCredit(people[j].getDebt());
                    people[j].setDebt(0);
                    j++;
                    break;
                }
            }
            if (people[j].getDebt() < people[idx].getCredit()) {
                cout << people[j].getName() << " will pay " << people[idx].getName() << " $" << people[j].getDebt() << endl;
                people[idx].subCredit(people[j].getDebt());
                people[j].setDebt(0);
            } else if (people[j].getDebt() >= people[idx].getCredit()) {
                cout << people[j].getName() << " will pay " << people[idx].getName() << " $" << people[idx].getCredit() << endl;
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

}

void printPeople(const vector<Person>& people) {        // helper function for checking data
    int s = people.size();
    for (int i = 0; i < s; i++) {
        cout << people[i].getName() << " " << people[i].getDebt() << " " << people[i].getCredit() << endl;
    }
}