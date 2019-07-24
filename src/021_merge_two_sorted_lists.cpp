
/*
Merge Two Sorted Lists

URL: https://leetcode.com/problems/merge-two-sorted-lists
Tags: ['linked-list']
___

Merge two sorted linked lists and return it as a new list. The new list should
be made by splicing together the nodes of the first two lists.

Example:

    Input: 1->2->4, 1->3->4
    Output: 1->1->2->3->4->4
*/

#include "test.h"

namespace merge_two_sorted_lists {

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

inline namespace v1 {
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode result{0};
        ListNode* cur = &result;
        while (l1 || l2) {
            if (!l1) {
                cur->next = l2;
                l2 = l2->next;
            } else if (!l2) {
                cur->next = l1;
                l1 = l1->next;
            } else {
                if (l1->val < l2->val) {
                    cur->next = l1;
                    l1 = l1->next;
                } else {
                    cur->next = l2;
                    l2 = l2->next;
                }
            }
            cur = cur->next;
        }
        return result.next;
    }
};
} // namespace v1

USING_MAKE_LIST;

TEST_CASE("Merge Two Sorted Lists") {
    TEST_SOLUTION(mergeTwoLists, v1) {

        CHECK(listEqual(mergeTwoLists(makeList({1, 2, 4}), makeList({1, 3, 4})),
                        makeList({1, 1, 2, 3, 4, 4})));

        BENCHMARK("") {
            auto l1 = makeList({1, 2, 4});
            auto l2 = makeList({1, 3, 4});
            auto result = mergeTwoLists(l1, l2);
            freeList(result);
        };
    };
}

} // namespace merge_two_sorted_lists
