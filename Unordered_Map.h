#import "Bin.h"

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
        vector<vector<pair<string, vector<T>>>> newBuckets(bucketSize);
        buckets = newBuckets;
    }

    int hash(string key) {
        return stringHash(key) % bucketSize;
    }

    void rehash() {
        if (numElements / bucketSize <= maxLoadFactor)
            return;
        bucketSize *= 2;
        vector<vector<pair<string, vector<T>>>> newBuckets(bucketSize);
        for (int i = 0; i < buckets.size(); i++) {
            for (int j = 0; j < buckets[i].size(); j++) {
                int newHash = hash(buckets[i][j].first);
                newBuckets[newHash].push_back({buckets[i][j].first, buckets[i][j].second});
            }
            buckets = newBuckets;
        }
    }

    vector<T> find(string key) {
        for (int i = 0; i < buckets[hash(key)].size(); i++) {
            if (buckets[hash(key)][i].first == key)
                return buckets[hash(key)][i].second;
        }
        cout << "does not exist" << endl;
        vector<T> emptyVec;
        return emptyVec;
    }

    void insert(string key, T value, string name) {
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
