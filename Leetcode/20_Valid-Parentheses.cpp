/*
 *  problem: https://leetcode-cn.com/problems/valid-parentheses/
 */

//Solution 1 (not so good):
//Code duplicates

class Solution {
public:
    bool isValid(string s) {
       stack<char> temp;   //Store opening brackets
        size_t len = s.size();
        for(size_t i = 0;i != len;++i) {
            switch(s[i]) {
                case '(':
                case '[':
                case '{':    //Push opening brackets
                    temp.push(s[i]);
                    break;
                case ')':            //Deal with closing brackets separately
                    if(!temp.empty() && temp.top() == '(') {
                        temp.pop();
                        break;
                    } else {
                        return false;
                    }
                case ']':
                    if(!temp.empty() && temp.top() == '[') {
                        temp.pop();
                        break;
                    } else {
                        return false;
                    }
                case '}':
                    if(!temp.empty() && temp.top() == '{') {
                        temp.pop();
                        break;
                    } else {
                        return false;
                    }
            }
        }
        return temp.empty();    //At last, the stack should be empty
    }
};

//Solution 2 (good):
//Use hash table to take care of the mappings and make the code easier to read

class Solution {
public:
    bool isValid(string s) {
       stack<char> temp;   //Store opening brackets
        size_t len = s.size();
        for(size_t i = 0;i != len;++i) {
            char ch = s[i];
            if(map.find(ch) != map.end()) {  //If current character is a closing bracket
                if(!temp.empty() && temp.top() == map[ch]) {
                    temp.pop();
                } else {
                    return false;
                }
            } else {   //If it's a opening brackets, push it to the stack
                temp.push(ch);
            }
        }
        return temp.empty();    //At last, the stack should be empty
    }
private:
    unordered_map<char,char> map {   //Just make the code easier to read
        {')','('}, {']','['},{'}','{'}
    };
};
