// Definition for singly-linked list.
// 合并有序链表
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) return l2;
        if (l2 == nullptr) return l1;
        ListNode head(0);
        ListNode* node = &head;
        while (l1 != nullptr && l2 != nullptr)
        {
            if (l1->val < l2->val)
            {
                node->next = l1;
                l1 = l1->next;
            }
            else
            {
                node->next = l2;
                l2 = l2->next;
            }
            node = node->next;
        }
        if (l1 != nullptr) node->next = l1;
        if (l2 != nullptr) node->next = l2;
        return head.next;
    }
};