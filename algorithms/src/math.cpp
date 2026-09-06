#include "algorithms/math.hpp" 



int Math::my_sqrt(int x) { 
    /*
    Approaches: 
    - O(logn) time, binary search integers and compute n^2 until we are close to x, watch out for int represent overflows 

    */

    const int MAX_SQUARE_VAL = 46340;

    int left_val = 0; 
    int right_val = x; 
    int middle_val = 0; 

    while(left_val < right_val) { 
        middle_val = ((right_val + left_val) / 2); 

        if (middle_val > MAX_SQUARE_VAL) {
            right_val = MAX_SQUARE_VAL; 
            continue; 
        } 

        if ((middle_val * middle_val) > x) right_val = middle_val - 1; 
        else if ((middle_val * middle_val) < x) left_val = middle_val + 1; 
        else break; 
    }

    if (left_val == right_val) middle_val = left_val; 
    return middle_val * middle_val > x ? middle_val - 1 : middle_val; 
}; 