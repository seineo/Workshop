/*
 *  problem: https://leetcode-cn.com/problems/implement-stack-using-queues/
 */

//Solution (using one queue):

class MyStack {
public:
    /** Initialize your data structure here. */
    MyStack() {

    }
    
    /** Push element x onto stack. */
    void push(int x) {
        q.push(x);
        s_top = x;
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int temp = s_top;
        while(q.front() != temp) {
            s_top = q.front();
            q.push(q.front());
            q.pop();
        }
        q.pop();
        return temp;
    }
    
    /** Get the top element. */
    int top() {
        return s_top;
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return q.empty();     
    }
private: 
    queue<int> q;
    int s_top;
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
