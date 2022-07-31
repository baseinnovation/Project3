#include "Bin.h"
using namespace std;

template <typename T>
class Unordered_Map {
private:
    list<list<pair<int, T>>> *buckets;
    int bucketSize;
    int numElements;
    float maxLoadFactor;
    hash<string> stringHash;

public:
    int hash(string key) {
        int hashedKey = stringHash(key);
        return hashedKey % bucketSize;
    }

    list<int>::iterator find(string key) {
        for (auto i: buckets[hash(key)]) {
            for (auto j: i)
                if (j.first == key)
                    return j;
        }
        return buckets[hash(key)].end();
    }

    void insert(string key, T value) {
        auto iter = find(key);
        if (iter != buckets[hash(key)].end()) {
            iter->second = value;
            return;
        }
        buckets[hash(key)].push_back({key, value});
        numElements++;
    }
};
