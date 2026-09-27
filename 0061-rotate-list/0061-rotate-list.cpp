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
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head) return head;
        int n = 0;
        ListNode* temp = head;
        while (temp) {
            n++;
            temp = temp->next;
        }
        k %= n;
        if (k == 0) return head;
        temp = head;
        for (int i = 0; i < n - k - 1; ++i) {
            temp = temp->next;
        }
        ListNode* new_head = temp->next;
        temp->next = nullptr;
        temp = new_head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = head;
        return new_head;
    }
};