#include <string>

using namespace std;

class Person {
    public:
        // constructors
        Person();                                           // constructor
        Person(std::string name);                                // constructor with name parameter
        Person(std::string name, double debt, double credit);    // constructor with name, debt, and credit parameter


        // getters
        std::string getName();      // returns name
        double getDebt();      // returns debt
        double getCredit();    // returns credit

        // setters 
        void setName(std::string name);      // sets name
        void setDebt(double debt);      // sets debt
        void setCredit(double credit);  // sets credit

        // modifiers 
        void addDebt(double d);     // adds d to debt
        void subDebt(double d);     // subtracts d from debt
        void addCredit(double c);   // adds d to credit
        void subCredit(double c);   // subtracts d from credit

    private:
        std::string name;        // name of person
        double debt;        // amount owed
        double credit;      // amount owed to them
};