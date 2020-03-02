/*
 *  problem: https://leetcode-cn.com/problems/reverse-linked-list/
 */

//Solution (Two Pointers):
//Time complexity: O(n)
//Space complexity: O(1)

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* beg = nullptr;
        ListNode* end = head;
        while(end != nullptr) {
            ListNode* next_node = end->next;
            end->next = beg;
            beg = end;
            end = next_node;
        }
        return beg;
    }
};
