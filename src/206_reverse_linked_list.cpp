
/*
Reverse Linked List

URL: https://leetcode.com/problems/reverse-linked-list
Tags: ['linked-list']
___

Reverse a singly linked list.

Example:

    Input: 1- >2->3->4->5->NULL
    Output: 5- >4->3->2->1->NULL


Follow up:

A linked list can be reversed either iteratively or recursively. Could you
implement both?
*/

#include "test.h"

using namespace leetcode;

namespace reverse_linked_list {

inline namespace v1 {
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* pre = nullptr;
        while (head) {
            auto next = head->next;
            head->next = pre;
            pre = head;
            head = next;
        }
        return pre;
    }
};
} // namespace v1

namespace v2 {
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }
        auto result = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return result;
    }
};
} // namespace v2

TEST_CASE("Reverse Linked List") {
    TEST_SOLUTION(reverseList, v1, v2) {
        CHECK(listEqual(reverseList(makeList({1, 2, 3, 4, 5})),
                        makeList({5, 4, 3, 2, 1})));
    };
}

} // namespace reverse_linked_list
