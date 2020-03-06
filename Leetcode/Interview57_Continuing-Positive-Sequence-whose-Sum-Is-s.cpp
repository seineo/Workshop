/*
 *  problem: https://leetcode-cn.com/problems/he-wei-sde-lian-xu-zheng-shu-xu-lie-lcof/
 */

//Solution 1 (Brute-force)
//Time complexity: O(target * sqrt(target))
//Space complexity: O(1)   (Excluded the return array)

class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        vector<vector<int>> ret;
        vector<int> ans;
        int upper = target / 2;
        int sum = 0;
        for(int i = 1;i <= upper;++i) {
            for(int j = i;;++j) {
                sum += j;
                if(sum > target) {
                    sum = 0;
                    break;
                }
                else if(sum == target) {
                    for(int k = i;k <= j;++k) {
                        ans.push_back(k);
                    }
                    ret.push_back(ans);
                    ans.clear();
                    sum = 0;
                    break;
                }
            }
        }
        return ret;
    }
};

//Solution 2 (Optimized Brute-force)
//Time complexity: O(target)
//Space complexity: O(1)  (Excluded the return array)

class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        vector<vector<int>> ret;
        vector<int> ans;
        int limit = target / 2;
        for(int x = 1;x <= limit;++x) {
            long long delta = 1 - 4 * (x - 1ll * x * x - 2 * target);   //delta should use long long data type, or it may overflow
            if(delta < 0)
                continue;
            int sqrt_delta = sqrt(delta);
            if(1ll * sqrt_delta * sqrt_delta == delta && (sqrt_delta - 1) % 2 == 0) {
                int y = (sqrt_delta - 1 ) / 2;
                if(y > x) {
                    for(int i = x;i <= y;++i) {
                        ans.push_back(i);
                    }
                    ret.push_back(ans);
                    ans.clear();
                }
            }
        }
        return ret;
    }
};

//Solution 3 (Two Pointers) 
//Time complexity: O(target)
//Space complexity: O(1)    (Excluded the return array)

class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        vector<vector<int>> ret;
        vector<int> ans;
        int sum = 0;
        for(int left = 1, right = 2;left < right;) {
            sum = (right - left + 1) * (left + right) / 2;
            if(sum == target) {
                for(int i = left;i <= right;++i) {
                    ans.push_back(i);
                }
                ret.push_back(ans);
                ans.clear();
                left++;
            }
            else if(sum < target) {
                right++;
            }
            else {
                left++;
            }
        }    
        return ret;
    }
};
