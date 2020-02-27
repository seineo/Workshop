/*
 *  problem: https://leetcode-cn.com/problems/house-robber/
 */

//Solution(Dynamic Programming):
//Time complexity: O(n)
//Space complexity: O(1)

//How to approach most of DP problems:
//(Reference:https://leetcode.com/problems/house-robber/discuss/156523/From-good-to-great.-How-to-approach-most-of-DP-problems.)
//1.Find recursive relation
//2.Recursive (top-down)
//3.Recursive + memo (top-down)
//4.Iterative + memo (bottom-up)
//5.Iterative + N variables (bottom-up)

class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size() == 0)
            return 0;
        if(nums.size() == 1)
            return nums[0];
        if(nums.size() == 2)
            return max(nums[0],nums[1]);
        int size = nums.size();
        int a = nums[0];
        int b = max(nums[0],nums[1]);
        int result = 0;
        for(int i = 2;i != size;++i) {
            result = max(nums[i] + a,b);
            a = b;
            b = result;
        }
        return result;
    }
};
