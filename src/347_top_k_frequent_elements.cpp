
/*
Top K Frequent Elements

URL: https://leetcode.com/problems/top-k-frequent-elements
Tags: ['hash-table', 'heap']
___

Given a non-empty array of integers, return the k most frequent elements.

Example 1:

    Input: nums = [1,1,1,2,2,3], k = 2
    Output: [1,2]


Example 2:

    Input: nums = [1], k = 1
    Output: [1]

Note:

  * You may assume k is always valid, 1  ≤ k ≤ number of unique elements.
  * Your algorithm's time complexity must be better than O( n log n ), where n
is the array 's size.
*/

#include <unordered_map>
#include "test.h"

using std::vector;

namespace top_k_frequent_elements {

/*
    先排序, 再统计并维护一个有序数组, 取 top k.
    另一个思路是用 hashmap + 最小堆来做.
*/
inline namespace v1 {

using std::greater;
using std::lower_bound;

class Solution {
    struct Item {
        int num;
        int count;
        bool operator>(const Item& item) { return this->count > item.count; }
    };

public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> result;
        if (nums.empty()) {
            return result;
        }

        // 这里如果使用外部排序, 则可以处理大数据量的 TOP k 问题.
        sort(nums.begin(), nums.end());

        // 要注意结束的处理, 这里通过增加一个无用数字来通用化.
        nums.resize(nums.size() + 1, nums.back() + 1);

        vector<Item> top;
        top.reserve(k + 1);
        Item item = {nums.front(), 0};
        for (auto n : nums) {
            if (item.num == n) {
                item.count++;
            } else {
                top.insert(
                    lower_bound(top.begin(), top.end(), item, greater<>()),
                    item);
                if (top.size() > k) {
                    top.pop_back();
                }
                item.num = n;
                item.count = 1;
            }
        }

        result.reserve(k);
        for (const auto& item : top) {
            result.push_back(item.num);
        }
        return result;
    }
};
} // namespace v1

TEST_CASE("Top K Frequent Elements") {
    TEST_SOLUTION(topKFrequent, v1) {
        vector<int> v = {1, 1, 1, 2, 2, 3};
        CHECK(topKFrequent(v, 2) == vector<int>{1, 2});

        v = {1};
        CHECK(topKFrequent(v, 1) == vector<int>{1});
    };
}

} // namespace top_k_frequent_elements
