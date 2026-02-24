/*
    Difficulty: Hard
    Source: https://leetcode.com/problems/merge-k-sorted-lists/
*/

#include <vector>

using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (list1 == nullptr && list2 == nullptr)
            return nullptr;
        if (list1 == nullptr)
            return list2;
        if (list2 == nullptr)
            return list1;

        ListNode* p1 = list1;
        ListNode* p2 = list2;
        ListNode* head;

        if (p1->val < p2->val) {
            head = p1;
            p1 = p1->next;
        } else {
            head = p2;
            p2 = p2->next;
        }
        
        ListNode* cur = head;
        while (p1 != nullptr && p2 != nullptr) {
            if (p1->val < p2->val) {
                cur->next = p1;
                cur = p1;
                p1 = p1->next;
            } else {
                cur->next = p2;
                cur = p2;
                p2 = p2->next;
            }
        }

        if (p1 == nullptr) {
            cur->next = p2;
        }
        if (p2 == nullptr) {
            cur->next = p1;
        }

        return head;
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int n = lists.size();
        if (n == 0)
            return nullptr;
        
        while (n > 1) {
            for (int i = 0; i < n / 2; i++) {
                lists[i] = mergeTwoLists(lists[i], lists[n - i - 1]);
            }
            n = (n + 1) / 2;
        }

        return lists.front();
    }
};