
/*
Search Insert Position

URL: https://leetcode.com/problems/search-insert-position
Tags: ['array', 'binary-search']
___

Given a sorted array and a target value, return the index if the target is
found. If not, return the index where it would be if it were inserted in
order.

You may assume no duplicates in the array.

Example 1:

    Input: [1,3,5,6], 5
    Output: 2


Example 2:

    Input: [1,3,5,6], 2
    Output: 1


Example 3:

    Input: [1,3,5,6], 7
    Output: 4


Example 4:

    Input: [1,3,5,6], 0
    Output: 0
*/

#include <vector>
#include <algorithm>

#include "test.h"

using std::lower_bound;
using std::vector;

namespace search_insert_position {

namespace v1 {
// 一行流
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        return lower_bound(nums.begin(), nums.end(), target) - nums.begin();
    }
};
} // namespace v1

namespace v2 {
// 二分查找
class Solution {
    typedef vector<int>::iterator Iter;

public:
    int searchInsert(vector<int>& nums, int target) {
        return bsearch(nums.begin(), nums.end(), target) - nums.begin();
    }

private:
    Iter bsearch(Iter begin, Iter end, int target) {
        if (begin == end) {
            return end;
        }
        auto m = begin + (end - begin) / 2;
        if (target == *m) {
            return m;
        } else if (target > *m) {
            return bsearch(m + 1, end, target);
        } else {
            return bsearch(begin, m, target);
        }
    }
};
} // namespace v2

inline namespace v3 {
// v2 版本的迭代版本
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        typedef vector<int>::iterator Iter;
        Iter begin = nums.begin(), end = nums.end();
        while (begin != end) {
            auto m = begin + (end - begin) / 2;
            if (target == *m) {
                return m - nums.begin();
            } else if (target > *m) {
                begin = m + 1;
            } else {
                end = m;
            }
        }
        return end - nums.begin();
    }
};
} // namespace v3

TEST_CASE("Search Insert Position") {
    TEST_SOLUTION(searchInsert, v1, v2, v3) {
        vector<int> v = {1, 3, 5, 6};
        CHECK(searchInsert(v, 5) == 2);
        v = {1, 3, 5, 6};
        CHECK(searchInsert(v, 2) == 1);
        v = {1, 3, 5, 6};
        CHECK(searchInsert(v, 7) == 4);
        v = {1, 3, 5, 6};
        CHECK(searchInsert(v, 0) == 0);

        v = {1, 3, 5, 6};
        BENCHMARK("") { return searchInsert(v, 7); };
    };
}

} // namespace search_insert_position
