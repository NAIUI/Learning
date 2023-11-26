// Definition for singly-linked list.
// 反转链表
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

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