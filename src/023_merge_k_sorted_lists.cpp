
/*
Merge k Sorted Lists

URL: https://leetcode.com/problems/merge-k-sorted-lists
Tags: ['linked-list', 'divide-and-conquer', 'heap']
___

Merge k sorted linked lists and return it as one sorted list. Analyze and
describe its complexity.

Example:

    Input:
    [
       1->4->5,
      1->3->4,
      2->6
    ]
    Output: 1- >1->2->3->4->4->5->6
*/

#include "test.h"

using namespace leetcode;
using std::remove;
using std::vector;

namespace merge_k_sorted_lists {

/*
    主要思路就是每一次都取剩余链表中头中小的那一个.
*/
namespace v1 {

class Solution {

public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode result(0);
        ListNode* cur = &result;

        lists.erase(remove(lists.begin(), lists.end(), nullptr), lists.end());

        while (!lists.empty()) {
            vector<ListNode*>::iterator min = lists.end();
            for (auto i = lists.begin(); i != lists.end(); i++) {
                if (min == lists.end() || (*i)->val <= (*min)->val) {
                    min = i;
                }
            }
            cur->next = *min;
            cur = *min;
            if ((*min)->next != nullptr) {
                *min = (*min)->next;
            } else {
                lists.erase(min);
            }
        }
        return result.next;
    }
};
} // namespace v1

/*
    使用最小堆优化 v1
*/
inline namespace v2 {

using std::make_heap;
using std::pop_heap;
using std::push_heap;

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode result(0);
        ListNode* cur = &result;

        lists.erase(remove(lists.begin(), lists.end(), nullptr), lists.end());

        // 使用 greater 比较函数构造最小堆 (less 用于构造最大堆)
        auto compare = [](ListNode* lhs, ListNode* rhs) -> bool {
            return lhs->val > rhs->val;
        };

        make_heap(lists.begin(), lists.end(), compare);
        while (!lists.empty()) {
            pop_heap(lists.begin(), lists.end(), compare);
            auto l = lists.back();
            cur->next = l;
            cur = l;
            if (l->next) {
                lists.back() = l->next;
                push_heap(lists.begin(), lists.end(), compare);
            } else {
                lists.pop_back();
            }
        }

        return result.next;
    }
};
} // namespace v2

// TODO 还可以使用分治的方式, 时间复杂度和 v2 相同, 均为 O(N*logk)

TEST_CASE("Merge k Sorted Lists") {
    TEST_SOLUTION(mergeKLists, v1, v2) {
        vector<ListNode*> v = {makeList({1, 4, 5}), makeList({1, 3, 4}),
                               makeList({2, 6})};
        CHECK(listEqual(mergeKLists(v), makeList({1, 1, 2, 3, 4, 4, 5, 6})));

        v = {nullptr};
        CHECK(listEqual(mergeKLists(v), nullptr));

        BENCHMARK("") {
            vector<ListNode*> v = {makeList({1, 4, 5}), makeList({1, 3, 4}),
                                   makeList({2, 6}),
                                   makeList({1, 2, 3, 4, 5, 6, 7, 9}),
                                   makeList({1, 2, 3, 4, 5, 6, 7, 8, 10})};
            return mergeKLists(v);
        };
    };
}

} // namespace merge_k_sorted_lists
