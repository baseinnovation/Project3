//
// Created by Cathy Quan on 7/31/22.
//

#ifndef UNTITLED_UNORDERED_MAP_H
#define UNTITLED_UNORDERED_MAP_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class Unordered_Map {
private:
    vector<vector<pair<string, vector<T>>>> buckets;
    int bucketSize;
    int numElements;
    float maxLoadFactor;
    hash<string> stringHash;

public:
    Unordered_Map() {
        bucketSize = 10;
        numElements = 0;
        maxLoadFactor = 0.8f;
    }

    int hash(string key) {
        int hashedKey = stringHash(key);
        return hashedKey % bucketSize;
    }

    void rehash() {
        if (numElements / bucketSize <= maxLoadFactor)
            return;
        bucketSize *= 2;
        vector<vector<pair<string, vector<T>>>> newBuckets(bucketSize);
        for (int i = 0; i < buckets.size(); i++) {
            for (int j = 0; j < buckets[i]; j++) {
                int newHash = hash(buckets[i][j].first);
                newBuckets[newHash].push_back({buckets[i][j].first, buckets[i][j].second});
            }
            buckets = newBuckets;
        }
    }

    T find(string key) {
        for (int i = 0; i < buckets[hash(key)].size(); i++) {
            if (buckets[hash(key)][i].first == key)
                return buckets[hash(key)][i].second;
        }
        cout << "does not exist" << endl;
        return nullptr;
    }

    void insert(string key, T value) {
        for (int i = 0; i < buckets[hash(key)].size(); i++) {
            if (buckets[hash(key)][i].first == key) {
                buckets[hash(key)][i].second.push_back(value);
                return;
            }
        }
        vector<T> newCategory;
        newCategory.push_back(value);
        buckets[hash(key)].push_back({key, newCategory});
        numElements++;
        rehash();
    }
};

#endif //UNTITLED_UNORDERED_MAP_H
