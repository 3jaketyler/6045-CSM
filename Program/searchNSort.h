#include <string>
#include <vector>
#include "person.h"

using namespace std;

// linear search because vector of people is unsorted by name
int findName(vector<Person> &people, const string& name);

void mergeSort(vector<Person> &people, int left, int mid, int right);