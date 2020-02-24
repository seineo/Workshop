/*
 *  problem: https://leetcode-cn.com/problems/majority-element/
 */

//The majority element is the element that appears more than ⌊ n/2 ⌋ times.
//So we don't need iteration to find which element occurs most times.

//Solution 1(Hash Table):
//Time complexity: O(n)
//Space complexity: O(n)

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int,size_t> count;
        size_t size = nums.size();
        for(const int& i : nums) {
            count[i]++;
            if(count[i] > size / 2) {
                return i;
            }
        }
        return 0;
    }
};

//Solution 2(Sorting):
//Time complexity: O(nlogn)
//Space complexity: O(1)

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        return nums[nums.size() / 2];
    }
};

//Solution 3(Boyer-Moore Voting Algorithm):
//This algorithm is incredible. Here is the source website: http://www.cs.utexas.edu/~moore/best-ideas/mjrty/

//Time complexity: O(n)
//Space complexity: O(1)

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        size_t count = 0;
        int candidate = 0;
        for(const int& i : nums) {
            if(count == 0) 
                candidate = i;
            count += (i == candidate ? 1 : -1);
        }
        return candidate;
    }
};
