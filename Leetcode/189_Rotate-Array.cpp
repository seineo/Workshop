/*
 *  problem: https://leetcode-cn.com/problems/rotate-array/
 */

//Solution 1(not so good):
//Time complexity: O(n)
//Space complexity: O(k % n)

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if(nums.size() <= 1)
            return;
        int size = nums.size();
        k %= size;
        vector<int> temp(nums.end() - k,nums.end());
        int count = size - k;
        copy_backward(nums.begin(),nums.begin() + count,nums.end());
        copy(temp.begin(),temp.end(),nums.begin());
    }
};

//Solution 2(good):
//Time complexity: O(n)
//Space complexity: O(1)

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if(nums.size() <= 1)
            return;
        k %= nums.size();
        reverse(nums.begin(),nums.end());
        reverse(nums.begin(),nums.begin() + k);
        reverse(nums.begin() + k,nums.end());
    }
};

//Solution 3(good):
//Time complexity: O(n)
//Space complexity: O(1)

//Cyclic Replacements
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if(nums.size() <= 1)
            return;
        int count = 0;  //Represent the number of moved elements
        int size = nums.size();
        k %= size;
        for(int start = 0;count != size;++start) {
           int cur = start;
           int cur_val = nums[cur];
           do {
               int next = (cur + k) % size;
               int next_val = nums[next];
               nums[next] = cur_val;
               cur = next;
               cur_val = next_val;
               count++;
           } while(cur != start);
        }
    }
};

