#include "ListNode.h"
ListNode* ListNode::addTwoNumbers(ListNode* l1, ListNode* l2)
{
    ListNode* r = new ListNode();
    ListNode* ans = new ListNode(0, r);
    int flag = 0;
    while (l1 != nullptr || l2 != nullptr) {
        l1->val = l1 == nullptr ? 0 : l1->val;
        l2->val = l2 == nullptr ? 0 : l2->val;
        ListNode* number = new ListNode();
        number->val = (l1->val + l2->val + flag) % 10;
        flag = (l1->val + l2->val + flag - 10) >= 0 ? 1 : 0;
        if (l1!= nullptr) {
            l1 = l1->next;
        }
        if (l2 != nullptr) {
            l2 = l2->next;
        }
        r->next = number;
        r = number;
    }
    if (flag != 0) {
        ListNode* number = new ListNode(1);
        r->next = number;
        r = number;
    }

    return ans->next->next;

}

