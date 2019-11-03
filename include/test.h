#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>

// common include
#include <tuple>
#include <map>
#include <unordered_map>
#include <stack>
#include <list>
#include <deque>
#include <limits>
#include <algorithm>

#include "catch.hpp"

#ifndef CATCH_CONFIG_ENABLE_BENCHMARKING
#define BENCHMARK(...)                                                         \
    if (test::detail::IgnoreUnused _{})                                        \
    _ = [&]()
#endif

#ifdef ENABLE_DBG
#include "dbg.h"
#endif

namespace test {
namespace detail {

class IgnoreUnused {
public:
    template <typename T>
    IgnoreUnused& operator=(T&& f) {
        return *this;
    }
    explicit operator bool() { return false; }
};

template <typename Fun>
struct Solution {
    std::string name;
    Fun f;
};

template <typename C, typename R, typename... Args>
Solution<std::function<R(Args...)>> makeSolution(const std::string& name,
                                                 R (C::*fp)(Args...)) {
    auto p = std::make_shared<C>();
    auto f = [=](Args... args) -> R { return (p.get()->*fp)(args...); };
    return {name, f};
}

template <typename Solution>
class RunTests {
    std::vector<Solution> solutions_;

public:
    RunTests(const std::initializer_list<Solution>& solutions)
        : solutions_(solutions) {}

    template <typename Func>
    RunTests& operator|(Func f) {
        for (auto& s : solutions_) {
            SECTION(s.name) { f(s.f, s.name); };
        }
        return *this;
    }
    explicit operator bool() { return true; };
};

} // namespace detail
} // namespace test

#define _CAT(a, b) a##b
#define CAT(a, b) _CAT(a, b)

#define _GET_NTH_ARG(_1, _2, _3, _4, _5, N, ...) N
#define COUNT_ARGS(...) _GET_NTH_ARG(__VA_ARGS__, 5, 4, 3, 2, 1)

#define TEST_SOLUTION(F, V, ...)                                               \
    if (test::detail::RunTests<decltype(                                       \
            test::detail::makeSolution(#V, &V::Solution::F))>                  \
            runtests = {CAT(SOLUTIONS_, COUNT_ARGS(V, ##__VA_ARGS__))(         \
                F, V, ##__VA_ARGS__)})                                         \
    runtests | [&](decltype(                                                   \
                       test::detail::makeSolution(#V, &V::Solution::F).f) F,   \
                   const std::string& section)

#define SOLUTIONS_1(F, V) test::detail::makeSolution(#V, &V::Solution::F)

#define SOLUTIONS_2(F, V1, V2) SOLUTIONS_1(F, V1), SOLUTIONS_1(F, V2)

#define SOLUTIONS_3(F, V1, V2, V3) SOLUTIONS_2(F, V1, V2), SOLUTIONS_1(F, V3)

#define SOLUTIONS_4(F, V1, V2, V3, V4)                                         \
    SOLUTIONS_3(F, V1, V2, V3), SOLUTIONS_1(F, V4)

#define SOLUTIONS_5(F, V1, V2, V3, V4, V5)                                     \
    SOLUTIONS_4(F, V1, V2, V3, V4), SOLUTIONS_1(F, V5)

namespace leetcode {

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

static inline ListNode* makeList(const std::vector<int>& vals) {
    ListNode *l = nullptr, *cur = nullptr;
    for (auto v : vals) {
        auto n = new ListNode(v);
        if (l == nullptr) {
            l = n;
        } else {
            cur->next = n;
        }
        cur = n;
    }
    return l;
}

static inline void freeList(ListNode* l) {
    while (l) {
        auto next = l->next;
        delete l;
        l = next;
    }
}

static inline bool listEqual(ListNode* lhs, ListNode* rhs) {
    if (lhs == rhs) {
        return true;
    }
    for (; lhs && rhs; lhs = lhs->next, rhs = rhs->next) {
        if (lhs->val != rhs->val) {
            return false;
        }
    }
    return lhs == rhs;
}

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

static inline TreeNode* makeTree(const std::vector<int>& vals, int nil = 0) {
    if (vals.empty()) {
        return nullptr;
    }
    auto root = new TreeNode(vals.front());
    auto list = std::vector<TreeNode*>{root};
    for (auto i = vals.begin();;) {
        auto parent = list.front();
        list.erase(list.begin());
        i++;
        if (i == vals.end()) {
            break;
        }
        parent->left = *i != nil ? new TreeNode(*i) : nullptr;
        list.push_back(parent->left);
        i++;
        if (i == vals.end()) {
            break;
        }
        parent->right = *i != nil ? new TreeNode(*i) : nullptr;
        list.push_back(parent->right);
    }
    return root;
}

static inline void freeTree(TreeNode* tree) {
    if (!tree) {
        return;
    }
    freeTree(tree->left);
    freeTree(tree->right);
    delete tree;
}

static inline bool treeEqual(TreeNode* lhs, TreeNode* rhs) {
    if (!lhs || !rhs) {
        if (!lhs && !rhs) {
            return true;
        }
        return false;
    }
    if (lhs->val != rhs->val) {
        return false;
    }
    return treeEqual(lhs->left, rhs->left) && treeEqual(lhs->right, rhs->right);
}

template <typename T>
bool unorderedEqual(std::vector<T> l, std::vector<T> r) {
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    return l == r;
}

template <typename T>
bool unorderedEqual(std::vector<std::vector<T>> l,
                    std::vector<std::vector<T>> r) {
    for (auto i = l.begin(); i != l.end(); i++) {
        sort(i->begin(), i->end());
    }
    for (auto i = r.begin(); i != r.end(); i++) {
        sort(i->begin(), i->end());
    }
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    return l == r;
}

} // namespace leetcode
