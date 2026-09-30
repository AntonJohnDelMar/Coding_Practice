// Add files 
#include "design_patterns/singleton.hpp" 
#include "design_patterns/factory_method.hpp" 
#include "algorithms/arrays.hpp" 
#include "algorithms/strings.hpp" 
#include "algorithms/dynamic_programming.hpp" 
#include "algorithms/linked_lists.hpp" 
#include "algorithms/trees.hpp" 
#include "algorithms/graphs.hpp" 
#include "algorithms/math.hpp" 
#include "threads/threading.hpp" 
#include "matrices/matrix.hpp" 



int main(int argv, char* argc[]) { 
    auto algorithm = Tree(); 

    TreeNode* node_7 = new TreeNode(3); 
    TreeNode* node_6 = new TreeNode(4); 
    TreeNode* node_5 = new TreeNode(4); 
    TreeNode* node_4 = new TreeNode(3); 
    TreeNode* node_3 = new TreeNode(2, node_6, node_7); 
    TreeNode* node_2 = new TreeNode(2, node_4, node_5); 
    TreeNode* node_1 = new TreeNode(1, node_2, node_3); 

    auto result = algorithm.is_symmetric(node_1); 

    return 0; 
} 