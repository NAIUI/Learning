//https://leetcode.cn/problems/c32eOV/description/
// 链表入环点问题
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* low = head;
        ListNode* high = head;
        ListNode* ptr = head;
        if (low == nullptr || high == nullptr) return nullptr;
        while (low && high) {
            if (high->next == nullptr) return nullptr;
            low = low->next;
            high = high->next->next;
            if (low == high) break;
        }
        if (low == high){
            while (ptr != low){
                ptr = ptr->next;
                low = low->next;
            }
            return ptr;
        }
        return nullptr;
    }
};