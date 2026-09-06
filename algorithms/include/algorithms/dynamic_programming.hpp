#include <iostream> 
#include <vector> 
#include <algorithm>
#include <map> 
#include <unordered_map> 
#include <unordered_set> 



class DynamicProgramming {
    public: 
        // O(n), use map for cache memoization, save fib sequence value using map, 
        int nth_fibonacci(const int n); 

        // O(n), use memoization, cache values in map, check how many steps for values 1 or 2 before, i.e. for 5 check 4 and 3 
        int climb_stairs(const int n); 

        // O(denom * coins), cache saves fewest # of denominations per coin value, for each coin value up to the target calculate the fewest coins needed by subtracting the denom and checking the fewest for that value 
        int coin_change(std::vector<int> &coins, int amount); 

        // O(1/2 * n^2) = O(n^2), save the longest increasing subsequence (LIS) for each number, when we reach a number iterate backwards adding the LIS of numbers smaller than itself if the sum is greater than it's current LIS 
        int length_of_LIS(std::vector<int> &nums); 

        // O(n * m), save the LCS for each position in text 1, compare the char in text 2, track the current length, if the current length < LCS at that index then make the curr len equal to that LCS, if the two char are the same LCS at that index = curr len + 1, 
        int longest_common_subsequence(std::string text1, std::string text2); 

        // O(n^2), for a given index n in curr_row it's value is prev_row[n - 1] + prev_row[n], the ith row has i + 1 elements, 
        std::vector<std::vector<int>> pascals_triangle(int num_rows); 

        // O(n^2), for a given index n in curr_row it's value is prev_row[n - 1] + prev_row[n], the ith row has i + 1 elements, 
        std::vector<int> pascals_triangle_row(int row_index); 
}; 

/*
Blind 75 List 
Completed: 
- (Easy) Climbing Stairs 
- (Medium) Coin Change 
- (Medium) Longest Increasing Subsequence 
- (Medium) Longest Common Subsequence 

TODO: 
- Word Break Problem
- Combination Sum
- House Robber
- House Robber II
- Decode Ways
- Unique Paths
- Jump Game
*/