#include <iostream> 
#include <unordered_set> 
#include <vector> 
#include <queue> 



struct ListNode {
    int val; 
    ListNode* next; 

    ListNode() : val(0), next(nullptr) {}; 
    ListNode(int _val) : val(_val) {}; 
    ListNode(int _val, ListNode* _next) : val(_val), next(_next) {}; 
}; 


class LinkedList {
    public: 
        void delete_list(ListNode* head); 

        ListNode* generate_list(std::vector<int> values); 

        // O(n), connect next to current, use temp variables to save previous and next, 
        ListNode* reverse_list(ListNode* head); 

        // O(n), use set to see if next node was seen before 
        // O(max_itr), check if our loop exceeds the max list len, if it does there is a cycle, max_itr constraint was small enough for this to run in 0ms haha, 
        bool has_cycle(ListNode *head); 

        // O(n + m) = O(n), iterate through both lists, compare nodes and whichever is smaller link it to the merged list 
        ListNode* merge_two_lists(ListNode* list_1, ListNode* list_2); 

        // O(n), add two nodes at a time, track the carry by dividing by 10, get remainder with modulo 10 
        ListNode* add_two_numbers(ListNode* list_1, ListNode* list_2); 

        // O(n), track prev val to compare prev current and next val for crit point, save idx of first crit point for later, as we add crit points check dist between prev and current crit point for min distance, in the end check first and last crit point for max distance 
        std::vector<int> nodes_between_critical_points(ListNode* head); 

        // O(n) time, O(1) space, list is sorted so check if next val equals curr val, delete dup by skipping the next val since it is a dup 
        ListNode* delete_duplicates(ListNode* head); 
}; 

/* 
Blind 75 List 
Completed: 
- (Easy) Reverse a Linked List 
- (Easy) Detect Cycle in a Linked List 
- (Easy) Merge Two Sorted Lists 

TODO: 
- Merge K Sorted Lists
- Remove Nth Node From End Of List
- Reorder List


*/