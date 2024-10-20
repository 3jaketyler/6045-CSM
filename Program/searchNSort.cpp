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

// merge algorithm to merge two vectors
void merge(vector<Person> & people, int left, int mid, int right) {
    vector<Person> temp(right - left + 1);

    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (people[i].getCredit() <= people[j].getCredit()) {
            temp[k++] = people[i++];
        } else {
            temp[k++] = people[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = people[i++];
    }

    while (j <= right) {
        temp[k++] = people[j++];
    }

    int s = temp.size();

    for (k = 0; k < s; k++) {
        people[left + k] = temp[k];
    }

}

// merge sort to sort the vector of people
void mergeSort(vector<Person> &people, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(people, left, mid);
        mergeSort(people, mid + 1, right);
        merge(people, left, mid, right);
    }
}