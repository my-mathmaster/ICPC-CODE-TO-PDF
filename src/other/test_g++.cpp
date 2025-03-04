#include <bits/stdc++.h>
using namespace std;
int main() {
    // GNU C++11: Array
    array<int, 3> C = {1, 2, 3};
    for (int i : C) {
        cout << i << " ";
    }
    cout << endl;
    // GNU C++14: Recursive lambda with auto
    auto dfs = [&](auto self, int x) -> void {
        if (x > 10)
            return;
        cout << "DFS at x = " << x << endl;
        self(self, x + 1);
    };
    dfs(dfs, 1);
    // GNU C++17: Template argument deduction for vector
    vector in(2, vector<int>(2, 1));
    for (auto x : in) {
        for (auto y : x) {
            cout << y << " ";
        }
        cout << endl;
    }

    // GNU C++17: Structured bindings
    map<int, int> dic = {{1, 2}, {3, 4}};
    for (auto [u, v] : dic) {
        cout << "{" << u << ", " << v << "} ";
    }
    cout << endl;
    // GNU C++20: contains method for map
    if (dic.contains(1)) {
        cout << "contains" << endl;
    } else {
        cout << "not contain" << endl;
    }

    return 0;
}
