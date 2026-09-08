#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <map> 
#include <set>
#include <unordered_set> 
#include <unordered_map> 
#include <queue> 
#include <cmath> 



class Math { 
    public: 
        // O(logn) time, binary search integers and compute n^2 until we are close to x, watch out for int represent overflows 
        int my_sqrt(int x); 

        // O(logn) time, take squared sum of digits (n % 10)^2, use Floyd's cycle algorithm to detect cycle, check if we hit 1, 
        bool is_happy(int n); 

        // O(1) time, use log base 2 and see if it is whole 
        bool is_power_of_two(int n); 

        // O(n) time, O(1) space, take sum of natural numbers up until n and sum of nums, subtract the two to find the missing num, to save space a little more space we can subtract nums as we take sum of natural numbers 
        int missing_number(std::vector<int> &nums); 

        // O(1) time, return n - 999 if n is > 999, because that is the amount of commas it would have 
        int count_commas(int n); 

        // O(1) time, digital root, calculate using floor formula method 
        int add_digits(int num); 
}; 