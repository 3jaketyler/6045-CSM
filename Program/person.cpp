#include <string>
#include "person.h"

using namespace std;

// constructors
// constructor
Person::Person() {
    
}   

// constructor with name parameter
Person::Person(std::string name) {
    setName(name);
}   

// constructor with name and debt parameter
Person::Person(std::string name, double debt, double credit) {
    setName(name);
    setDebt(debt);
    setCredit(credit);
}   



// getters
// returns name
string Person::getName() {
    return name;
}  

// returns debt
double Person::getDebt() {
    return debt;
} 

// returns credit     
double Person::getCredit() {
    return credit;
}    



// setters 
// sets name
void Person::setName(string name) {
    name = name;
}  

// sets debt
void Person::setDebt(double debt) {
    debt = debt;
} 

// sets credit
void Person::setCredit(double credit) {
    credit = credit;
}  



// modifiers 
// adds d to debt
void Person::addDebt(double d) {
    debt = debt + d;
} 

// subtracts d from debt
void Person::subDebt(double d) {
    debt = debt - d;
} 

// adds d to credit
void Person::addCredit(double c) {
    credit = credit + c;
}

// subtracts d from credit   
void Person::subCredit(double c) {
    credit = credit - c;
}   