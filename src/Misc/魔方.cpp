本题的输入是一个魔方的展开图，我们以黄色为中心块的面作为顶面，红色为中心块的面作为前面，绿色为中心块的面作为右面。
定义六种魔方转动操作类型，分别如下：
1. "R1"：右面顺时针旋转90度
2. "R2"：右面逆时针旋转90度
3. "U1"：顶面顺时针旋转90度
4. "U2"：顶面逆时针旋转90度
5. "F1"：前面顺时针旋转90度
6. "F2"：前面逆时针旋转90度
Sol：
特殊限制：存在 6 种不同操作，且一定存在步数小于等于 8 的正解
直接暴力 dfs 或 bfs 搜索答案即可。

考虑魔方在转动某一面时，转动面的 9 个颜色会进行顺时针或逆时针移位，与转动面相邻的 4 个侧面中，直接
与转动面相邻的 3 个颜色也会按顺时针或逆时针顺序循环移位。故可使用 struct Plane 定义一个面按顺序排列的九种
颜色，结构体内部实现单面的顺时针或逆时针移位。使用 struct Cube 定义整个魔方的状态，每次操作先转动单面，
再按顺序移位相邻 4 个侧面中的 3 个相邻颜色即可。
      O O O
      O O O
B B B Y Y Y G G G W W W
B B B Y Y Y G G G W W W
B B B Y Y Y G G G W W W
      R R R
      R R R
      R R R 
#include <bits/stdc++.h>
#define Buff ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
using namespace std;
typedef vector<char> vchar;

struct Plane  // 面
{
    char c[9];

    Plane() {
        memset(c, 0, sizeof(c));
    }

    void set(char x)  // 设置颜色，本题非必要
    {
        memset(c, x, sizeof(c));
    }

    bool check() const  // 判断此面颜色是否相同
    {
        for (int i = 1; i < 9; i++) {
            if (c[i] != c[0])
                return false;
        }
        return true;
    }

    void CRotate()  // 此面顺时针旋转90度
    {
        char b = c[0];
        c[0] = c[6];
        c[6] = c[8];
        c[8] = c[2];
        c[2] = b;

        b = c[1];
        c[1] = c[3];
        c[3] = c[7];
        c[7] = c[5];
        c[5] = b;
    }

    void CCRotate()  // 此面逆时针旋转90度
    {
        char b = c[0];
        c[0] = c[2];
        c[2] = c[8];
        c[8] = c[6];
        c[6] = b;

        b = c[1];
        c[1] = c[5];
        c[5] = c[7];
        c[7] = c[3];
        c[3] = b;
    }
};

struct Cube  // 魔方
{
    Plane p[6];

    Cube() {
        init();
    }

    void init()  // 初始化颜色，本题非必要
    {
        p[0].set('R');
        p[1].set('G');
        p[2].set('Y');
        p[3].set('O');
        p[4].set('B');
        p[5].set('W');
    }

    bool check() const  // 判断是否已还原
    {
        for (int i = 0; i < 6; i++) {
            if (!p[i].check())
                return false;
        }
        return true;
    }

    void operate(int opid)  // 操作
    {
        if (opid == 1)
            R1();
        else if (opid == 2)
            R2();
        else if (opid == 3)
            U1();
        else if (opid == 4)
            U2();
        else if (opid == 5)
            F1();
        else if (opid == 6)
            F2();
    }

    void roperate(int opid)  // 逆操作
    {
        if (opid == 1)
            R2();
        else if (opid == 2)
            R1();
        else if (opid == 3)
            U2();
        else if (opid == 4)
            U1();
        else if (opid == 5)
            F2();
        else if (opid == 6)
            F1();
    }

    void R1() {
        p[1].CRotate();  // 旋转面

        int updateplane[4] = {0, 5, 3, 2};  // 需要按顺序移位的相邻面
        int updateid[4][3] = {{2, 5, 8},    // 每面需要移位的颜色下标
                              {6, 3, 0},
                              {2, 5, 8},
                              {2, 5, 8}};

        update(updateid, updateplane);
    }
    void R2() {
        p[1].CCRotate();

        int updateplane[4] = {0, 2, 3, 5};
        int updateid[4][3] = {{2, 5, 8},
                              {2, 5, 8},
                              {2, 5, 8},
                              {6, 3, 0}};

        update(updateid, updateplane);
    }

    void U1() {
        p[2].CRotate();

        int updateplane[4] = {0, 1, 3, 4};
        int updateid[4][3] = {{0, 1, 2},
                              {6, 3, 0},
                              {8, 7, 6},
                              {2, 5, 8}};

        update(updateid, updateplane);
    }
    void U2() {
        p[2].CCRotate();

        int updateplane[4] = {0, 4, 3, 1};
        int updateid[4][3] = {{0, 1, 2},
                              {2, 5, 8},
                              {8, 7, 6},
                              {6, 3, 0}};

        update(updateid, updateplane);
    }

    void F1() {
        p[0].CRotate();

        int updateplane[4] = {1, 2, 4, 5};
        int updateid[4][3] = {{6, 7, 8},
                              {6, 7, 8},
                              {6, 7, 8},
                              {6, 7, 8}};

        update(updateid, updateplane);
    }
    void F2() {
        p[0].CCRotate();

        int updateplane[4] = {1, 5, 4, 2};
        int updateid[4][3] = {{6, 7, 8},
                              {6, 7, 8},
                              {6, 7, 8},
                              {6, 7, 8}};

        update(updateid, updateplane);
    }

