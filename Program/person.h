#include <string>

using namespace std;

class Person {
    public:
        // constructors
        Person();                                           // constructor
        Person(string name);                                // constructor with name parameter
        Person(string name, double debt, double credit);    // constructor with name, debt, and credit parameter


        // getters
        string getName();      // returns name
        double getDebt();      // returns debt
        double getCredit();    // returns credit

        // setters 
        void setName(string name);      // sets name
        void setDebt(double debt);      // sets debt
        void setCredit(double credit);  // sets credit

        // modifiers 
        void addDebt(double d);     // adds d to debt
        void subDebt(double d);     // subtracts d from debt
        void addCredit(double c);   // adds d to credit
        void subCredit(double c);   // subtracts d from credit

    private:
        string name;        // name of person
        double debt;        // amount owed
        double credit;      // amount owed to them
}