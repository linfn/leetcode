
/*
Remove Nth Node From End of List

URL: https://leetcode.com/problems/remove-nth-node-from-end-of-list
Tags: ['linked-list', 'two-pointers']
___

Given a linked list, remove the n -th node from the end of list and return its
head.

Example:

    Given linked list: 1- >2->3->4->5, and n = 2.

    After removing the second node from the end, the linked list becomes 1-
>2->3->5.


Note:

Given n will always be valid.

Follow up:

Could you do this in one pass?
*/

#include <deque>

#include "test.h"

using namespace leetcode;
using std::deque;

namespace remove_nth_node_from_end_of_list {

namespace v1 {
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        deque<ListNode*> v(n + 1, nullptr);
        for (auto cur = head; cur; cur = cur->next) {
            v.pop_front();
            v.push_back(cur);
        }
        auto r = v[1];
        if (r == head) {
            return head->next;
        }
        v.front()->next = r->next;
        return head;
    }
};
} // namespace v1

inline namespace v2 {
/*
先往前走 n 步, 那我可以获得一段 n 步长的距离(从 head 到 cur),
然后跟踪这段距离继续走到底, 就得到了倒数 nth.
*/
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* cur = head;
        for (int i = 0; i < n; i++) {
            cur = cur->next;
        }
        ListNode *node1 = nullptr, *node2 = head;
        for (; cur; cur = cur->next) {
            node1 = node2;
            node2 = node2->next;
        }
        if (!node1) {
            return head->next;
        }
        node1->next = node2->next;
        return head;
    }
};
} // namespace v2

TEST_CASE("Remove Nth Node From End of List") {
    TEST_SOLUTION(removeNthFromEnd, v1, v2) {
        CHECK(listEqual(removeNthFromEnd(makeList({1, 2, 3, 4, 5}), 2),
                        makeList({1, 2, 3, 5})));

        BENCHMARK(""){};
    };
}

} // namespace remove_nth_node_from_end_of_list
