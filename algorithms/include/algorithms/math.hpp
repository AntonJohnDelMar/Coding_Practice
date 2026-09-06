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
}; 