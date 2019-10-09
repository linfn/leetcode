
/*
Linked List Cycle

URL: https://leetcode.com/problems/linked-list-cycle
Tags: ['linked-list', 'two-pointers']
___

Given a linked list, determine if it has a cycle in it.

To represent a cycle in the given linked list, we use an integer `pos` which
represents the position (0-indexed) in the linked list where tail connects to.
If `pos` is `-1`, then there is no cycle in the linked list.



Example 1:

    Input: head = [3,2,0,-4], pos = 1
    Output: true
    Explanation: There is a cycle in the linked list, where tail connects to the
second node.


![](https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist.png)

Example 2:

    Input: head = [1,2], pos = 0
    Output: true
    Explanation: There is a cycle in the linked list, where tail connects to the
first node.


![](https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist_test2.png)

Example 3:

    Input: head = [1], pos = -1
    Output: false
    Explanation: There is no cycle in the linked list.


![](https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist_test3.png)



Follow up:

Can you solve it using O(1) (i.e. constant) memory?
*/

#include <unordered_map>
#include "test.h"

using namespace leetcode;

namespace linked_list_cycle {

namespace v1 {

using std::unordered_map;

class Solution {
public:
    bool hasCycle(ListNode* head) {
        unordered_map<ListNode*, bool> record;
        while (head) {
            if (record[head]) {
                return true;
            }
            record[head] = true;
            head = head->next;
        }
        return false;
    }
};
} // namespace v1

/*
    two-pointers, 快指针追慢指针
*/
inline namespace v2 {
class Solution {
public:
    bool hasCycle(ListNode* head) {
        if (!head || !head->next) {
            return false;
        }
        auto slow = head;
        auto fast = head->next;
        while (slow != fast) {
            if (fast->next && fast->next->next) {
                fast = fast->next->next;
            } else {
                return false;
            }
            slow = slow->next;
        }
        return true;
    }
};
} // namespace v2

TEST_CASE("Linked List Cycle") {
    TEST_SOLUTION(hasCycle, v1, v2) {
        ListNode n1(3);
        ListNode n2(2);
        ListNode n3(0);
        ListNode n4(-4);
        n1.next = &n2;
        n2.next = &n3;
        n3.next = &n4;

        CHECK_FALSE(hasCycle(&n1));

        n4.next = &n1;
        CHECK(hasCycle(&n1));

        BENCHMARK("") { return hasCycle(&n1); };
    };
}

} // namespace linked_list_cycle
