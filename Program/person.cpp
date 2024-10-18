#include <string>
#include "person.h"

using namespace std;

// constructors
// constructor
Person() {

}   

// constructor with name parameter
Person(string name) {
    setName(name);
}   

// constructor with name and debt parameter
Person(string name, double debt, double credit) {
    setName(name);
    setDebt(debt);
    setCredit(credit);
}   



// getters
// returns name
string getName() {
    return name;
}  

// returns debt
double getDebt() {
    return debt;
} 

// returns credit     
double getCredit() {
    return credit;
}    



// setters 
// sets name
void setName(string name) {
    name = name;
}  

// sets debt
void setDebt(double debt) {
    debt = debt;
} 

// sets credit
void setCredit(double credit) {
    credit = credit;
}  



// modifiers 
// adds d to debt
void addDebt(double d) {
    debt = debt + d;
} 

// subtracts d from debt
void subDebt(double d) {
    debt = debt - d;
} 

// adds d to credit
void addCredit(double c) {
    credit = credit + c;
}

// subtracts d from credit   
void subCredit(double c) {
    credit = credit - c;
}   