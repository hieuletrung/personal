#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <vector>
#include <iostream>
#include <algorithm>

// Generate an array with non-duplicate number starting from 1 to max_value

int main() {
    int count = 10;
    int max_value = 50;
    std::vector<int> v;

    std::cout << "Max value: ";
    std::cin >> max_value;
    std::cout << "Max array len: ";
    std::cin >> count;

    srand (time(NULL));

    for (int i=0; i<count; ++i) {
    	int x = (rand() % max_value) + 1;
    	if(std::find(v.begin(), v.end(), x) != v.end()) {
    		--i;
		} else {
    		v.push_back(x);
		}
    }

    // sort it
    std::sort(v.begin(), v.end(), std::less<int>());

    // Iterate and print values of vector
    for (int n : v) {
        std::cout << n << '\n';
    }

    return 0;
}