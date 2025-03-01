#include <vector>

class DSU {
    std::vector<int> d;

    int root(int u) {
        if (d[u] == u)
            return u;
        return d[u] = root(d[u]);
    }

public:
    DSU(std::size_t size) : d(size + 1) {
        for (std::size_t i = 1; i <= size; i++) {
            d[i] = i;
        }
    }

    bool bind(int u, int v) {
        int x = root(u), y = root(v);
        if (x == y)
            return 0;
        else
            return (d[x] = y);
    }

    bool check(int u, int v) {
        return root(u) == root(v);
    }
};