#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

#include "model/Student.h"
#include "ds/LinkedList.h"
#include "net/TcpServer.h"

void testDs();

void testList();

void testClass();

void testAlg();

using namespace std;

int binarySearch(int arr[], int target, int start, int end) {
    if (arr == NULL)
        return -1;
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] > target) {
            end = mid;
        } else {
            start = mid;
        }
    }
    return -1;
}

int main() {
    std::cout << "Hello, cplusplus demo for test!" <<
              std::endl;

//    testDs();
//    testClass();
//    testAlg();
//    testList();

    TcpServer server(9090);
    server.start();


    return 0;
}

void testAlg() {
    cout << "-------------------" << endl;
    int testArr[]{1, 2, 3, 4, 5, 6, 7, 8, 9};
    int index = binarySearch(testArr, 3, 0, sizeof(testArr) / sizeof(testArr[0]));
    cout << index << endl;
}

void testClass() {
    Student stu(10, 10, 1);
    cout << stu.getSalary() << endl;
}

void testList() {
    std::cout << "-------test linked list ----" << std::endl;
    LinkedList list;
    for (int i = 10; i < 15; i++) {
        list.add2Tail(i);
    }

    for (int i = 5; i < 10; i++) {
        list.add2Head(i);
    }

    for (int i = 0; i < list.length(); i++) {
        ListNode *target = list.findNode(i);
        cout << target->value << endl;
    }

    ListNode *target = list.searchKey(8);
    cout << target->value << endl;


    list.removeNode(8);
    target = list.searchKey(8);
    if (target == NULL) {
        cout << "remove node success!" << endl;
    } else {
        cout << "fail to remove the node." << endl;
    }
}

void testDs() {
    vector<int> testVector(1, 9);
    stack<int> testStack;
    for (int i = 0; i < 10; i++) {
        testStack.push(i);
    }

    while (!testStack.empty()) {
        int element = testStack.top();
        cout << element << endl;
        testStack.pop();
    }

    queue<int> testQueue;

    for (int i = 5; i >= 0; i--) {
        testQueue.push(i);
    }

    while (!testQueue.empty()) {
        cout << testQueue.front() << endl;
        testQueue.pop();
    }
}
