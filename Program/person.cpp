#include "person.h"

// Default constructor
Person::Person() : name(""), debt(0.0), credit(0.0) {}

// Constructor with name parameter
Person::Person(std::string n) : name(n), debt(0.0), credit(0.0) {}

// Constructor with name, debt, and credit parameters
Person::Person(std::string n, double d, double c) : name(n), debt(d), credit(c) {}

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
void Person::setName(std::string n) {
    this->name = n;
}

void Person::setDebt(double d) {
    this->debt = d;
}

void Person::setCredit(double c) {
    this->credit = c;
}

// Modifiers
void Person::addDebt(double d) {
    this->debt += d;  // Add the debt amount
}

void Person::subDebt(double d) {
    this->debt -= d;  // Subtract the debt amount
}

void Person::addCredit(double c) {
    this->credit += c;  // Add the credit amount
}

void Person::subCredit(double c) {
    this->credit -= c;  // Subtract the credit amount
}
