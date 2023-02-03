#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

#include "Student.h"
#include "LinkedList.h"

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
    std::vector<int> testVector(1, 9);
    std::stack<int> testStack;
    for (int i = 0; i < 10; i++) {
        testStack.push(i);
    }

    while (!testStack.empty()) {
        int element = testStack.top();
        std::cout << element << std::endl;
        testStack.pop();
    }

    std::queue<int> testQueue;

    for (int i = 5; i >= 0; i--) {
        testQueue.push(i);
    }

    while (!testQueue.empty()) {
        std::cout << testQueue.front() << endl;
        testQueue.pop();
    }

    Student stu(10, 10, 1);
    std::cout << stu.getsalary() << std::endl;

    std::cout << "-------------------" << std::endl;
    int testArr[]{1, 2, 3, 4, 5, 6, 7, 8, 9};
    int index = binarySearch(testArr, 3, 0, sizeof(testArr) / sizeof(testArr[0]));
    std::cout << index << endl;

    std::cout << "Hello, World!" <<
              std::endl;

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
        std::cout << target->value << std::endl;
    }

    ListNode *target = list.searchKey(8);
    std::cout << target->value << endl;


    list.removeNode(8);
    target = list.searchKey(8);
    if (target == NULL) {
        std::cout << "remove node success!" << endl;
    } else {
        std::cout << "fail to remove the node." << endl;
    }

    return 0;
}
