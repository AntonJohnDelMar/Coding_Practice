#include "algorithms/linked_lists.hpp"



void LinkedList::delete_list(ListNode* head) { 
    ListNode* temp = nullptr; 

    // [1, 2, 3, 4, 5] 
    while (head->next != nullptr) {
        temp = head; 
        head = head->next; 
        delete temp; 
    }

    delete head; 
}; 


ListNode* LinkedList::generate_list(std::vector<int> values) { 
    ListNode* current_node = nullptr; 
    ListNode* root = current_node; 

    for (auto &val : values) {
        if (root == nullptr) {
            current_node = new ListNode(val, nullptr); 
            root = current_node; 
        }

        else {
            ListNode* new_node = new ListNode(val, nullptr); 
            current_node->next = new_node; 
            current_node = current_node->next; 
        }
    }

    return root; 
}; 


ListNode* LinkedList::reverse_list(ListNode* head) { 
    if (head == nullptr) return nullptr; 

    /*
    Approach: 
    - O(2n), use stack, add nodes to the stack, connect nodes as we pop from the stack 
    - O(n), use temp variable to save previous and next node 

    [1, 2, 3, 4, 5] 
    */

    ListNode* prev_node = nullptr; 
    ListNode* next_node = nullptr; 

    while (head->next != nullptr) {
        next_node = head->next; 
        head->next = prev_node; 
        prev_node = head; 
        head = next_node; 
    } 

    head->next = prev_node; 
    return head; 
}; 


bool LinkedList::has_cycle(ListNode *head) {
    /*
    Approaches: 
    - O(n), iterate through the linked list, use a set to see if we have seen a node before 
    - O(max_itr), if the while loop cycles past the max # of possible nodes there is a cycle, 
    - slow fast pointer approach, the fast will catch the slow if cycle, fast goes next by two slow goes next by one 

    */
    if (head == nullptr) return false; 

    int max_iterations = 1e4 + 1; 
    int counter = 1; 
    while (head->next != nullptr) { 
        ++counter; 
        if (counter >= max_iterations) return true; 
        head = head->next; 
    }

    return false; 
}; 


ListNode* LinkedList::merge_two_lists(ListNode* list_1, ListNode* list_2) {
    /*
    Approaches: 
    - if list_2 node is greater add list_1 node, switch once list_1 node is greater, go until we hit nullptr for both 

    */

    ListNode* root_node = nullptr; 
    ListNode* current_node = nullptr; 

    auto assign_and_move = [&](ListNode* &move_node) { 
        if (current_node == nullptr) {
            current_node = move_node;
            root_node = current_node; 
        }  

        else {
            current_node->next = move_node; 
            current_node = current_node->next; 
        } 

        move_node = move_node->next; 
    }; 

    while (list_1 != nullptr || list_2 != nullptr) { 

        if (list_1 == nullptr) assign_and_move(list_2); 

        else if (list_2 == nullptr) assign_and_move(list_1); 

        else {
            if (list_1->val <= list_2->val) assign_and_move(list_1); 
            else assign_and_move (list_2); 
        } 

    }

    return root_node; 
}; 


ListNode* LinkedList::add_two_numbers(ListNode* list_1, ListNode* list_2) { 
    /*
    Approaches: 
    - O(n + m + o), obtain int representation of both numbers by iterating, add them, then find linked list representation of the sum 
    - O(n), add two nodes at a time, track the carry by dividing by 10, get remainder with modulo 10 

    */ 

    ListNode* current_number = nullptr; 
    ListNode* root = nullptr; 

    int carry = 0; 
    while (list_1 != nullptr || list_2 != nullptr || carry != 0) { 
        int val_1 = list_1 != nullptr ? list_1->val : 0; 
        int val_2 = list_2 != nullptr ? list_2->val : 0; 

        int sum = val_1 + val_2 + carry; 
        int remainder = sum % 10; 
        carry = sum / 10; 

        ListNode* new_number = new ListNode(remainder, nullptr); 

        if (current_number == nullptr) {
            current_number = new_number; 
            root = current_number; 
        }

        else {
            current_number->next = new_number; 
            current_number = current_number->next; 
        }

        list_1 = list_1 != nullptr ? list_1->next : list_1; 
        list_2 = list_2 != nullptr ? list_2->next : list_2; 
    }

    return root; 
}; 


