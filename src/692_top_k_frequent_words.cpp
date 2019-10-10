
/*
Top K Frequent Words

URL: https://leetcode.com/problems/top-k-frequent-words
Tags: ['hash-table', 'heap', 'trie']
___

Given a non-empty list of words, return the k most frequent elements.

Your answer should be sorted by frequency from highest to lowest. If two words
have the same frequency, then the word with the lower alphabetical order comes
first.

Example 1:

    Input: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
    Output: ["i", "love"]
    Explanation: "i" and "love" are the two most frequent words.
        Note that "i" comes before "love" due to a lower alphabetical order.


Example 2:

    Input: ["the", "day", "is", "sunny", "the", "the", "the", "sunny", "is",
"is"], k = 4 Output: ["the", "is", "sunny", "day"] Explanation: "the", "is",
"sunny" and "day" are the four most frequent words, with the number of
occurrence being 4, 3, 2 and 1 respectively.


Note:

  1. You may assume k is always valid, 1  ≤ k ≤ number of unique elements.
  2. Input words contain only lowercase letters.

Follow up:

  1. Try to solve it in O ( n log k ) time and O ( n ) extra space.
*/

#include <unordered_map>
#include "test.h"

using std::string;
using std::vector;

namespace top_k_frequent_words {

inline namespace v1 {

using std::pair;
using std::reverse;
using std::unordered_map;

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> m;
        for (const auto& s : words) {
            m[s]++;
        }

        auto compare = [](const pair<string, int>& l,
                          const pair<string, int>& r) {
            if (l.second == r.second) {
                return l.first < r.first;
            }
            return l.second > r.second;
        };

        vector<pair<string, int>> top;
        top.reserve(k + 1);
        for (const auto& p : m) {
            top.push_back(p);
            push_heap(top.begin(), top.end(), compare);
            if (top.size() > k) {
                pop_heap(top.begin(), top.end(), compare);
                top.pop_back();
            }
        }

        vector<string> result;
        result.reserve(top.size());
        while (!top.empty()) {
            result.emplace_back(top.front().first);
            pop_heap(top.begin(), top.end(), compare);
            top.pop_back();
        }
        reverse(result.begin(), result.end());
        return result;
    }
};
} // namespace v1

TEST_CASE("Top K Frequent Words") {
    TEST_SOLUTION(topKFrequent, v1) {
        vector<string> v = {"i", "love", "leetcode", "i", "love", "coding"};
        CHECK(topKFrequent(v, 2) == vector<string>{"i", "love"});

        v = {"the", "day", "is",    "sunny", "the",
             "the", "the", "sunny", "is",    "is"};
        CHECK(topKFrequent(v, 4) ==
              vector<string>{"the", "is", "sunny", "day"});
    };
}

} // namespace top_k_frequent_words
