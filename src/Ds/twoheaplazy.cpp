#include <bits/stdc++.h>
using namespace std;
class MedianFinder {//可删除对顶堆，动态维护中位数
    priority_queue<int, vector<int>, greater<int>> minheap;
    priority_queue<int> maxheap;
    unordered_map<int, int> delayed;
    int minSize, maxSize;  // decrease delayed

    template <typename T>
    void prune(T &heap) {
        while (!heap.empty()) {
            int num = heap.top();
            if (delayed.count(num)) {
                delayed[num]--;
                if (delayed[num] == 0)
                    delayed.erase(num);
                heap.pop();
            } else
                break;
        }
    }

    void makebalance() {
        if (maxSize > minSize + 1) {
            minheap.push(maxheap.top());
            maxheap.pop();
            minSize++;
            maxSize--;
            prune(maxheap);
        } else if (maxSize < minSize) {
            maxheap.push(minheap.top());
            minheap.pop();
            maxSize++;
            minSize--;
            prune(minheap);
        }
    }

public:
    MedianFinder() : minSize(0), maxSize(0) {}

    void insert(int num) {
        if (minheap.empty() && maxheap.empty()) {
            maxheap.push(num);
            maxSize++;
        } else {
            int topnum = maxheap.top();
            if (topnum < num) {
                minheap.push(num);
                minSize++;
            } else {
                maxheap.push(num);
                maxSize++;
            }
        }
        makebalance();
    }

    void erase(int num) {
        delayed[num]++;
        if (num <= maxheap.top()) {
            maxSize--;
            if (num == maxheap.top())
                prune(maxheap);
        } else {
            minSize--;
            if (num == minheap.top())
                prune(minheap);
        }
        makebalance();
    }

    double getMedian() {
        if (minSize == maxSize)
            return ((double)minheap.top() + maxheap.top()) / 2;  // 防范int溢出
        else
            return (double)maxheap.top();
    }
};

int main() {
    MedianFinder mf;

    // 插入一些数据
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        mf.insert(a[i]);
    }
    // mf.insert(3);
    // mf.insert(1);
    // mf.insert(5);
    // mf.insert(8);
    // mf.insert(2);
    for (int i = 1; i <= n; i++) {
        mf.erase(a[i]);
        // cout<<mf.getMedian() << endl;
        baoliu(mf.getMedian(), 1);
        cout << endl;
        mf.insert(a[i]);
    }
    // // 输出当前中位数
    // cout << "Current median: " << mf.getMedian() << endl;
    //
    // // 删除一个元素
    // mf.erase(1);
    //
    // // 再次输出中位数
    // cout << "Updated median: " << mf.getMedian() << endl;

    return 0;
}
