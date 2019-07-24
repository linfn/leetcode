/*
Longest Increasing Subsequence

URL: https://leetcode.com/problems/longest-increasing-subsequence
Tags: ['binary-search', 'dynamic-programming']
___

Given an unsorted array of integers, find the length of longest increasing
subsequence.

Example:

    Input: [10,9,2,5,3,7,101,18]
    Output: 4
    Explanation: The longest increasing subsequence is [2,3,7,101], therefore
the length is 4.

Note:

  * There may be more than one LIS combination, it is only necessary for you to
return the length.
  * Your algorithm should run in O( n 2) complexity.

Follow up: Could you improve it to O( n log n ) time complexity?
*/

#include <vector>
#include <limits>

#include "test.h"

using std::vector;

namespace longest_increasing_subsequence {

namespace v1 {
// NOTE: v1 版本 Time Limit Exceeded, 不可取.
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        return step(nums, 0, std::numeric_limits<int>::min());
    }

private:
    // 这个方式更像是一种迭代, 每迭代一步可以对最后的结果 +1 或者不加.
    int step(vector<int>& nums, int k, int prev) {
        if (k >= nums.size()) {
            return 0;
        }
        int n1 = 0, n2 = 0;
        // 当当前的值大于之前的值时, 有两种选择,
        // 接纳当前值作为结果的一部分, 或者选择不接纳, 继续往后迭代
        if (nums[k] > prev) {
            n1 = 1 + step(nums, k + 1, nums[k]);
        }
        n2 = step(nums, k + 1, prev);
        return n1 > n2 ? n1 : n2;
    }
};
} // namespace v1

inline namespace v2 {
/*
假设, F(i) 表示以第i项结尾的最长递增数列长度 (第i项必须是递增数列的一部分), 则:
F(0) = 1
F(i+1) = max{ 1, F(j)+1 }, 其中j可取值的集合是 0<=j<=i, 且 nums[i+1]>nums[j]
于是:
LIS(n) = max{ F(i) }, 其中 0 <= i <= n
*/
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        vector<int> F(nums.size());
        F[0] = 1;
        int result = 0;
        for (int i = 0; i < nums.size(); i++) {
            int max = 1;
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    auto a = F[j] + 1;
                    if (a > max) {
                        max = a;
                    }
                }
            }
            F[i] = max;
            if (max > result) {
                result = max;
            }
        }
        return result;
    }
};
} // namespace v2

TEST_CASE("Longest Increasing Subsequence") {
    TEST_SOLUTION(lengthOfLIS, v1, v2) {
        vector<int> v = {10, 9, 2, 5, 3, 7, 101, 18};
        CHECK(lengthOfLIS(v) == 4);

        BENCHMARK("") { return lengthOfLIS(v); };

        v = {0};
        CHECK(lengthOfLIS(v) == 1);
    };
}

} // namespace longest_increasing_subsequence
