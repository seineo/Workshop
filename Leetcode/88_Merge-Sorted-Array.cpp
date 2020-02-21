/*
 *  problem: https://leetcode-cn.com/problems/merge-sorted-array/
 */

//Solution 1 (not so good):
//Time complexity: O(n + m)
//Space complexity: O(m)

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> nums1_copy(nums1.begin(), nums1.begin() + m);
        int p1_copy = 0, p1 = 0, p2 = 0;
        while(p1_copy != m && p2 != n)
            nums1[p1++] = (nums1_copy[p1_copy] < nums2[p2] ? nums1_copy[p1_copy++] : nums2[p2++]);
        copy(nums1_copy.begin() + p1_copy,nums1_copy.end(),nums1.begin() + p1);  //If p1_copy == m, it'll do nothing
        copy(nums2.begin() + p2, nums2.end(),nums1.begin() + p1);    //If p2 == n, it'll do nothing
        return;
    }
};

//Solution 2 (good):
//Time complexity: O(n + m)
//Space complexity: O(1)

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p1 = m - 1, p2 = n - 1, p = m + n - 1;
        while(p1 >= 0 && p2 >= 0) 
            nums1[p--] = (nums1[p1] > nums2[p2] ? nums1[p1--] : nums2[p2--]);
        //In the following expression, p2 + 1 should be calculated first, or when p2 == -1(n == 0), it'll cause runtime error 
        //since iterator can't minus an integer.
        copy(nums2.begin(),nums2.begin() + (p2 + 1),nums1.begin());  
        return;
    }
};
