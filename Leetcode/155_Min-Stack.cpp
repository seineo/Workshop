/*
 *  problem: https://leetcode-cn.com/problems/min-stack/
 */

//Solution 1(using two stacks):

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {

    }

    void push(int x) {
        if(min.empty() || x <= min.top()) {  //note that x also need be pushed when x is equal to  min
            min.push(x);
        }
        normal.push(x);
    }

    void pop() {
        if(normal.top() == min.top())
            min.pop();
        normal.pop();
    }

    int top() {
        return normal.top();
    }

    int getMin() {
        return min.top();
    }
private:
    stack<int> normal;
    stack<int> min;
};

//Solution 2(using one stack):

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        min = INT_MAX;
    }
    
    void push(int x) {
       if(x <= min) {    //if x <= min, we push min first and then update min
           s.push(min);
           min = x;
       } 
       s.push(x);
    }
    
    void pop() {
        if(s.top() == min) {  //if we pop min, we need pop twice and update min
            s.pop();
            min = s.top();
        }
        s.pop();
    }
    
    int top() {
        return s.top();
    }
    
    int getMin() {
        return min;
    }
private:
    stack<int> s;
    int min;
};

//Solution 3(using one stack):

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {

    }

    void push(int x) {
        if(s.empty()) {
            s.push(0);
            min = x;
        } else {
            s.push(x - min);  //it can be negative
            if(x < min)   //if x < min, we need update min
                min = x;
        }
    }

    void pop() {
        if(s.top() < 0) {  //s.top() < 0 means we are going to pop the current min value and we need replace it with old min value
            min = min - s.top();
        }
        s.pop();
    }

    int top() {
        return (s.top() < 0 ? static_cast<int>(min) : static_cast<int>(min + s.top()));
    }

    int getMin() {
        return static_cast<int>(min);
    }
private:
    //We use long data type here since we store the gap between the min value and the current value, and it may overflow
    stack<long> s;
    long min;
};
