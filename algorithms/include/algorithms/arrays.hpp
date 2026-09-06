#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <map> 
#include <set>
#include <unordered_set> 
#include <unordered_map> 
#include <queue> 
#include <cmath> 


class Array {
    public: 
        // O(n), clone collection and append it's own items to itself, iterate through list of length n 
        std::vector<int> get_concatenation(std::vector<int> &nums); 

        // O(n), place items from second half between items in first half, 2 * n operations 
        std::vector<int> shuffle(std::vector<int> &nums); 

        // O(n), iterate once, keep track of longest sequence, iterate list length n 
        int find_max_consecutive_ones(std::vector<int> &nums); 

        // O(2n) = O(n), Use set to find duplicate, iterate through and check which number is missing from set, n + n operations 
        // O(n), iterate through vector, keep track of natural sum to n as well as sum of vector and track duplicate, in the end we know we can subtract the duplicate and the missing number will add to that to match the natural sum of n 
        std::vector<int> find_error_nums(std::vector<int> &nums); 

        // O(n), Iterate once, as we find largest value, assign second largest, iterate list of length n, 
        int second_largest(std::vector<int> &nums); 

        // O(n), Sort and use two pointers, moving respective pointers if the sum is too big or small, iterate through 
        // O(n), Use set to save seen values, check if target - current exists already, iterate through 
        std::tuple<int, int> two_sum(const int target, std::vector<int> &nums); 

        // O(n) iterate through keep track of largest profit, save smallest and check profit, if we find smaller restart 
        int max_profit(std::vector<int> &prices); 

        // O(n), iterate through and use separate unordered set to track duplicates, unordred saves time! 
        bool contains_duplicate(std::vector<int> &nums); 

        // O(2n) = O(n), find prefix and postfix products, then multiply the prefix and post fix for each element 
        std::vector<int> product_except_self(std::vector<int> &nums); 

        // O(n), sliding window, move left pointer if the current sum is negative and start over again from the right, 
        int max_sub_array(std::vector<int> &nums); 

        // O(2n) = O(n), worst case we have to check every element twice, we use a window taking product of items, if we hit a zero shrink window keeping track of remaining product after dividing out terms, move past zero repeat, shrink again at the end 
        int max_product(std::vector<int> &nums); 

        // O(n + mlogm) = O(mlogm), if modulo is 0 then it is a multiple, we can calculate multiple by dividing, save the multiples in a sorted vector then iterate and find the smallest missing one 
        int missing_multiple(std::vector<int> &nums, int k); 

        // O(n), left and right pointer, when the right detects a new unique num move left one spot and place it, track the current unique num 
        int remove_duplicates(std::vector<int> &nums); 

        // O(n), move right until we hit num == val set the left pointer here, from now on any time num != val set that val at left and move left up 
        int remove_element(std::vector<int>& nums, int val);  

        // O(logn), binary search, move window left if target is > or move right if < mid value, if we are at the smallest window size of two elements determine where the target val will be inserted 
        int search_insert(std::vector<int>& nums, int target); 

        // O(n), add one to final element, while there is a carry keep adding it to the elements until there is no carry then return digits, otherwise in the end we have to insert carry into the front of digits 
        std::vector<int> plus_one(std::vector<int> &digits); 

        // O(2 * (n + m)), compare element by element, save values into a separate list, write values back into nums_1, 
        void merge(std::vector<int> &nums_1, int m, std::vector<int> &nums_2, int n);  

        // O(n), first idx is the max left and the last idx is the min right, move left and right and track the new max and min as if you started at that index, once we are halfway we can start calculating the stability of the left and right pointers 
        int first_stable_index(std::vector<int> &nums, int k); 

        // O(n) time, O(1) space, Boyer-Moore majority vote algorithm, start candidate with vote of 1, if the next num is same increment otherwise decrement, if vote is 0 set the current num as new candidate, in the end one candidate should remain, 
        int majority_element(std::vector<int> &nums); 
}; 

/*
Blind 75 List 
Completed: 
- (Easy) Two Sum 
- (Easy) Best Time to Buy and Sell Stock 
- (Easy) Contains Duplicate 
- (Medium) Product of Array Except Self
- (Medium) Maximum Subarray 

TODO: 
- Maximum Product Subarray
- Find Minimum in Rotated Sorted Array
- Search in Rotated Sorted Array
- 3 Sum
- Container With Most Water
*/