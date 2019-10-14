
/*
Merge Intervals

URL: https://leetcode.com/problems/merge-intervals
Tags: ['array', 'sort']
___

Given a collection of intervals, merge all overlapping intervals.

Example 1:

    Input: [[1,3],[2,6],[8,10],[15,18]]
    Output: [[1,6],[8,10],[15,18]]
    Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into
[1,6].


Example 2:

    Input: [[1,4],[4,5]]
    Output: [[1,5]]
    Explanation: Intervals [1,4] and [4,5] are considered overlapping.

NOTE:  input types have been changed on April 15, 2019. Please reset to
default code definition to get new method signature.
*/

#include "test.h"

using std::max;
using std::min;
using std::vector;

namespace merge_intervals {

namespace v1 {
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> result;
        for (const auto& v : intervals) {
            mergeVal(result, v);
        }
        return result;
    }

private:
    void mergeVal(vector<vector<int>>& intervals, const vector<int>& val) {
        for (auto i = intervals.begin(); i != intervals.end(); i++) {
            if ((*i)[0] > val[1] || (*i)[1] < val[0]) {
                continue;
            }
            vector<int> newVal = {min((*i)[0], val[0]), max((*i)[1], val[1])};
            if (newVal != (*i)) {
                intervals.erase(i);
                // 每个合并后新产生的值还需要递归进行 merge
                mergeVal(intervals, newVal);
            }
            return;
        }
        intervals.push_back(val);
    }
};
} // namespace v1

/*
    先排序后, 只需按序处理就可以了, 时间复杂度是 O(nlogn)
    但是 leetcode 上 v1 (时间复杂度O(n2)) 要比 v2 快上许多.
*/
inline namespace v2 {
using std::sort;
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& l, const vector<int>& r) {
                 return l[0] < r[0];
             });
        vector<vector<int>> result;
        for (const auto& v : intervals) {
            if (result.empty() || result.back()[1] < v[0]) {
                result.push_back(v);
            } else {
                result.back()[1] = max(v[1], result.back()[1]);
            }
        }
        return result;
    }
};
} // namespace v2

TEST_CASE("Merge Intervals") {
    TEST_SOLUTION(merge, v1, v2) {
        using leetcode::unorderedEqual;

        vector<vector<int>> v = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
        CHECK(unorderedEqual(merge(v),
                             vector<vector<int>>{{1, 6}, {8, 10}, {15, 18}}));

        BENCHMARK("") {
            vector<vector<int>> v = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
            return merge(v);
        };
    };
}

} // namespace merge_intervals
