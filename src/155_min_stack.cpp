
/*
Min Stack

URL: https://leetcode.com/problems/min-stack
Tags: ['stack', 'design']
___

Design a stack that supports push, pop, top, and retrieving the minimum
element in constant time.

  * push(x) -- Push element x onto stack.
  * pop() -- Removes the element on top of the stack.
  * top() -- Get the top element.
  * getMin() -- Retrieve the minimum element in the stack.



Example:

    MinStack minStack = new MinStack();
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    minStack.getMin();   --> Returns -3.
    minStack.pop();
    minStack.top();      --> Returns 0.
    minStack.getMin();   --> Returns -2.
*/

#include "test.h"

namespace min_stack {

inline namespace v1 {
using std::vector;
class MinStack {
    vector<int> stack_;
    vector<int> min_;

public:
    MinStack() {}

    void push(int x) {
        stack_.push_back(x);
        if (min_.empty() || x <= min_.back()) {
            min_.push_back(x);
        }
    }

    void pop() {
        if (min_.back() == stack_.back()) {
            min_.pop_back();
        }
        stack_.pop_back();
    }

    int top() { return stack_.back(); }

    int getMin() { return min_.back(); }
};

} // namespace v1

TEST_CASE("Min Stack") {

    MinStack minStack;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    CHECK(minStack.getMin() == -3);
    minStack.pop();
    CHECK(minStack.top() == 0);
    CHECK(minStack.getMin() == -2);

    minStack = MinStack();
    minStack.push(0);
    minStack.push(1);
    minStack.push(0);
    CHECK(minStack.getMin() == 0);
    minStack.pop();
    CHECK(minStack.getMin() == 0);
}

} // namespace min_stack
