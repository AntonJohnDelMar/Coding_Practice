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


int Math::missing_number(std::vector<int> &nums) { 
    /*
    Approaches: 
    - O(logn + n) time, O(1) space, sort then itr in order until we find the missing number 
    - O(n) time, O(n) space, use array of zeros and fill it out with each respective number, in the end itr until we find the idx with the zero left in it 
    - O(n) time, O(1) space, take sum of natural numbers up until n and sum of nums, subtract the two to find the missing num, to save space a little more space we can subtract nums as we take sum of natural numbers 

    */

    int natural_sum = nums.size(); 

    for (int i = 0; i < nums.size(); i++) {
        natural_sum += (i - nums[i]); 
    }

    return natural_sum; 
}; 


int Math::count_commas(int n) {
    /* 
    Approaches: 
    - Modulo by 10^k until it returns n, the remainders are the amount of commas, minus 999 as those numbers don't have commas 
    - O(1) time, if n is > 999 then return n - 999, this is the amount of numbers with at least one comma 

    */

    return n >= 1000 ? n - 999 : 0; 
}; 


int Math::add_digits(int num) {
    /*
    Approaches: 
    - add up all digits in num using modulo, repeat until we have a single digit 
    - O(1) time, digital root, calculate using floor formula method 

    */

    return num - 9 * ((num - 1) / 9); 
    /* 
    auto add_up = [](int num) -> int {
        int sum = 0; 
        while (num != 0) { 
            sum += num % 10; 
            num /= 10; 
        }

        return sum; 
    }; 

    while (num % 10 != num) {
        num = add_up(num); 
    }

    return num; 
    */
}; 


bool Math::is_ugly(int n) {
    /*
    Approaches: 
    - O(k) time, divide n by our constrained prime factors if their mod is 0 until we get to 1 or a number with prime factors outside our constraint 
    
    */

    std::vector<int> prime_factors {2, 3, 5}; 

    while (n != 1 && n != 0) { 

        for (int i = 0; i < prime_factors.size(); i++) { 
            if (n % prime_factors[i] == 0) { 
                n /= prime_factors[i]; 
                break; 
            } 
            else if (i == prime_factors.size() - 1) n = 0; 
        }
    }

    return n == 1; 
}; 


long long Math::count_commas_II(long long n) {
    /*
    Approaches: 
    - check number of digits, every three digits adds a comma, check groups using modulo, 
    - O(k) time, O(1) space, determine number of commas k in n, multiply k * n then subtract the max of subset groups, i.e. 1,234,567,890 * 3 - 999,999,999 - 999,999 - 999 

    1,000,000,000 
    */

    long long comma_count = 0; 
    int commas = 0; 

    long long base = 1e3; 

    while (n > base - 1) { 
        comma_count -= base - 1; 
        commas++; 

        base *= 1e3; 
    }

    return n * commas + comma_count; 
}; 