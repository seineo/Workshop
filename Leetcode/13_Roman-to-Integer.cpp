/*
*   problem: https://leetcode-cn.com/problems/roman-to-integer/
*/

//Solution 1 (not so good):
//I thought there were only six cases that the small can be placed before the large because of the translation

class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char,int> map{       //create a dictionary
            {'I',1},{'V',5},{'X',10},{'L',50},{'C',100},{'D',500},{'M',1000}
        };
        int result = 0;
        size_t len = s.size();
        for(size_t i = 0;i != len;++i) {   
            if(i != len - 1) {   //cover the special cases 
                if(s[i] == 'I' && (s[i + 1] == 'V' || s[i + 1] == 'X')) 
                    result += -1;
                else if(s[i] == 'X' && (s[i + 1] == 'L' || s[i + 1] == 'C')) 
                    result += -10;
                else if(s[i] == 'C' && (s[i + 1] == 'D' || s[i + 1] == 'M'))
                    result += -100;
                else 
                    result += map[s[i]];
            } else {
                result += map[s[i]];
            }
        }
        return result;
    }
};

//Solution 2 (good):

class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char,int> map{   //create a dictionary
            {'I',1},{'V',5},{'X',10},{'L',50},{'C',100},{'D',500},{'M',1000}
        };
        int result = 0;
        size_t len = s.size();
        for(size_t i = 0;i != len;++i) {
            if(i != len - 1) {   
                if(map[s[i]] >= map[s[i + 1]]) 
                    result += map[s[i]];
                else
                    result += -map[s[i]];
            } else {
                result += map[s[i]];
            }
        }
        return result;
    }
};
