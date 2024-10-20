#include <string>
#include <vector>
#include "person.h"

using namespace std;

// linear search because vector of people is unsorted by name
int findName(vector<Person> &people, const string& name) {
    int s = people.size();
    for (int i = 0; i < s; i++) {
        if (people[i].getName() == name) {
            return i;
        }
    }
    return -1;
}

// merge sort to sort the vector of people
void mergeSort(vector<Person> &people, int left, int mid, int right) {
    
}