std::vector<int> LinkedList::nodes_between_critical_points(ListNode* head) {
    /* 
    Approaches: 
    - use a window as we iterate through the list, in this case the window is achieved by saving our previous value and just comparing our node val next node val and prev node val, as we move the window we keep track of the index of the middle element, with another list we track critical points 
    - o(n), track prev val to compare prev current and next val for crit point, save idx of first crit point for later, as we add crit points check dist between prev and current crit point for min distance, in the end check first and last crit point for max distance 

    [5, 3, 1, 2, 5, 1, 2] 

    [1, 3, 2, 4] 
    */

    int first_idx = -1; 
    int prev_idx = -1; 
    int idx = 0; 

    int min_distance = 1e6; 

    int prev_value = -1; 
    while (head->next != nullptr) { 
        int current_value = head->val; 
        int next_value = head->next->val; 

        bool is_min = (current_value < prev_value && current_value < next_value); 
        bool is_max = (current_value > prev_value && current_value > next_value); 
        if ((is_min || is_max) && prev_value != -1) { 
            if (prev_idx != -1) min_distance = std::min(min_distance, idx - prev_idx);
            else first_idx = idx; 

            prev_idx = idx; 
        }

        prev_value = current_value; 
        idx++; 
        head = head->next; 
    } 

    if (prev_idx == first_idx) return {-1, -1}; 
    else {
        int max_distance = prev_idx - first_idx; 
        return {min_distance, max_distance}; 
    } 
}; 


ListNode* LinkedList::delete_duplicates(ListNode* head) {
    /*
    Approaches: 
    - use a set to track unique vals, to delete a dup node just connect the prev node to dup nodes next node, 
    - since the list is sorted already just check if the current val equals the prev val, to delete a dup node just connect the prev node to dup nodes next node, 
    - O(n) time, O(1) space, list is sorted so check if next val equals curr val, delete dup by skipping the next val since it is a dup 

    */
    ListNode* curr_node = head; 

    while (curr_node != nullptr && curr_node->next != nullptr) { 

        while (curr_node->next != nullptr && curr_node->val == curr_node->next->val) {
            curr_node->next = curr_node->next->next; 
        }

        curr_node = curr_node->next; 
    }

    return head; 
}; 


ListNode* LinkedList::get_intersection_node(ListNode* head_A, ListNode* head_B) { 
    /*
    Approaches: 
    - O(n + m) time, O(n + m) space, itr through both linked lists and save node pointers in a set, if we find a matching node return it, 
    - O(n + m) time, O(1) space, make the lists the same size n + m the final node will be the intersect, to do this loop list A to list B when it hits it's end and vice versa, 
    
    */

    ListNode* curr_A = head_A; 
    ListNode* curr_B = head_B; 

    while (curr_A != curr_B) {
        if (curr_A == nullptr) curr_A = head_B; 
        else curr_A = curr_A->next; 

        if (curr_B == nullptr) curr_B = head_A; 
        else curr_B = curr_B->next; 
    }

    return curr_A; 
}; 


ListNode* LinkedList::remove_elements(ListNode* head, int val) {
    /*
    Approaches: 
    - O(n) time, O(1) space, itr the list and connect prev node to next node of curr node if it is the target value, 

    [7, 7, 7, 8, 9], val = 7 
    [1, 2, 3, 4, 4, 5, 6], val = 4 
    */

    ListNode* root = nullptr; 
    ListNode* prev_node = nullptr; 

    while (head != nullptr) {
        if (head->val == val) { 
            if (prev_node != nullptr) prev_node->next = head->next; 
        }

        else {
            if (prev_node == nullptr) root = head; 
            prev_node = head; 
        }

        head = head->next; 
    } 

    return root; 
}; 


bool LinkedList::is_palindrome(ListNode* head) {
    /*
    Approaches: 
    - O(n) time, O(n) space, use a stack to track elements and remove them, in the end it should be empty or have one element if it is a palindrome, doesn't work if there is odd amount of elements as we end up not popping the stack ! 
    - O(2n) = O(n) time, O(n) space, save linked list as a vector, then use two pointers to see if it is palindrome 
    - O(n) time, O(1) space, tortoise / hare algorithm, when fast reaches the end then slow is in the middle, slow will reverse the last half, then we can compare first and last half 

    */

    ListNode* slow = head; 
    ListNode* fast = head; 
    ListNode* prev = nullptr; 
    ListNode* temp = nullptr; 

    while (fast && fast->next) {
        fast = fast->next->next; 
        slow = slow->next; 
    }

    prev = slow; 
    slow = slow->next; 
    prev->next = nullptr; 

    while (slow) {
        temp = slow->next; 
        slow->next = prev; 
        prev = slow; 
        slow = temp; 
    }

    fast = head; 
    slow = prev; 

    while (slow) {
        if (slow->val != fast->val) return false; 
        else {
            slow = slow->next; 
            fast = fast->next; 
        }
    }

    return true; 
}; 