#include "algorithms/dynamic_programming.hpp" 



int DynamicProgramming::nth_fibonacci(const int n) {

    // Base case 
    if (n == 0) return 0; 
    if (n == 1 || n == 2) return 1; 

    // Memoization ! 
    std::unordered_map<int, int> nth_value_map; 
    nth_value_map[0] = 0; 
    nth_value_map[1] = 1; 
    nth_value_map[2] = 1; 

    for (int i = 3; i <= n; i++) {
        nth_value_map[i] = nth_value_map[i - 1] + nth_value_map[i - 2]; 
    } 

    return nth_value_map.at(n); 
}; 


int DynamicProgramming::climb_stairs(const int n) {

    /* 
    1, 1 base case 
    2, 11, 2
    3, 111, 12, 21 
    4, 1111, 112, 211, 121, 22, 

    memoization? 
    */

    std::unordered_map<int, int> possible_steps; 
    possible_steps[1] = 1; // Base case 
    possible_steps[2] = 2; 

    if (n > 2) {
        for (int i = 3; i <= n; i++) { 
            possible_steps[i] = possible_steps[i - 1] + possible_steps[i - 2]; 
        }
    }
    
    return possible_steps[n]; 
}; 


int DynamicProgramming::coin_change(std::vector<int> &coins, int amount) {
    /*
    3, 4 = 12 
    12 - 3, 12 - 4 = 9, 8 -> 3, 2 

    8 - 3, 8 - 4 = 5, 4 -> -1, 1 

    4 -> 1 
    */

    std::unordered_map<int, int> fewest_moves; 

    // Base case 
    for (auto denomination : coins) {
        fewest_moves[denomination] = 1; 
    }

    for (int value = 1; value <= amount; value++) { 
        if (fewest_moves.find(value) != fewest_moves.end()) continue; 

        int smallest = -1; 

        for (auto denomination : coins) { 
            int difference = value - denomination; 

            if (difference < 0) continue; 

            int current_smallest = fewest_moves[difference]; 

            if (current_smallest < 0) continue; 

            if (current_smallest < smallest || smallest < 0) smallest = current_smallest; 
        } 

        if (smallest >= 1) fewest_moves[value] = smallest + 1; 
        else fewest_moves[value] = smallest; 
    } 

    return fewest_moves[amount]; 
}; 


int DynamicProgramming::length_of_LIS(std::vector<int> &nums) { 
    /*
    Approaches: 
    - O(nlogn + n^2) = O(n^2), Sort the list first, then for each item in the list compare it's original index to the rest, increasing the length if the index is larger than the current smallest, nvm doesnt work ! 
    - ^ If we see a larger increasing sequence first and later a smaller but still increasing sequence, the smaller sequence will take over and we will miss the larger sequence from earlier 


    [10, 9, 2, 6, 7, 3, 4, 1, 5, 8, 11, 12, 0] = 2, 3, 4, 5, 8, 11, 12 

    [2, 6, 7, 3, 8, 9] = 2, 6, 7, 8, 9 // This disproves the first approach 
    [0, 3, 1, 2, 4, 5] 

    - O(1/2 * n^2), save the LIS for each number, when we reach a number iterate backwards adding the LIS of numbers smaller than itself if the sum is greater than it's current LIS 
    [0, 4, 5, 7, 2, 8, 9, 1, 2, 3, 6] = 0, 1, 2, 3, 6 
    [1, 2, 3, 4, 2, 5, 6] 

    [10, 9, 2, 6, 7, 3, 4, 1, 5, 8, 11, 12, 0] 
    [ 1, 1, 1, 2, 3, 2, 3, 1, 4, 5,  6,  7, 1] 
    */

    std::unordered_map<int, int> LIS; 
    int max_LIS = 1; 
    LIS[nums[0]] = 1; 

    for (int right = 1; right < static_cast<int>(nums.size()); right++) { 
        int current_LIS = 1; 
        int current_value = nums.at(right); 

        for (int left = right - 1; left >= 0; left--) { 
            int prev_value = nums.at(left); 
            if (prev_value < current_value) { 
                current_LIS = std::max(current_LIS, LIS[prev_value] + 1); 
            }
        }

        max_LIS = std::max(current_LIS, max_LIS); 
        LIS[current_value] = current_LIS; 
    }

    return max_LIS; 
}; 


int DynamicProgramming::longest_common_subsequence(std::string text_1, std::string text_2) {
    /*
    Approaches: 
    - save subsequences from both texts into separate sets, see if any of the subs in set 1 are in set 2, doesn't work if we can delete characters 
    - save subs and their permutations then check if other text contains one of them, this would be very expensive, could help if we just look at the smaller text 
    - Use 2D array, if two letters at i and j are equal, check all previous rows before i up until j and take max(ij, ij + 1), this soln takes too long ! 
    - Use 2D array, carry over info from the previous row, if i and j are the same add one to the LCS from the previous row and carry that for the rest of the row 
    - O(n * m), save the LCS for each position in text 1, compare the char in text 2, track the current length, if the current length < LCS at that index then make the curr len equal to that LCS, if the two char are the same LCS at that index = curr len + 1, 


    text1 = "abcde", text2 = "afshe" 
    text1 = "abcde", text2 = "ce" 
    */

    std::vector<int> LCS(text_1.size(), 0); 
    int longest = 0; 

    for (auto &_char : text_2) {
        int current_length = 0; 
        for (int i = 0; i < text_1.size(); i++) {
            if (current_length < LCS[i]) current_length = LCS[i]; 
            else if (_char == text_1[i]) {
                LCS[i] = current_length + 1; 
                longest = std::max(longest, current_length + 1); 
            } 
        }
    }

    return longest; 

    /* 
    // Third approach, took too long 
    int LCS[text_1.size()][text_2.size()]; 

    int max = 0; 
    for (int i = 0; i < text_1.size(); i++) { 
        for (int j = 0; j < text_2.size(); j++) { 

            if (text_1[i] == text_2[j]) {
                int find_max = 1; 

                for (int i_search = 0; i_search < i; i_search++) { 
                    for (int j_search = 0; j_search < j; j_search++) { 
                        find_max = std::max(find_max, LCS[i_search][j_search] + 1); 
                    }
                }

                LCS[i][j] = find_max; 
                max = std::max(max, find_max); 

                if (find_max == 2) continue; 
            }

            else LCS[i][j] = 0; 
        }
    }

    return max; 
    */
}; 


