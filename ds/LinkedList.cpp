//
// Created by james on 2023/2/3.
//

#include "LinkedList.h"

void LinkedList::add2Head(int val) {
    ListNode *listNode;
    ListNode *node = (ListNode *) malloc(sizeof(*listNode));
    node->value = val;
    if (this->len == 0) {
        this->head = this->tail = node;
        node->prev = NULL;
        node->next = NULL;
        this->len++;
        return;
    }

    node->next = this->head;
    this->head->prev = node;
    node->prev = NULL;
    this->head = node;
    this->len++;
}

void LinkedList::add2Tail(int val) {
    ListNode *listNode;
    ListNode *node = (ListNode *) malloc(sizeof(*listNode));
    node->value = val;
    if (this->len == 0) {
        this->head = this->tail = node;
        node->prev = NULL;
        node->next = NULL;
        this->len++;
        return;
    }

    node->prev = this->tail;
    node->next = NULL;
    this->tail->next = node;
    this->tail = node;
    this->len++;
}

ListNode *LinkedList::findNode(int index) {
    if (this->head == NULL) {
        return NULL;
    }

    ListNode *cur = head;
    int i = 0;

    while (cur != NULL && i <= index) {
        if (i == index) {
            return cur;
        }
        cur = cur->next;
        i++;
    }
    return NULL;
}

ListNode *LinkedList::searchKey(int key) {
    if (this->len == 0) {
        return NULL;
    }

    ListNode *cur = head;
    int len = this->len;
    while (len--) {
        if (cur->value == key) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

void LinkedList::removeNode(int val) {
    if (this->len == 0) {
        return;
    }

    ListNode *cur = head;
    int len = this->len;
    while (len--) {
        if (cur->value == val) {
            if (cur->prev != NULL) {
                cur->prev->next = cur->next;
            }

            if (cur->next != NULL) {
                cur->next->prev = cur->prev;
            }

            free(cur);
            this->len--;
            if (this->len == 0) {
                this->head = NULL;
                this->tail = NULL;
            }
            break;
        }
        cur = cur->next;
    }

    return;
}

