#include "algorithms/math.hpp" 



int Math::my_sqrt(int x) { 
    /*
    Approaches: 
    - O(logn) time, binary search integers and compute n^2 until we are close to x, watch out for int represent overflows 

    */

    const int MAX_SQUARE_VAL = 46340;

    int left_val = 0; 
    int right_val = x; 
    int middle_val = 0; 

    while(left_val < right_val) { 
        middle_val = ((right_val + left_val) / 2); 

        if (middle_val > MAX_SQUARE_VAL) {
            right_val = MAX_SQUARE_VAL; 
            continue; 
        } 

        if ((middle_val * middle_val) > x) right_val = middle_val - 1; 
        else if ((middle_val * middle_val) < x) left_val = middle_val + 1; 
        else break; 
    }

    if (left_val == right_val) middle_val = left_val; 
    return middle_val * middle_val > x ? middle_val - 1 : middle_val; 
}; 


bool Math::is_happy(int n) { 
    /*
    Approaches: 
    - O(logn) time, take squared sum of digits (n % 10)^2, use Floyd's cycle algorithm to detect cycle, check if we hit 1, 
    - O(logn) time, take squared sum of digits (n % 10)^2, use unordered set to detect cycle, 

    */

    auto squared_sum = [](int n) -> int {
        int square_sum = 0; 

        while (true) { 
            square_sum += std::pow((n % 10), 2); 

            if ((n % 10) == n) break; 
            else n /= 10; 
        } 

        return square_sum; 
    }; 

    int tortoise = n; 
    int hare = n; 

    int cycle = 0; 
    while (tortoise != hare || cycle == 0) { 
        cycle++; 

        hare = squared_sum(hare); 
        if (hare == 1) break; 

        if (cycle % 2 == 0) tortoise = squared_sum(tortoise); 
    } 

    return tortoise != hare || hare == 1; 
    /*
    std::unordered_set<int> seen; 

    int squared_sum = n; 

    while (!seen.contains(squared_sum)) {
        seen.insert(squared_sum); 
        squared_sum = 0; 

        while (true) {
            squared_sum += std::pow((n % 10), 2); 

            if (n % 10 == n) break; 
            else n /= 10; 
        }

        n = squared_sum; 
        if (squared_sum == 1) break; 
    }

    return squared_sum == 1; 
    */
}; 


bool Math::is_power_of_two(int n) {
    /*
    Approaches: 
    - O(logn) time, we can modulo by two and check if there is a remainder 
    - O(1) time, use log base 2 and see if it is whole 
    - O(1) time, bit manipulation trick, n & n - 1 == 0, 

    */

    return (std::log2(n) == floor(std::log2(n))) && n != 0; 
    /*
    Loop solution 
    while (n != 1) {
        if (n % 2 != 0) return false; 
        n /= 2; 
    } 

    return true; 

    Solution without loops, log base 2 
    return (std::log2(n) == floor(std::log2(n))) && n != 0; 

    Bit manipulation trick ! If it is a power of two it has a single one bit, so subtracting one would have all other bits as one except the end bit, then if you and you should get zero, 
    return n > 0 && (n & (n - 1)) == 0;

    */
}; 