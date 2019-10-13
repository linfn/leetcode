
/*
Group Anagrams

URL: https://leetcode.com/problems/group-anagrams
Tags: ['hash-table', 'string']
___

Given an array of strings, group anagrams together.

Example:

    Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
    Output:
    [
      [ "ate","eat","tea"],
      ["nat","tan"],
      ["bat"]
    ]

Note:

  * All inputs will be in lowercase.
  * The order of your output does not matter.
*/

#include "test.h"

using std::move;
using std::string;
using std::unordered_map;
using std::vector;

namespace group_anagrams {

inline namespace v1 {
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;
        for (const auto& str : strs) {
            string key = str;
            sort(key.begin(), key.end());
            auto iter = groups.find(key);
            if (iter == groups.end()) {
                groups[move(key)] = {str};
            } else {
                iter->second.push_back(str);
            }
        }
        vector<vector<string>> result;
        result.reserve(groups.size());
        for (auto& pair : groups) {
            result.emplace_back(move(pair.second));
        }
        return result;
    }
};
} // namespace v1

TEST_CASE("Group Anagrams") {
    TEST_SOLUTION(groupAnagrams, v1) {
        using leetcode::unorderedEqual;

        vector<string> v = {"eat", "tea", "tan", "ate", "nat", "bat"};
        CHECK(unorderedEqual(groupAnagrams(v),
                             vector<vector<string>>{{"ate", "eat", "tea"},
                                                    {"nat", "tan"},
                                                    {"bat"}}));
    };
}

} // namespace group_anagrams
