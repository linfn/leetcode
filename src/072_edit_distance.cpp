
/*
Edit Distance

URL: https://leetcode.com/problems/edit-distance
Tags: ['string', 'dynamic-programming']
___

Given two words word1 and word2 , find the minimum number of operations
required to convert word1 to word2.

You have the following 3 operations permitted on a word:

  1. Insert a character
  2. Delete a character
  3. Replace a character

Example 1:

    Input: word1 =  "horse", word2 = "ros"
    Output: 3
    Explanation:
    horse - > rorse (replace 'h' with 'r')
    rorse -> rose (remove 'r')
    rose -> ros (remove 'e')


Example 2:

    Input: word1 =  "intention", word2 = "execution"
    Output: 5
    Explanation:
    intention - > inention (remove 't')
    inention -> enention (replace 'i' with 'e')
    enention -> exention (replace 'n' with 'x')
    exention -> exection (replace 'n' with 'c')
    exection -> execution (insert 'u')
*/

#include "test.h"

using std::string;

namespace edit_distance {

/*
    Time Limit Exceeded
*/
namespace v1 {

using std::numeric_limits;
using std::swap;

class Solution {
public:
    int minDistance(string word1, string word2) {
        if (word1 == word2) {
            return 0;
        }
        int min = numeric_limits<int>::max();
        if (word1.length() == word2.length()) {
            min = replaceDis(word1, word2);
        } else if (word1.length() < word2.length()) {
            swap(word2, word1);
        }
        for (int i = 0; i < word1.length(); i++) {
            int d = minDistance(remove(word1, i), word2) + 1;
            if (d < min) {
                min = d;
            }
        }
        return min;
    }

private:
    string remove(string word, int i) {
        word.erase(word.begin() + i);
        return word;
    }

    int replaceDis(string word1, string word2) {
        int result = 0;
        for (int i = 0; i < word1.length(); i++) {
            if (word1[i] != word2[i]) {
                result++;
            }
        }
        return result;
    }
};
} // namespace v1

/*
设 dp[i][j] 是从 word1[0...i] to word2[0...j] 的距离
(这里 0 表示空字符串)

1. 从空字符串转换到目标等于目标字符串的长度
2. dp[i][j] =
    1. dp[i-1][j-1] when word1[i-1] == word2[j-1]
    2. min(使用 replace, 使用 delete, 使用 insert)
*/
inline namespace v2 {

using std::min;
using std::vector;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.length() + 1, n = word2.length() + 1;
        vector<vector<int>> dp(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
            dp[i][0] = i;
        }
        for (int j = 0; j < n; j++) {
            dp[0][j] = j;
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] =
                        min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j])) +
                        1;
                }
            }
        }
        return dp[m - 1][n - 1];
    }
};
} // namespace v2

TEST_CASE("Edit Distance") {
    TEST_SOLUTION(minDistance, v2) {
        CHECK(minDistance("horse", "ros") == 3);
        CHECK(minDistance("intention", "execution") == 5);
        CHECK(minDistance("sea", "eat") == 2);
    };
}

} // namespace edit_distance