    void update(int uid[4][3], int uplane[4])  // 循环移位相邻面颜色
    {
        char buffer[3] = {p[uplane[0]].c[uid[0][0]],
                          p[uplane[0]].c[uid[0][1]],
                          p[uplane[0]].c[uid[0][2]]};

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                p[uplane[i]].c[uid[i][j]] = p[uplane[i + 1]].c[uid[i + 1][j]];
        }

        p[uplane[3]].c[uid[3][0]] = buffer[0];
        p[uplane[3]].c[uid[3][1]] = buffer[1];
        p[uplane[3]].c[uid[3][2]] = buffer[2];
    }

    friend std::istream& operator>>(std::istream& os, Cube& cube)  // 输入
    {
        std::string buffer;

        for (int i = 0; i < 9; i += 3) {
            for (int j = 0; j < 3; j++) {
                os >> buffer;
                cube.p[3].c[i + j] = buffer[0];
            }
        }

        for (int i = 0; i < 9; i += 3) {
            for (int j = 0; j < 3; j++) {
                os >> buffer;
                cube.p[4].c[i + j] = buffer[0];
            }
            for (int j = 0; j < 3; j++) {
                os >> buffer;
                cube.p[2].c[i + j] = buffer[0];
            }
            for (int j = 0; j < 3; j++) {
                os >> buffer;
                cube.p[1].c[i + j] = buffer[0];
            }
            for (int j = 0; j < 3; j++) {
                os >> buffer;
                cube.p[5].c[i + j] = buffer[0];
            }
        }

        for (int i = 0; i < 9; i += 3) {
            for (int j = 0; j < 3; j++) {
                os >> buffer;
                cube.p[0].c[i + j] = buffer[0];
            }
        }

        return os;
    }

    friend std::ostream& operator<<(std::ostream& os, const Cube& cube)  // 输出，本题非必要
    {
        for (int i = 0; i < 9; i += 3) {
            os << "      ";
            for (int j = 0; j < 3; j++) {
                os << cube.p[3].c[i + j];
                if (j < 2)
                    os << ' ';
            }
            os << '\n';
        }

        for (int i = 0; i < 9; i += 3) {
            for (int j = 0; j < 3; j++) {
                os << cube.p[4].c[i + j] << ' ';
            }
            for (int j = 0; j < 3; j++) {
                os << cube.p[2].c[i + j] << ' ';
            }
            for (int j = 0; j < 3; j++) {
                os << cube.p[1].c[i + j] << ' ';
            }
            for (int j = 0; j < 3; j++) {
                os << cube.p[5].c[i + j];
                if (j < 2)
                    os << ' ';
            }
            os << '\n';
        }

        for (int i = 0; i < 9; i += 3) {
            os << "      ";
            for (int j = 0; j < 3; j++) {
                os << cube.p[0].c[i + j];
                if (j < 2)
                    os << ' ';
            }
            os << '\n';
        }

        return os;
    }
};

/////////////////////////////////////////////////////////////////////////////////

void dfs(Cube& cube, vchar& way, bool& flag, size_t stop)  // dfs深搜
{
    if (way.size() >= stop)
        return;

    char ref = -1;  // 上次操作的逆操作序号
    if (!way.empty()) {
        ref = *(way.rbegin());
        if (ref & 1)
            ref++;
        else
            ref--;
    }

    for (char i = 1; i <= 6; i++) {
        if (i == ref)  // 剪枝
            continue;

        cube.operate(i);
        way.emplace_back(i);

        if (cube.check()) {
            flag = true;
            return;
        }

        dfs(cube, way, flag, stop);

        if (flag)
            return;

        cube.roperate(i);  // 回溯
        way.pop_back();
    }
}

vchar bfs(Cube icube)  // bfs宽搜
{
    using pcv = pair<Cube, vchar>;  // 保存的魔方状态以及操作顺序

    pcv ib;
    ib.first = icube;
    queue<pcv> q;
    q.push(ib);

    vchar ans;

    while (!q.empty()) {
        pcv b = q.front();
        q.pop();
        char ref = -1;  // 上次操作的逆操作序号
        if (!b.second.empty()) {
            ref = *(b.second.rbegin());
            if (ref & 1)
                ref++;
            else
                ref--;
        }

        for (char i = 1; i <= 6; i++) {
            if (i == ref)
                continue;

            pcv x = b;
            x.first.operate(i);
            x.second.emplace_back(i);

            if (x.first.check()) {
                ans = x.second;
                return ans;
            }

            q.push(x);
        }
    }

    return ans;
}

void solve() {
    Cube cube;
    cin >> cube;

    if (cube.check()) {
        cout << "0\n";
        return;
    }

    vchar ans;

    // ans = bfs(cube); // bfs调用

    bool flag = false;
    dfs(cube, ans, flag, 8);  // dfs调用

    cout << ans.size() << '\n';

    vector<string> map_op{"", "R1", "R2", "U1", "U2", "F1", "F2"};  // 操作映射
    for (char i : ans) {
        if (i >= 1 && i <= 6)
            cout << map_op[i] << '\n';
    }
}

int main() {
    Buff;
    int _N = 1;
    // cin >> _N;
    while (_N--)
        solve();
    return 0;
}


