#include <iostream> 
#include <algorithm> 
#include <queue> 
#include <vector> 



struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Tree {
    public: 
        TreeNode* root; 

        // O(V), we have to traverse through each node on the tree, use recursion to determine if left or right subtree is larger 
        int max_depth(TreeNode* root); 

        // O(V), use recursion, check if p and q value is equal as well as their right and left subtrees 
        bool is_same_tree(TreeNode* p, TreeNode* q); 

        // O(V), recursively swap left and right children 
        TreeNode* invert_tree(TreeNode* root); 

        // O(V), We add the children of all nodes in the current layer using a queue 
        std::vector<std::vector<int>> level_order(TreeNode* root); 

        // O(V * v) = O(V^2), recursive approach, check if current tree is same as subtree, if not check if left or right are same as subtree, for each node in our tree check if it is a subtree, this is doubly recursive 
        bool is_subtree(TreeNode* root, TreeNode* subRoot); 

        // O(V) time, use recursion, check left child first then you visit yourself and check right child next, this is inorder 
        std::vector<int> inorder_traversal(TreeNode *root); 
}; 

/*
Blind 75 List 
Completed: 
- (Easy) Maximum Depth of Binary Tree 
- (Easy) Same Tree
- (Easy) Invert/Flip Binary Tree
- (Medium) Binary Tree Level Order Traversal 

TODO: 
- Binary Tree Maximum Path Sum
- Serialize and Deserialize Binary Tree
- Subtree of Another Tree
- Construct Binary Tree from Preorder and Inorder Traversal
- Validate Binary Search Tree
- Kth Smallest Element in a BST
- Lowest Common Ancestor of BST
- Implement Trie (Prefix Tree)
- Add and Search Word
- Word Search II
*/

/*
Tree alg; 

TreeNode* node_7 = new TreeNode(7); 
TreeNode* node_6 = new TreeNode(6); 
TreeNode* node_5 = new TreeNode(5); 
TreeNode* node_4 = new TreeNode(4); 
TreeNode* node_3 = new TreeNode(3, node_6, node_7); 
TreeNode* node_2 = new TreeNode(2, node_4, node_5); 
TreeNode* node_1 = new TreeNode(1, node_2, node_3); 

auto result = alg.level_order(node_1); 
*/

/*
auto algorithm = Tree(); 

TreeNode* sub_tree_left = new TreeNode(1); 
TreeNode* sub_tree_right = new TreeNode(2); 
TreeNode* sub_tree_root = new TreeNode(3, sub_tree_left, sub_tree_right); 

TreeNode* one_node = new TreeNode(1); 
TreeNode* two_node = new TreeNode(2, nullptr, sub_tree_root); 
TreeNode* four_node = new TreeNode(4, one_node, nullptr); 
TreeNode* five_node = new TreeNode(5, two_node, nullptr); 
TreeNode* root = new TreeNode(3, four_node, five_node); 

auto result = algorithm.is_subtree(root, sub_tree_root); 

std::cout << result << std::endl; 
*/