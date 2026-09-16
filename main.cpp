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
    auto algorithm = LinkedList(); 
    ListNode* root = algorithm.generate_list({1, 2, 2, 1}); 

    auto result = algorithm.is_palindrome(root); 

    return 0; 
} 