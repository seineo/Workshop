/*
 *  problem: https://leetcode-cn.com/problems/distribute-candies-to-people/
 */

//Solution 1 (Brute-Force):
//Time complexity: O(sqrt(candies)})
//Space complexity: O(num_people)

class Solution {
public:
    vector<int> distributeCandies(int candies, int num_people) {
        int i = 0;
        vector<int> row(num_people);
        while(candies > 0) {
            int distribute = min(i + 1, candies);
            row[i++ % num_people] += distribute; 
            candies -= distribute;
        }
        return row;
    }
};

//Solution 2 (Math)
//Time complexity: O(num_people)
//Space complexity: O(num_people)

//Reference : https://leetcode-cn.com/problems/distribute-candies-to-people/solution/xiang-xi-jie-shi-shu-xue-fang-fa-zen-yao-zuo-gao-z/

class Solution {
public:
    vector<int> distributeCandies(int candies, int num_people) {
        vector<int> v(num_people);
        int p = static_cast<int>(sqrt(2 * candies + 0.25) - 0.5);
        int remaining = candies - p * (p + 1) / 2;
        int row = p / num_people;
        int col = p % num_people;
        for(int i = 0;i != num_people;++i) {
            v[i] += row * (i + 1) + row * (row - 1) / 2 * num_people;
            if(i < col)
                v[i] += i + 1 + row * num_people;
        }
        v[col] += remaining;
        return v;
    }
};
