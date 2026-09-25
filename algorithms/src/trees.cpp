#include "algorithms/trees.hpp" 



int Tree::max_depth(TreeNode* root) {
    if (root == nullptr) return 0; 
    /*
    Solution 1: recursion, return max of left and right child depth 
    */
    int depth = 1; 

    // Base case 
    if (root->left == nullptr && root->right == nullptr) {
        return 1; 
    }

    depth += std::max(max_depth(root->left), max_depth(root->right)); 

    return depth; 
}; 


bool Tree::is_same_tree(TreeNode* p, TreeNode* q) { 
    /* 
    Approaches: 
    - O(n + n), n is number of nodes in a tree, traverse both trees with the same traversal, save visited nodes in two containers, in the end see if they are the same  
    - O(n), BFS, if at any point the nodes are different return false, 
    - O(n), recursion, return false if two nodes are not the same  
    */

    if (p == nullptr && q == nullptr) return true; 

    if (p == nullptr && q != nullptr || p != nullptr && q == nullptr) return false; 

    return (p->val == q->val && is_same_tree(p->left, q->left) && is_same_tree(p->right, q->right)); 
}; 


TreeNode* Tree::invert_tree(TreeNode* root) { 
    /*
    Approaches: 
    - O(V), recursively swap the left and right children 

    */

    if (root == nullptr) return nullptr; 
    root->left =  invert_tree(root->left); 
    root->right = invert_tree(root->right); 

    TreeNode* swap_node; 
    swap_node = root->left; 
    root->left = root->right; 
    root->right = swap_node; 

    return root; 
}; 


std::vector<std::vector<int>> Tree::level_order(TreeNode* root) { 
    if (root == nullptr) return {}; 
    /*
    Approaches: 
    - O(V), We add the children of all nodes in the current layer using a queue 
    */

    std::vector<std::vector<int>> level_order {}; 
    std::queue<TreeNode*> level_nodes; 
    level_nodes.push(root); 

    while (!level_nodes.empty()) {
        std::vector<int> level_values; 
        int level_length = level_nodes.size(); 
        // level_values.reserve(level_length); // Reserve length of vector, prevents resizing which can be time expensive 

        for (int i = 0; i < level_length; i++) {
            auto current_node = level_nodes.front(); 
            level_nodes.pop(); 

            level_values.push_back(current_node->val); 

            auto left_node = current_node->left; 
            auto right_node = current_node->right; 

            if (left_node != nullptr) level_nodes.push(left_node); 
            if (right_node != nullptr) level_nodes.push(right_node); 
        }

        level_order.push_back(level_values); 
    }

    return level_order; 

    /* 
    std::vector<int> next_layer_vals; 

    std::queue<TreeNode*> current_layer; 
    std::queue<TreeNode*> next_layer; 
    current_layer.push(root); 

    while (!current_layer.empty()) { 

        TreeNode* current_node = current_layer.front(); 
        current_layer.pop(); 

        if (current_node->left != nullptr) { 
            next_layer_vals.push_back(current_node->left->val); 
            next_layer.push(current_node->left); 
        }
        
        if (current_node->right != nullptr) { 
            next_layer_vals.push_back(current_node->right->val); 
            next_layer.push(current_node->right); 
        } 

        if (current_layer.size() >= 1) continue; 
        if (next_layer.empty()) break; 

        level_list.push_back(next_layer_vals); 
        next_layer_vals.clear(); 

        current_layer = next_layer; 
        std::queue<TreeNode*> empty; 
        std::swap(next_layer, empty); 
    }

    return level_list; 
    */

}; 


bool Tree::is_subtree(TreeNode* root, TreeNode* sub_root) { 
    /*
    Approaches: 
    - O(V * v) recursive approach, check if current tree is same as subtree, if not check if left or right are same as subtree, for each node in the tree check if it is the subtree, this is like double recursive 

    */    

    if (root == nullptr && sub_root == nullptr) return true; 

    if ((root != nullptr && sub_root == nullptr) || (root == nullptr && sub_root != nullptr)) return false; 

    if (root->val == sub_root->val) { 
        return is_same_tree(root, sub_root) ? true : (is_subtree(root->left, sub_root) || is_subtree(root->right, sub_root)); 
    }

    else return (is_subtree(root->left, sub_root) || is_subtree(root->right, sub_root)); 
}; 


std::vector<int> Tree::inorder_traversal(TreeNode *root) {
    /*
    Approaches: 
    - O(V) time, use recursion, check left child first then you visit yourself and check right child next, this is inorder 

    */

    std::vector<int> traversal; 

    auto inorder = [&](this const auto &self, TreeNode* root, std::vector<int> &traversal) -> void { 
        if (root == nullptr) return; 

        self(root->left, traversal); 

        traversal.push_back(root->val); 

        self(root->right, traversal); 
    }; 

    inorder(root, traversal); 

    return traversal; 
}; 