
/*
LRU Cache

URL: https://leetcode.com/problems/lru-cache
Tags: ['design']
___

Design and implement a data structure for [Least Recently Used (LRU)
cache](https://en.wikipedia.org/wiki/Cache_replacement_policies#LRU). It
should support the following operations: `get` and `put`.

`get(key)` \- Get the value (will always be positive) of the key if the key
exists in the cache, otherwise return -1.
`put(key, value)` \- Set or insert the value if the key is not already
present. When the cache reached its capacity, it should invalidate the least
recently used item before inserting a new item.

The cache is initialized with a positive capacity.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

    LRUCache cache = new LRUCache( 2 );

    cache.put(1, 1);
    cache.put(2, 2);
    cache.get(1);       // returns 1
    cache.put(3, 3);    // evicts key 2
    cache.get(2);       // returns -1 (not found)
    cache.put(4, 4);    // evicts key 1
    cache.get(1);       // returns -1 (not found)
    cache.get(3);       // returns 3
    cache.get(4);       // returns 4
*/

#include "test.h"

namespace lru_cache {

inline namespace v1 {
using std::list;
using std::unordered_map;
class LRUCache {
    struct Item {
        int value;
        list<int>::iterator iter;
    };
    int capacity_;
    unordered_map<int, Item> cache_;
    list<int> list_;

    auto find(int key) {
        auto i = cache_.find(key);
        if (i == cache_.end()) {
            return i;
        }
        list_.splice(list_.begin(), list_, i->second.iter);
        i->second.iter = list_.begin();
        return i;
    }

public:
    LRUCache(int capacity) : capacity_(capacity) {}

    int get(int key) {
        auto i = find(key);
        if (i == cache_.end()) {
            return -1;
        }
        return i->second.value;
    }

    void put(int key, int value) {
        auto i = find(key);
        if (i != cache_.end()) {
            i->second.value = value;
        } else {
            if (list_.size() >= capacity_) {
                cache_.erase(list_.back());
                list_.back() = key;
                list_.splice(list_.begin(), list_, prev(list_.end()));
            } else {
                list_.push_front(key);
            }
            cache_[key] = {value, list_.begin()};
        }
    }
};
} // namespace v1

TEST_CASE("LRU Cache") {
    LRUCache cache(2);

    cache.put(1, 1);
    cache.put(2, 2);
    CHECK(cache.get(1) == 1);
    cache.put(3, 3);
    CHECK(cache.get(2) == -1);
    cache.put(4, 4);
    CHECK(cache.get(1) == -1);
    CHECK(cache.get(3) == 3);
    CHECK(cache.get(4) == 4);
}

} // namespace lru_cache
