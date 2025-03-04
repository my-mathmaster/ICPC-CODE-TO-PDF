priority_queue<int> down;                           // 大根堆
priority_queue<int, vector<int>, greater<int> > b;  // 前k大的元素在这里，第k大在堆顶
void insert(int x) {
    if (b.empty() || x >= b.top())
        b.push(x);  // 插入
    else {
        down.push(x);
    }
}
int stob(int sum, int small) {  // 第small小转化为第k大，当前总数意义下
    return sum + 1 - small;
}
void makebl(int k) {                                        // 维护前k大性质
    while ((int)b.size() > k) down.push(b.top()), b.pop();  // 调整
    while ((int)b.size() < k) b.push(down.top()), down.pop();
}
int getkth() {
    return b.top();
}