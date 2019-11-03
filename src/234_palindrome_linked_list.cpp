
/*
Palindrome Linked List

URL: https://leetcode.com/problems/palindrome-linked-list
Tags: ['linked-list', 'two-pointers']
___

Given a singly linked list, determine if it is a palindrome.

Example 1:

    Input: 1- >2
    Output: false

Example 2:

    Input: 1- >2->2->1
    Output: true

Follow up:
Could you do it in O(n) time and O(1) space?
*/

#include "test.h"

using namespace leetcode;

namespace palindrome_linked_list {

/*
    通过快慢指针, 找到链表的中间位置后, 反转后半链表, 与前半段比较
*/
inline namespace v1 {
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode* slow = &dummy, *fast = &dummy;
        while (fast->next) {
            if (fast->next->next) {
                fast = fast->next->next;
            } else {
                fast = fast->next;
            }
            slow = slow->next;
        }
        if (!slow->next) {
            return true;
        }
        auto r = reverse(slow->next);
        for( ; r ; r = r->next, head = head->next) {
           if (r->val != head->val) {
               return false;
           }
        }
        return true;
    }
    
private:
    ListNode* reverse(ListNode* head) {
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

TEST_CASE("Palindrome Linked List") {
    TEST_SOLUTION(isPalindrome, v1) {
        CHECK_FALSE(isPalindrome(makeList({1, 2})));
        CHECK(isPalindrome(makeList({1, 2, 2, 1})));
        CHECK(isPalindrome(makeList({1, 2, 3, 2, 1})));
        CHECK(isPalindrome(makeList({1})));
        CHECK(isPalindrome(makeList({})));
    };
}

} // namespace palindrome_linked_list
