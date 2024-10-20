#include <string>
#include <vector>
#include "person.h"

using namespace std;

// linear search because vector of people is unsorted by name
int findName(vector<Person> &people, const string& name);

// merge algorithm to merge two vectors by credit
void mergeByCredit(vector<Person> & people, int left, int mid, int right);
// mergeSort algorithm to sort the vector of poeple by credit
void mergeSortByCredit(vector<Person> &people, int left, int right);