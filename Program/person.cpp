#include "person.h"

// Default constructor
Person::Person() : name(""), debt(0.0), credit(0.0) {}

// Constructor with name parameter
Person::Person(std::string name) : name(name), debt(0.0), credit(0.0) {}

// Constructor with name, debt, and credit parameters
Person::Person(std::string name, double debt, double credit) : name(name), debt(debt), credit(credit) {}

// Getters
std::string Person::getName() const {
    return name;
}

double Person::getDebt() const {
    return debt;
}

double Person::getCredit() const {
    return credit;
}

// Setters
void Person::setName(std::string name) {
    this->name = name;
}

void Person::setDebt(double debt) {
    this->debt = debt;
}

void Person::setCredit(double credit) {
    this->credit = credit;
}

// Modifiers
void Person::addDebt(double d) {
    debt += d;  // Add the debt amount
}

void Person::subDebt(double d) {
    debt -= d;  // Subtract the debt amount
}

void Person::addCredit(double c) {
    credit += c;  // Add the credit amount
}

void Person::subCredit(double c) {
    credit -= c;  // Subtract the credit amount
}
