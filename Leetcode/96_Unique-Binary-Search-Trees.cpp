/*
 *  problem: https://leetcode-cn.com/problems/unique-binary-search-trees/
 */

//Solution 1 (DP):
//Time complexity: O(N ^ 2)
//Space complexity: O(N)

class Solution {
public:
    int numTrees(int n) {
        vector<int> num(n + 1);
        num[0] = 1;
        num[1] = 1;
        for(int i = 2;i <= n;++i) {
            for(int j = 1;j <= i;++j) {
                num[i] += num[j - 1] * num[i - j];
            }
        }
        return num[n];
    }
};

//Solution 2 (Catalan number):
//Time complexity: O(N)
//Space complexity: O(1)

class Solution {
public:
    int numTrees(int n) {
        long num = 1;  //Use long data type or it may overflow
        for(int i = 0;i != n;++i) {
            num = num * 2 * (2 * i + 1) / (i + 2);
        }
        return static_cast<int>(num);
    }
};
