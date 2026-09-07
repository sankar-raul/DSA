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
class Solution {
public:
    void add(ListNode* l1, ListNode* l2, int rem, ListNode* ans) {
        if (!l1 && !l2) {
            if (rem) {
                ans->next = new ListNode(rem);
            }
            return;
        };
        if (!l1) {
            int res;
            while (l2) {
                res = l2->val + rem;
                ans->next = new ListNode(res % 10);
                ans = ans->next;
                rem = res / 10;
                l2 = l2->next;
            }
            if (rem) {
                ans->next = new ListNode(rem);
            }
            return;
        }
        if (!l2) {
            int res;
            while (l1) {
                res = l1->val + rem;
                ans->next = new ListNode(res % 10);
                ans = ans->next;
                rem = res / 10;
                l1 = l1->next;
            }
            if (rem) {
                ans->next = new ListNode(rem);
            }
            return;
        }
        int res = l1->val + l2->val + rem;
        ans->next = new ListNode(res % 10);
        add(l1->next, l2->next, res / 10, ans->next);
    }
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int res = l1->val + l2->val;
        ListNode* ans = new ListNode(res % 10);
        res /= 10;
        add(l1->next, l2->next, res, ans);
        return ans;
    }
};