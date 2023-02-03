//
// Created by james on 2023/2/3.
//

#ifndef CPLUS_DEMO_LINKEDLIST_H
#define CPLUS_DEMO_LINKEDLIST_H

#include <iostream>

typedef struct ListNode {
    ListNode *prev;
    ListNode *next;
    int value;
} ListNode;


class LinkedList {
public:
    void add2Tail(int val);

    void add2Head(int val);

    ListNode *findNode(int index);

    ListNode *searchKey(int key);

    void removeNode(int val);

    int length() {
        return this->len;
    }

    ListNode *getHead() {
        return this->head;
    }

    ListNode *getTail() {
        return this->tail;
    }

    LinkedList() {
        this->head = NULL;
        this->tail = NULL;
        this->len = 0;
    }

    ~LinkedList() {
        ListNode *cur = head;
        while (this->len--) {
            ListNode *next = cur->next;
            if (next == NULL)
                break;
            free(cur);
            cur = next;
        }
    }

private:
    ListNode *head;
    ListNode *tail;
    int len;
};


#endif //CPLUS_DEMO_LINKEDLIST_H
