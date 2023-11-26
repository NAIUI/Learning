// 链表有环判断
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* low = head;
        ListNode* high = head;
        if (low == nullptr || high == nullptr) return false;
        while (low && high) {
            if (high->next == nullptr) return false;
            low = low->next;
            high = high->next->next;
            if (low == high) return true;
        }
        return false;
    }
};