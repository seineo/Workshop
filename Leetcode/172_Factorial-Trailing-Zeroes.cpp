/*
 *  problem: https://leetcode-cn.com/problems/factorial-trailing-zeroes/
 */

//The number of trailing zeroes is actually the number of min{2,5} since 10 = 2 * 5.
//And it's straightforward that 2 appears much more times than 5, so we only need to count
//the times 5 appears. But the answer isn't n / 5. Let n = 130, for example, then:
//n! = 1 * 2 * 3 … *(1 * 5) * … * (2 * 5) … * (1 * 5 * 5) * … * (2 * 5 * 5) … * (1 * 5 * 5 * 5) … * 130.
//So the answer should be n / 5 + n / 25 + n / 125 + … 

//Time complexity: O(logn)
//Space complexity: O(1)

class Solution {
public:
    int trailingZeroes(int n) {
       int count_5 = 0;
       while(n > 0) {
           n /= 5;
           count_5 += n;
       }
       return count_5;
    }
};
