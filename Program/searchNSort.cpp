#include <string>
#include <iostream>
#include <vector>
#include "person.h"

using namespace std;

// linear search because vector of people is unsorted by name
// out of date, not in use
int findName(vector<Person> &people, const string& name) {
    int s = people.size();
    for (int i = 0; i < s; i++) {
        if (people[i].getName() == name) {
            return i;
        }
    }
    return -1;
}

// merge algorithm to merge two vectors
void mergeByCredit(vector<Person> & people, int left, int mid, int right) {
    vector<Person> temp(right - left + 1);

    int i = left, j = mid + 1, k = 0;

    // merges the two array sections together
    while (i <= mid && j <= right) {
        if (people[i].getCredit() <= people[j].getCredit()) {
            temp[k++] = people[i++];
        } else {
            temp[k++] = people[j++];
        }
    }

    ///////////////////////////////////////////////
    //                                           //
    //      ONLY ONE OF THE FOLLOWING TWO        //
    //            LOOPS WILL RUN                 //
    //                                           // 
    ///////////////////////////////////////////////

    // adds the rest of the left half
    while (i <= mid) {
        temp[k++] = people[i++];
    }

    // adds the rest of the right half
    while (j <= right) {
        temp[k++] = people[j++];
    }

    // size of the temporary array
    int s = temp.size();

    // starting from left point, copies the new values into original vector
    for (k = 0; k < s; k++) {
        people[left + k] = temp[k];
    }

}

// merge sort to sort the vector of people
void mergeSortByCredit(vector<Person> &people, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSortByCredit(people, left, mid);
        mergeSortByCredit(people, mid + 1, right);
        mergeByCredit(people, left, mid, right);
    }
}