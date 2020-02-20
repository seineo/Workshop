/*
 *  problem: https://leetcode-cn.com/problems/merge-two-sorted-lists/
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

//Solution 1 (Iteration):
//Time complexity: O(n + m)    
//Space complexity: O(1)

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        /*if(l1 == nullptr && l2 == nullptr)
            return nullptr;
        if(l1 == nullptr ^ l2 == nullptr)
            return (l1 == nullptr ? l2 : l1); */
        if(l1 == nullptr)     //this is easier than that above
            return l2;
        else if(l2 == nullptr)
            return l1;
        ListNode* dummy = new ListNode(0);
        ListNode* p = dummy;
        while(l1 != nullptr && l2 != nullptr) {
            if(l1->val < l2->val) {
                p->next = l1;
                l1 = l1->next;
            } else {
                p->next = l2;
                l2 = l2->next;
            }
            p = p->next;
        }
        p->next = (l1 == nullptr ? l2 : l1);
        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
};

//Solution 2 (Recursion):
//Time complexity: O(n + m)
//Space complexity: O(n + m)

//We can get the following definition: 
//{list1[0]+merge(list1[1:],list2)   list1[0] < list2[0]
//list2[0]+merge(list1,list2[1:])    otherwise

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1 == nullptr)
            return l2;
        else if(l2 == nullptr)
            return l1;
        if(l1->val < l2->val) {
            l1->next = mergeTwoLists(l1->next,l2);
            return l1;
        } else {
            l2->next = mergeTwoLists(l1,l2->next);
            return l2;
        }
    }
};
