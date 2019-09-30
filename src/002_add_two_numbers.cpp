/*
Add Two Numbers

URL: https://leetcode.com/problems/add-two-numbers
Tags: ['linked-list', 'math']
___

You are given two non-empty linked lists representing two non-negative
integers. The digits are stored in reverse order and each of their nodes
contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the
number 0 itself.

Example:

    Input: (2 - > 4 -> 3) + (5 -> 6 -> 4)
    Output: 7 - > 0 -> 8
    Explanation: 342 + 465 = 807.
*/

#include "test.h"

namespace add_two_numbers {

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

inline namespace v1 {
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head = nullptr;
        ListNode* cur = nullptr;
        auto ex = 0;
        // 这里用 for 相比用 while 的形式在 leetcode 上要快许多
        for (; l1 || l2 || ex != 0;
             l1 = l1 ? l1->next : nullptr, l2 = l2 ? l2->next : nullptr) {
            auto v = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + ex;
            ex = 0;
            if (v >= 10) {
                v -= 10;
                ex = 1;
            }
            auto node = new ListNode(v);
            if (cur) {
                cur->next = node;
            } else {
                head = node;
            }
            cur = node;
        }
        return head;
    }
};
} // namespace v1

USING_MAKE_LIST;

TEST_CASE("Add Two Numbers") {
    using std::vector;

    TEST_SOLUTION(addTwoNumbers, v1) {
        auto l1 = makeList({1, 2, 3});
        auto l2 = makeList({7, 8, 9});

        auto r = addTwoNumbers(l1, l2);

        vector<int> v;
        for (; r; r = r->next) {
            v.push_back(r->val);
        }
        CHECK(v == vector<int>{8, 0, 3, 1});

        BENCHMARK("") { return addTwoNumbers(l1, l2); };
    };
}

} // namespace add_two_numbers
