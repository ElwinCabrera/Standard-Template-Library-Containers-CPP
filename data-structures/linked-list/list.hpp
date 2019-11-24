#ifndef LIST_HPP
#define LIST_HPP

#include "../global.hpp"


class ListNode{
public:
    int value;

    ListNode *prev;
    ListNode *next;
    ListNode() {}
    ListNode(int val) : value(val), next(nullptr), prev(nullptr) {}
};

class LinkedList{
private:
    ListNode *head;
public:
    LinkedList();
    LinkedList(vector<int> nums);
    ~LinkedList();

    ListNode *buildList(vector<int> nums);
    

    ListNode* insert_back(int num);
    ListNode* insert_front(int num);
    void remove(ListNode *node);

    ListNode* getHead() {return head;}
    
    void printList(); 

};


#endif