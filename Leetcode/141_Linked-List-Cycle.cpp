/*
 *  problem: https://leetcode-cn.com/problems/linked-list-cycle/
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

//Solution 1(not so good):
//Time complexity: O(n)
//Space complexity: O(n)

class Solution {
public:
    bool hasCycle(ListNode *head) {
        unordered_set<ListNode*> nodes;
        while(head != nullptr) {
            if(nodes.find(head) != nodes.end())
                return true;
            else
                nodes.insert(head);
            head = head->next;
        }
        return false;
    }
};

//Solution 2(good):
//Time complexity: O(n)
//Space complexity: O(1)

class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(head == nullptr || head->next == nullptr)
            return false;
        if(head->next == head)
            return true;
        ListNode* front = head->next;
        ListNode* back = head;
        while(front != back) {
            if(front->next == nullptr || front->next->next == nullptr)
                return false;
            front = front->next->next;
            back = back->next;
        }
        return true;
    }
};


