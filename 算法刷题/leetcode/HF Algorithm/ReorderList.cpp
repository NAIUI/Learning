// 重排链表

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* pre = nullptr;
        if(!head) return head;
        ListNode* index = head, *ord = index->next;
        while(index) {
            index->next = pre;
            pre = index;
            index = ord;
            if(ord) ord = ord->next;
        } 
        return pre;
    }

    ListNode* mergeList(ListNode* l1, ListNode* l2) {
        if(l1 == nullptr) return l2;
        if(l2 == nullptr) return l1;
        ListNode head(0);
        ListNode* node = &head;
        while(l1 != nullptr && l2 != nullptr){
            node->next = l1;
            l1 = l1->next;
            node = node->next;
            node->next = l2;
            l2 = l2->next;
            node = node->next;
        }
        if (l1 != nullptr) node->next = l1;
        if (l2 != nullptr) node->next = l2;
        return head.next;
    }

    void reorderList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return;
        ListNode* slow = head, * fast = head->next;
	    while (fast != nullptr && fast->next != nullptr) {
		    slow = slow->next;
		    fast = fast->next->next;
	    }
	    ListNode* second = slow->next;
	    slow->next = nullptr;
	    second = reverseList(second);
	    head = mergeList(head, second);
    }
};