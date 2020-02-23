/*
 *  problem:  https://leetcode-cn.com/problems/intersection-of-two-linked-lists/
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

//Solution 1 (not so good):
//Time complexity: O(m + n)
//Space complexity: O(m) or O(n)

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA == nullptr || headB == nullptr)
            return nullptr;
        unordered_set<ListNode*> nodes;
        while(headA != nullptr) {
            nodes.insert(headA);
            headA = headA->next;
        }
        while(headB != nullptr) {
            if(nodes.find(headB) != nodes.end()) {
                return headB;
            }
            headB = headB->next;
        }
        return nullptr;
    }
};

//Solution 2 (good):
//Time complexity: O(m + n)
//Space complexity: O(1)

//Idea: A_left + A_intersection + B_left = B_left + B_intersection + A_left
//A_intersection = B_intersection

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA == nullptr || headB == nullptr)
            return nullptr;
        ListNode* pA = headA;
        ListNode* pB = headB;
        while(pA != pB) {
            pA = (pA == nullptr ? headB : pA->next);
            pB = (pB == nullptr ? headA : pB->next);
        }
        return pA;
    }
};
