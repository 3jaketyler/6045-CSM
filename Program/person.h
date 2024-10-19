#ifndef PERSON_H    // If PERSON_H is not defined...
#define PERSON_H    // Define PERSON_H

#include <string>

using namespace std;

class Person {
public:
    // Constructors
    Person();
    Person(std::string name);
    Person(std::string name, double debt, double credit);

    // Getters (marked as const)
    std::string getName() const;  // returns name
    double getDebt() const;       // returns debt
    double getCredit() const;     // returns credit

    // Setters
    void setName(std::string name);
    void setDebt(double debt);
    void setCredit(double credit);

    // Modifiers
    void addDebt(double d);
    void subDebt(double d);
    void addCredit(double c);
    void subCredit(double c);

private:
    std::string name;   // name of person
    double debt;        // amount owed
    double credit;      // amount owed to them
};

#endif  // End of include guard
