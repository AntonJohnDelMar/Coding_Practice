#include "algorithms/arrays.hpp" 



std::vector<int> Array::get_concatenation(std::vector<int> &nums) { 
    std::vector<int> temp = nums; 

    for(auto itr = nums.begin(); itr != nums.end(); ++itr) {
        temp.push_back(*itr); 
    } 

    return temp; 
}; 


std::vector<int> Array::shuffle(std::vector<int> &nums) { 
    int n = nums.size() % 2; 

    for (int i = 0; i < 2 * n; i++) {
        if (i % 2) {
            nums.insert(nums.begin() + i, nums.at(i + n - 1)); 
        }
    }

    nums.erase(nums.begin() + 2 * n, nums.end()); 
    
    return nums; 
}; 


int Array::find_max_consecutive_ones(std::vector<int> &nums) { 
    int max = 0; 
    int count = 0; 

    // 0 0 1 1 0 0 0 1 1 1 1 
    for (auto &curr : nums) {
        if (curr == 1) count++; 
        else count = 0; 

        max = std::max(max, count); 
    }; 

    return max; 
}; 


std::vector<int> Array::find_error_nums(std::vector<int> &nums) { 
    /* 
    Approaches: 
    - O(2n), use a set to find duplicate number, iterate through again to find the missing number, requires two passes 
    - O(n), iterate through vector, keep track of natural sum to n as well as sum of vector and track duplicate, in the end we know we can subtract the duplicate and the missing number will add to that to match the natural sum of n 

    [4, 5, 3, 1, 1] return [1, 2]  
    [2, 2] return [2, 1] 
    [1, 2, 2] return [2, 3] 
    [1, 1] return [1, 2] 
    [4, 1, 3, 4] 
    12 
    10 
    return [duplicate, missing] 
    */

    std::unordered_set<int> seen; 
    int duplicate = -1; 

    int natural_sum = 0; 
    int vector_sum = 0; 
    for (int i = 0; i < nums.size(); i++) { 
        int current_num = nums[i]; 
        if (seen.contains(current_num)) duplicate = current_num; 
        seen.insert(current_num); 

        vector_sum += current_num; 
        natural_sum += (i + 1); 
    }

    return {duplicate, natural_sum - (vector_sum - duplicate)}; 
}; 

/*
    std::unordered_set<int> seen;  
    std::vector<int> result; 
    int duplicate = -1; 

    for (auto &num : nums) {
        if (seen.contains(num)) duplicate = num; 
        seen.insert(num); 
    } 

    for (int i = 1; i < static_cast<int>(nums.size()) + 1; i++) {
        if (!seen.contains(i)) return {duplicate, i}; 
    }

    return {-1, -1}; 
*/


int Array::second_largest(std::vector<int> &nums) {
    /*
    naive approach - iterate twice, find largest value, then iterate again for the second largest 
    - O(2n) complexity, terrible scalablity, 
    - O(n), Iterate once, as we find largest value, assign second largest, iterate list of length n, 
    */
    int largest = -1; 
    int second_largest = -1; 

    for (auto &curr_num : nums) {
        if (curr_num >= largest) { 
            second_largest = largest; 
            largest = curr_num; 
        }; 

        if (curr_num > second_largest && curr_num < largest) { 
            second_largest = curr_num; 
        }; 
    }; 

    return second_largest; 
}; 


std::tuple<int, int> Array::two_sum(const int target, std::vector<int> &nums) {  
    std::map<int, int> values; 

        for (int i = 0; i <= static_cast<int>(nums.size()); i++) { 
            int curr = nums.at(i); 
            int difference = target - curr; 

            if (auto find = values.find(difference); find != values.end()) { 
                return {i, values[difference]}; 
            }

            values.insert({curr, i}); 
        }

        return {-1, -1}; 

    // Two pointer approach
    /* 
    std::sort(nums.begin(), nums.end()); 

    auto start = nums.begin(); 
    auto end = nums.end() - 1; 

    int sum = 0; 

    while (start != end) {
        int small = *start; int large = *end; 
        std::tuple<int, int> pair {small, large}; 
        sum = small + large; 

        if (sum == target) {
            return pair; 
        } 

        if (sum < target) {
            start++; 
        }

        if (sum > target) {
            end--; 
        }
    }

    return {0, 0}; 
    */
}; 


