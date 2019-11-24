#ifndef LIST_HPP
#define LIST_HPP


class ListNode{
public:
    int value;

    ListNode *prev;
    ListNode *next;
    ListNode() {}
    ListNode(int val) : value(val), next(nullptr), prev(nullptr) {}
};
#endif