std::vector<std::vector<int>> DynamicProgramming::pascals_triangle(int num_rows) { 
    /*
    Approaches: 
    - O(n^2), for a given index n in curr_row it's value is prev_row[n - 1] + prev_row[n], the ith row has i + 1 elements, 

    */

    std::vector<std::vector<int>> triangle; 

    // Base case, we have at least one row so add it first 
    std::vector<int> prev_row {1}; 
    triangle.push_back(prev_row); 

    for (int ith_row = 1; ith_row < num_rows; ith_row++) { 
        std::vector<int> curr_row(ith_row + 1, 1); 

        for (int row_idx = 1; row_idx < ith_row; row_idx++) { 
            curr_row[row_idx] = (prev_row[row_idx - 1] + prev_row[row_idx]); 
        } 

        triangle.push_back(curr_row); 
        prev_row = std::move(curr_row); 
    }

    return triangle; 
}; 


std::vector<int> DynamicProgramming::pascals_triangle_row(int row_index) { 
    /*
    Approaches: 
    - O(n^2), for a given index n in curr_row it's value is prev_row[n - 1] + prev_row[n], the ith row has i + 1 elements, return row

    */

    // Base case, at least one row 
    std::vector<int> prev_row {1}; 

    for (int i = 1; i <= row_index; i++) { 
        std::vector<int> curr_row(i + 1, 1); 

        for (int j = 1; j < i; j++) {
            curr_row[j] = prev_row[j - 1] + prev_row[j]; 
        }

        prev_row = std::move(curr_row); 
    }

    return prev_row; 
}; 


std::vector<long long> DynamicProgramming::result_array(std::vector<int> &nums, int k) { 
    /*
    Approaches: 
    - O(n + k*n*3) = O(k * n) time, O(3*n) = O(n) space, brute force, calculate products for each index if you remove the prefx/suffix/both, so three possible operations per element, we go through our product list and mod by k and see if we get our x value, nvm this is not the right soln.! 
    - O(k * n) time, find all possible contiguous subarrays if you removed prefix/suffix/both, calculate the products and mod by k to get the remainder, count the frequencies for each remainder and return that freq count,
 
    */

    std::vector<long long> x_values(k); 
    int freq[5] = {0}; 

    for (auto &num: nums) {
        num %= k; 
        int cur[5] = {0}; 
        cur[num]++; 

        for (int x = 0; x < k; x++) cur[x * num % k] += freq[x]; 

        for (int x = 0; x < k; x++) {
            freq[x] = cur[x]; 
            x_values[x] += freq[x]; 
        }
    }

    return x_values; 
}; 


std::vector<int> DynamicProgramming::count_bits(int n) {
    /*
    Approaches:  
    - separate n by it's respective groups 2^x, every time we hit a 2^x number we can reuse the previous group values, 
    - O(n) time, O(n) space, group n by 2^x groups, every time we reach a new group we know there will be an extra one and we reuse all the previous group values to makeup the next group, 
    
    */

    std::vector<int> bit_map(n + 1, 0); 

    int current = 1; int reuse = 1; int power = 1; 

    while (current <= n) { 
        if (current < power) {
            bit_map[current] = bit_map[reuse] + 1; 
            reuse++; 
        }

        else {
            bit_map[current] = 1; 
            power *= 2; 
            reuse = 1; 
        }

        current++; 
    }

    return bit_map; 
}; 


int DynamicProgramming::min_cost_climbing_stairs(std::vector<int> &stairs) {
    /*
    Approaches: 
    - O(n) time, O(n) space, calculate the min cost to go for each stair by taking the min cost to go of the previous two steps

    */

    std::vector<int> costs(stairs.size(), 0); 

    auto cost_to_go = [&](int step) {
        return std::min(costs[step - 1] + stairs[step - 1], costs[step - 2] + stairs[step - 2]); 
    }; 

    for (int step = 2; step < stairs.size(); step++) {
        costs[step] = cost_to_go(step); 
    } 

    return cost_to_go(stairs.size()); 
}; 


int DynamicProgramming::tribonacci(int n) {
    /*
    Approaches: 
    - O(n) time, O(n) space, cache the tribonacci value for every number up to n 
    
    */    

    std::vector<int> tribonacci_values(38, 1); 
    tribonacci_values[0] = 0; 

    for (int i = 3; i <= n; i++) { 
        tribonacci_values[i] = (tribonacci_values[i - 1] + tribonacci_values[i - 2] + tribonacci_values[i - 3]); 
    }

    return tribonacci_values[n]; 
}; 