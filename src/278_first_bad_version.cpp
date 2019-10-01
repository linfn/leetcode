
/*
First Bad Version

URL: https://leetcode.com/problems/first-bad-version
Tags: ['binary-search']
___

You are a product manager and currently leading a team to develop a new
product. Unfortunately, the latest version of your product fails the quality
check. Since each version is developed based on the previous version, all the
versions after a bad version are also bad.

Suppose you have `n` versions `[1, 2, ..., n]` and you want to find out the
first bad one, which causes all the following ones to be bad.

You are given an API `bool isBadVersion(version)` which will return whether
`version` is bad. Implement a function to find the first bad version. You
should minimize the number of calls to the API.

Example:

    Given n = 5, and version = 4 is the first bad version.

    call isBadVersion(3) -> false
    call isBadVersion(5) -> true
    call isBadVersion(4) -> true

    Then 4 is the first bad version.
*/

#include "test.h"

namespace first_bad_version {

static int badVersion = 0;

// Forward declaration of isBadVersion API.
static bool isBadVersion(int version) { return version >= badVersion; }

inline namespace v1 {
/*
    需要处理溢出的问题
*/
class Solution {
public:
    int firstBadVersion(int n) { return search(1, n); }

private:
    int search(int begin, int end) {
        if (begin > end) {
            return 0;
        }
        int mid = begin + (end - begin) / 2;
        if (!isBadVersion(mid)) {
            return search(mid + 1, end);
        } else {
            if (mid == begin || !isBadVersion(mid - 1)) {
                return mid;
            } else {
                return search(begin, mid);
            }
        }
    }
};
} // namespace v1

TEST_CASE("First Bad Version") {
    TEST_SOLUTION(firstBadVersion, v1) {
        badVersion = 4;
        CHECK(firstBadVersion(5) == badVersion);

        badVersion = 2;
        CHECK(firstBadVersion(2) == badVersion);

        badVersion = 2147483647;
        CHECK(firstBadVersion(2147483647) == badVersion);
    };
}

} // namespace first_bad_version
