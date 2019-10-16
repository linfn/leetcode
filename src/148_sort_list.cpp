
/*
Sort List

URL: https://leetcode.com/problems/sort-list
Tags: ['linked-list', 'sort']
___

Sort a linked list in O ( n log n ) time using constant space complexity.

Example 1:

    Input: 4- >2->1->3
    Output: 1- >2->3->4


Example 2:

    Input: -1- >5->3->4->0
    Output: -1- >0->3->4->5
*/

#include "test.h"

using namespace leetcode;
using std::tuple;

/*
    归并排序
*/
namespace sort_list {

inline namespace v1 {
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        int len = 0;
        for (auto i = head; i != nullptr; i = i->next) {
            len++;
        }

        ListNode ahead(0);
        ahead.next = head;
        for (int n = 1; n < len; n *= 2) {
            auto preTail = &ahead;
            while (preTail->next) {
                auto l1 = preTail->next;
                auto l2 = advance(l1, n);
                if (!l2) {
                    break;
                }
                auto [head, tail] = merge(l1, l2, n);
                preTail->next = head;
                preTail = tail;
            }
        }
        return ahead.next;
    }

private:
    ListNode* advance(ListNode* head, int n) {
        for (; n > 0 && head; n--) {
            head = head->next;
        }
        return head;
    }

    tuple<ListNode*, ListNode*> merge(ListNode* l1, ListNode* l2, int n) {
        int m = n;
        ListNode *i = l1, *j = l2, *jPre = nullptr, *head = l2;
        for (; n > 0; n--) {
            auto iNext = i->next;
            for (; m > 0 && j && (j->val < i->val); m--) {
                jPre = j;
                j = j->next;
            }
            if (jPre) {
                jPre->next = i;
            } else {
                head = i;
            }
            jPre = i;
            i->next = j;
            i = iNext;
        }
        for (; m > 0 && j; m--) {
            jPre = j;
            j = j->next;
        }
        return {head, jPre};
    }
};
} // namespace v1

TEST_CASE("Sort List") {
    TEST_SOLUTION(sortList, v1) {
        CHECK(listEqual(sortList(makeList({4, 2, 1, 3})),
                        makeList({1, 2, 3, 4})));
        CHECK(listEqual(sortList(makeList({-1, 5, 3, 4, 0})),
                        makeList({-1, 0, 3, 4, 5})));
        CHECK(listEqual(sortList(makeList({4, 3, 2, 1})),
                        makeList({1, 2, 3, 4})));
        CHECK(listEqual(sortList(makeList({})), makeList({})));
        CHECK(listEqual(sortList(makeList({1})), makeList({1})));
    };
}

} // namespace sort_list
