#include "ListNode.h"
ListNode* ListNode::addTwoNumbers(ListNode* l1, ListNode* l2)
{
    return dfs(l1, l2, 0);

}
ListNode* dfs(ListNode* l1, ListNode* l2, int i) {
    if (l1 == nullptr && l2 == nullptr && i == 0) {
        return nullptr;
    }
    int sum = (l1 == nullptr ? 0 : l1->val) + (l2 == nullptr ? 0 : l2->val) + i;
    ListNode* number = new ListNode(sum % 10);
    number->next = dfs(l1 == nullptr ? nullptr : l1->next, l2 == nullptr ? nullptr : l2->next, sum / 10);
    return number;
}