int Array::max_profit(std::vector<int> &prices) { 
    // [7, 1, 5, 3, 6, 4, 0, 2, 4, 6], output 5, buy when it is 1 sell when it is 6, 
    // Track smallest value, track max profit 
    // 1 5 
    // 0 6 

    int smallest = 1e6; 
    int profit = 0; 

    for (int i = 0; i < static_cast<int>(prices.size()); i++) { 
        int curr = prices.at(i); 
        int curr_profit = curr - smallest; 

        if (curr < smallest) {
            smallest = curr; 
            continue; 
        }

        if (curr_profit > profit) {
            profit = curr_profit; 
            continue; 
        }

    }

    return profit; 
}; 


bool Array::contains_duplicate(std::vector<int> &nums) { 
    std::unordered_set<int> seen; 

    for (int i = 0; i < static_cast<int>(nums.size()); i++) { 
        int curr_num = nums.at(i); 

        if (seen.count(curr_num) > 0) return true; 

        seen.insert(curr_num); 
    } 

    return false; 
}; 


std::vector<int> Array::product_except_self(std::vector<int> &nums) { 
    /*
    O(n + n) = O(2n), return array where each element is product of the other elements except itself, no division! 
    Find prefix and postfix products, then multiply the prefix and post fix for each element 
    [1, 2, 3, 4] = [24, 12, 8, 6] 
    */
    std::vector<int> result; 

    int prefix = 1; 
    for (int i = 0; i < static_cast<int>(nums.size()); i++) { 
        result.push_back(prefix); 
        prefix *= nums.at(i); 
    }

    // [1, 1, 2, 6] 
    int postfix = 1; 
    for (int j = static_cast<int>(nums.size()) - 1; j >= 0; j--) {
        result.at(j) *= postfix; 
        postfix *= nums.at(j); 
    }

    return result; 
}; 


int Array::max_sub_array(std::vector<int> &nums) { 
    if (nums.size() == 1) return nums.at(0); 
    /*
    Approaches: 
    - naive solution: O(n^2) find sum of subarrays of each size, i.e. n, n - 1, n - 2 until 1 
    - O(~1/2 * n^2), keep track of cummulative sum, and subtract and add elements as needed as we come across each window size 
    - O(n) solution: use sliding window like, move right and only move left if prefix is negative, track largest sub array 

    [1, -2, 3, -4, 5] 
    [-2, 1, -3, 4, -1, 2, 1, -5, 4] 
    [-2, -1, -4] 
    */ 

    int max_sum = -1e4; 
    int sum = 0; 

    for (int right = 0; right < static_cast<int>(nums.size()); right++) { 
        int curr_num = nums.at(right); 

        sum += curr_num; 

        max_sum = std::max(max_sum, sum); 

        if (sum < 0) {
            sum = 0; 
        }

    }

    return max_sum; 
}; 


int Array::max_product(std::vector<int> &nums) { 
    /*
    Approaches: 
    - Track product of window, if it is <= 0 reset window, doesn't work in the case we have multiple (-) in a row 
    - Window, move right as far as we can (stop if it is 0 or the end) taking product along the way, then we move the left and divide out the numbers as we go 

    [-2, 0, -1] 
    [3, -1, 4] 
    [-1, -2, -3, 0] 
    [2, -5, -2, -4, 3] 
    [-1, -2, -3] 
    */
    if (nums.size() == 1) return nums[0]; 

    int max_product = 1e-4; 
    int window_product = 1; 

    int left = 0; 
    int right = 0; 

    auto shift_left_to_right = [&]() { 
        while (left < right - 1) { 
            window_product /= nums[left]; 
            left++; 
            max_product = std::max(max_product, window_product); 
        } 

        if (left == right) left++; 
        else left += 2; // Skip index with zero term 
        window_product = 1; 
    }; 

    for (right = 0; right < nums.size(); right++) { 
        int right_num = nums[right]; 

        int current_product = window_product * right_num; 
        max_product = std::max(max_product, current_product); 

        if (current_product == 0) {
            shift_left_to_right(); 
        } 

        else {
            window_product = current_product; 
        }
    }

    shift_left_to_right(); 

    return max_product; 
}; 


