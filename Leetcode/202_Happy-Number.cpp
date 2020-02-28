/*
 *  problem: https://leetcode-cn.com/problems/happy-number/
 */

//Like the Linked List Cycle detection problem, we can adapt the Floyd Cycle detection algorithm(fast and slow pointers)
//If it is a happy number than it will stay at one and the slow pointer will eventually catch up.
//On the other hand, there must be a recurring number.

class Solution {
public:
    int digit_square_sum(int n) {
        int sum = 0;
        while(n > 0) {
            int digit = n % 10;
            sum += digit * digit;
            n /= 10;
        }
        return sum;
    }
    bool isHappy(int n) {
        int fast = n, slow = n;
        do {
            slow = digit_square_sum(slow);
            fast = digit_square_sum(digit_square_sum(fast));
        } while(fast != slow);
        return fast == 1;
    }
};
