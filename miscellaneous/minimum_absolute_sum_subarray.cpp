#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>

/*
Given an array of integers,
   return a non-empty subarray with a minimal absolute value of the sum of its elements.

   [10 20 30 -29] -> 1

          |    |
   abs(30 + -29) = 1

   [10 -11 1] -> 0
    |      |
   abs(sum_i a[i]) -> min

*/

/*

1 2 3 4 5 -15

total sum = S
prefix sums: sum from 0 to ith element.

31 21 1 -29

6th to the 16th element (i to j)
sum of a sub array = ith + suff(i) - suff(j)
abs(sum of a sub array) -> min =>

abs(suff(i) - suff(j+1)) -> min (sum of i to j)

abs(suff(i) - suff(j+1)) = 0
=> suff(i) == suff(j+1)

1 2 3 4 5 -15

*/

/**
 * @brief Get the minimum absolute sum that a subarray in the given array can provide.
 * @param elements Vector of ints
 * @return int Minimum absolute sum
 */
int min_absolute_sum(std::vector<int> & elements) {

    std::vector<int> suffixes(elements.size() + 1, 0);
    int current_sum = 0;
    int min_abs = std::numeric_limits<int>::max();

    for (int i = elements.size()-1; i >=0; i--) {
        current_sum += elements[i];
        suffixes[i+1] = current_sum;
    }

    std::sort(suffixes.begin(), suffixes.end());

    for (int i = 0; i < suffixes.size()-1; i++) {
        min_abs = std::min(min_abs, std::abs(suffixes[i] - suffixes[i+1]));
    }

    return min_abs;
}

int main() {
    std::cout << "Hello LeetCoder"<<std::endl;
    std::vector<int> vec{10, 20, 35, -29};

    std::cout<<min_absolute_sum(vec)<<std::endl;
}