int Array::missing_multiple(std::vector<int>& nums, int k) { 
    /*
    Approaches: 
    - O(n + mlogm) = O(mlogm), if modulo is 0 then it is a multiple, we can calculate multiple by dividing, save the multiples in a sorted vector then iterate and find the smallest missing one 

    10, 6, 7, 9, 2, 3, 8, k = 2 
    5, 3, n, n, 1, n, 4 
    */ 

    std::set<int> seen_multiples; 
    for (auto &number : nums) { 
        if (number % k == 0) seen_multiples.insert(number / k); 
    }

    for (int i = 0; i < seen_multiples.size(); i++) { 
        if (!seen_multiples.contains(i + 1)) return k * (i + 1); 
    } 

    return k * (seen_multiples.size() + 1); // return nth + 1 multiple, i.e. we had 2, 4, 6, 8 so return 10 
}; 


int Array::remove_duplicates(std::vector<int> &nums) {
    /*
    Approaches: 
    - O(n), left and right pointer, when the right detects a new unique num move left one spot and place it, track the current unique num 

    [0, 0, 1, 1, 1, 2, 2, 3, 3, 4] = [0, 1, 2, 3, 4, -, -, -, -, -] 
    */
 
    int current_unique = nums[0]; 
    int left = 0; 
    for (auto &right_number : nums) { 
        if (right_number != current_unique) { 
            left++; 
            nums[left] = right_number; 
            current_unique = right_number; 
        } 
    }

    return left + 1; 
}; 


int Array::remove_element(std::vector<int>& nums, int val) { 
    /*
    Approaches: 
    - O(n), move right until we hit num == val set the left pointer here, from now on any time num != val set that val at left and move left up 

    [0, 1, 2, 2, 3, 0, 4, 2] = [0, 1, 3, 0, 4, -, -, -] 
    */

    int k = 0; 
    int left = -1; 
    for (int right = 0; right < nums.size(); right++) {
        int right_val = nums[right]; 

        if (right_val == val && left == -1) left = right; 

        else if (right_val != val) { 
            k++; 
            if (left != -1) {
                nums[left] = right_val; 
                left++; 
            }
        }

    }

    return k; 
}; 


int Array::search_insert(std::vector<int>& nums, int target) {
    /*
    Approaches: 
    - O(logn), binary search, move window left if target is > or move right if < mid value, if we are at the smallest window size of two elements determine where the target val will be inserted 

    [1, 2, 3, 4, 5, 7] 
    [0, 2, 3, 4, 5, 7]
    [1, 3, 5, 6] 
    */

    int left = 0; 
    int right = nums.size() - 1;  
    int mid = -1; 

    while (left != right) { 
        mid = (left + right) / 2; 

        if (left == mid) target > nums[mid] ? left = right : right = left; 

        else if (target > nums[mid]) left = mid; 

        else if (target < nums[mid]) right = mid; 

        else return mid; 

    }

    return target > nums[left] ? left + 1 : left; 
}; 


std::vector<int> Array::plus_one(std::vector<int> &digits) { 
    /*
    Approach:  
    - O(n), add one to final element, while there is a carry keep adding it to the elements until there is no carry then return digits, otherwise in the end we have to insert carry into the front of digits 

    */
    int curr_digit = -1; 
    for (int i = digits.size() - 1; i >= 0; i--) {
        curr_digit = digits[i]; 
        curr_digit++; 

        if (curr_digit / 10) digits[i] = 0; 
        else {
            digits[i] = curr_digit;
            break; 
        } 
    }

    if (curr_digit / 10) digits.insert(digits.begin(), 1); 
    return digits; 
}; 


