#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
// this is something to hold the debt per person once called//
struct PersonDebts {
    string name;
    int debt = 0;
    int owed = 0;
};
// this shows a transaction between 2 ppl//
struct Transaction {
    string debtor;
    string creditor;
    int amount;
};
// this si to compare 2 persons debt and to see who owes who between a or b//
bool compareOwed(const PersonDebts& a, const PersonDebts& b) {
    return a.owed > b.owed;
}

void settleDebts(vector<Transaction>& debts, vector<string>& people) {
    vector<PersonDebts> totalDebts(people.size());
    //stores debt per person and how much they owed
    for (size_t i = 0; i < people.size(); i++) {
        totalDebts[i].name = people[i];
    }
    // processes each transaction 
    for (const auto& debt : debts) {
        auto debtorIt = find(people.begin(), people.end(), debt.debtor);
        auto creditorIt = find(people.begin(), people.end(), debt.creditor);
        
        if (debtorIt != people.end() && creditorIt != people.end()) {
            int debtorIdx = distance(people.begin(), debtorIt);
            int creditorIdx = distance(people.begin(), creditorIt);

            totalDebts[debtorIdx].debt += debt.amount;
            totalDebts[creditorIdx].owed += debt.amount;
        }
    }
    
    for (auto& totalDebt : totalDebts) {
        if (totalDebt.owed < totalDebt.debt) {
            totalDebt.debt -= totalDebt.owed;
            totalDebt.owed = 0;
        }
        else if (totalDebt.debt <= totalDebt.owed) {
            totalDebt.owed -= totalDebt.debt;
            totalDebt.debt = 0;
        }
    }

    sort(totalDebts.begin(), totalDebts.end(), compareOwed);

    size_t j = 0;
    for (int i = totalDebts.size() - 1; i >= 0; --i) {
        while (totalDebts[i].owed != 0 && j < totalDebts.size()) {
            if (totalDebts[j].debt < totalDebts[i].owed) {
                cout << totalDebts[j].name << " needs to pay " << totalDebts[i].name
                    << " $" << totalDebts[j].debt << "." << endl;
                totalDebts[i].owed -= totalDebts[j].debt;
                totalDebts[j].debt = 0;
            }
            else if (totalDebts[j].debt >= totalDebts[i].owed) {
                cout << totalDebts[j].name << " needs to pay " << totalDebts[i].name
                    << " $" << totalDebts[i].owed << "." << endl;
                totalDebts[j].debt -= totalDebts[i].owed;
                totalDebts[i].owed = 0;
            }
            j++;
        }
    }
}
// This i
int main() {
    int numPeople, numDebts;

    cout << "Find out who owes who" << endl;
    cout << "How many people are involved in this cash flow?: ";
    cin >> numPeople;

    vector<string> people(numPeople);

    for (int i = 0; i < numPeople; ++i) {
        cout << "What is the name of person " << i + 1 << "?: ";
        cin >> people[i];
    }

    cout << "How many debt transactions are there to settle?: ";
    cin >> numDebts;

    vector<Transaction> debts(numDebts);

    for (int i = 0; i < numDebts; ++i) {
        cout << "Who owes money for debt " << i + 1 << "? (Enter debtor's name): ";
        cin >> debts[i].debtor;
        cout << "Who should receive the money? (Enter creditor's name): ";
        cin >> debts[i].creditor;
        cout << "How much money does " << debts[i].debtor << " owe to " << debts[i].creditor << "?: ";
        cin >> debts[i].amount;
        cout << endl;
    }

    cout << "Calculating who should pay whom..." << endl;
    settleDebts(debts, people);

    return 0;
}
