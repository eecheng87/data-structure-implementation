// first method, worst beat 12% c++ code
// waste more space
// cost 12ms
ListNode *reverseList(ListNode *head)
{
    if (head == NULL)
        return NULL;
    if (head->next == NULL)
        return head;
    ListNode *new_head = NULL;
    ListNode *flag = head;
    ListNode *tmp;

    while (flag != NULL)
    {
        tmp = (ListNode *)malloc(sizeof(ListNode));
        tmp->val = flag->val;
        tmp->next = new_head;
        new_head = tmp;
        flag = flag->next;
    }
    return new_head;
}

// second method , without use waste memory
// beat 100% c++ code
// cost 4ms
ListNode *reverseList(ListNode *head)
{
    ListNode *prev = NULL;
    ListNode *curr = head;
    while (curr != NULL)
    {
        ListNode *nextTmp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextTmp;
    }
    return prev;
}

// third method, use recursive
// bead 100% c++ code
// cost 4 ms
ListNode *reverseList(ListNode *head)
{
    if (head == NULL || head->next == NULL)
        return head;
    ListNode *p = reverseList(head->next);
    head->next->next = head;
    head->next = NULL;
    return p;
}