void Array::merge(std::vector<int> &nums_1, int m, std::vector<int> &nums_2, int n) { 
    /*
    Approaches: 
    - compare element by element, if a val needs to be inserted into nums_1 then shift all the values to the left 
    - O(2 * (n + m)), compare element by element, save values into a separate list, write values back into nums_1, 
   
    [1, 3, 5, 0, 0, 0], [2, 4, 6] 
    [1, 3, 5, 0, 0, 0] 
    */

    int nums_1_ptr = 0; 
    int nums_2_ptr = 0; 
    std::vector<int> result; 
    while (nums_1_ptr != m || nums_2_ptr != n) {
        if (nums_1_ptr == m) {
            result.push_back(nums_2[nums_2_ptr]); 
            nums_2_ptr++; 
        }

        else if (nums_2_ptr == n) { 
            result.push_back(nums_1[nums_1_ptr]); 
            nums_1_ptr++;  
        }

        else if (nums_1[nums_1_ptr] <= nums_2[nums_2_ptr]) { 
            result.push_back(nums_1[nums_1_ptr]); 
            nums_1_ptr++;  
        } 

        else {
            result.push_back(nums_2[nums_2_ptr]); 
            nums_2_ptr++; 
        }
    }

    for (int i = 0; i < m + n; i++) {
        nums_1[i] = result[i]; 
    }
}; 


int Array::first_stable_index(std::vector<int> &nums, int k) { 
    /*
    Approaches: 
    - O(n), first idx is the max left and the last idx is the min right, move left and right and track the new max and min as if you started at that index, once we are halfway we can start calculating the stability of the left and right pointers 
    
    */

    int max_left_values[nums.size()]; 
    int min_right_values[nums.size()]; 

    int max_left = 0; 
    int min_right = 1e9; 

    int first_index = -1; 

    int right = nums.size() - 1; 
    for (int left = 0; left < nums.size(); left++) {
        int left_value = nums[left]; 
        int right_value = nums[right]; 

        max_left = std::max(max_left, left_value); 
        min_right = std::min(min_right, right_value); 

        max_left_values[left] = max_left; 
        min_right_values[right] = min_right; 

        if (left >= nums.size() / 2) { 
            if (max_left_values[right] - min_right_values[right] <= k) {
                if (first_index == -1) first_index = right; 
                else first_index = right; 
            } 

            if (max_left_values[left] - min_right_values[left] <= k) {
                if (first_index == -1) first_index = left; 
                else first_index = std::min(first_index, left); 
            }; 
        }

        right--; 
    }

    return first_index; 
}; 


int Array::majority_element(std::vector<int> &nums) { 
    /*
    Approaches: 
    - O(n) time, O(unique nums) space, Use hash map, track majority num as we iterate, 
    - O(n) time, O(1) space, Boyer-Moore majority vote algorithm, start candidate with vote of 1, if the next num is same increment otherwise decrement, if vote is 0 set the current num as new candidate, in the end one candidate should remain, 

    */

    int vote = 1; 
    int candidate = nums[0]; 

    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] == candidate) vote++; 
        else vote--; 

        if (vote == 0) {
            candidate = nums[i]; 
            vote = 1;
        }
    }

    return candidate; 
}; 


std::vector<int> Array::intersection(std::vector<int> &nums_1, std::vector<int> &nums_2) {
    /*
    Approaches: 
    - O(n + m) time, O(n + k) space, use a set to save seen vals for nums_1 then check nums_2 and remove intersecting numbers from seen to prevent duplicates, 

    nums_1 = [4, 9, 5, 4], nums_2 = [9, 4, 9, 8, 4], result = [4, 9] 
    */

    std::unordered_set<int> seen_nums_1; 

    for (auto &num : nums_1) seen_nums_1.insert(num); 

    std::vector<int> result; 
    for (auto &num : nums_2) { 
        if (seen_nums_1.contains(num)) { 
            seen_nums_1.erase(num); 
            result.push_back(num); 
        } 
    } 

    return result; 
}; 