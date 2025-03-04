struct Matrix {
    using LL = long long;
    std::vector<std::vector<LL>> mat;
    Matrix() : mat{} {}

    /// @brief 生成n行m列空矩阵
    /// @param n 行数
    /// @param m 列数
    Matrix(int n, int m) : mat(n, std::vector<LL>(m)) {}

    /// @brief 生成单位矩阵 E
    /// @param n size
    Matrix(int n) : mat(n, std::vector<LL>(n)) {
        for (int i = 0; i < n; i++) {
            mat[i][i] = 1;
        }
    }

    int size() const { return mat.size(); }
    auto &operator[](int n) { return mat[n]; }
    auto &operator[](int n) const { return mat[n]; }

    auto begin() { return mat.begin(); }
    auto begin() const { return mat.begin(); }
    auto end() { return mat.end(); }
    auto end() const { return mat.end(); }

    Matrix operator*(const Matrix &o) const {
        Matrix res(mat.size(), o.size());
        for (size_t i = 0; i < res.size(); i++) {
            for (size_t k = 0; k < mat[0].size(); k++) {
                if (!mat[i][k])
                    continue;
                for (size_t j = 0; j < res[0].size(); j++) {
                    res[i][j] += mat[i][k] * o[k][j];
                    res[i][j] %= Mod;
                }
            }
        }
        return res;
    }

    Matrix operator*(const LL &a) const {
        Matrix res;
        res.mat = mat;
        for (int i = 0; i < res.size(); i++) {
            for (int j = 0; j < res[0].size(); j++) {
                res[i][j] *= a;
            }
        }
        return res;
    }

    friend Matrix operator*(const LL &a, const Matrix &o) { return o * a; }

    Matrix operator+(const Matrix &o) const {
        Matrix res = *this;
        for (int i = 0; i < res.size(); i++) {
            for (int j = 0; j < res[0].size(); j++) {
                res[i][j] = (mat[i][j] + o[i][j]) % Mod;
            }
        }
        return res;
    }

    Matrix operator-(const Matrix &o) const { return -1 * o + *this; }

    Matrix pow(LL k) const {
        Matrix a = *this;
        Matrix ans(this->size());
        while (k) {
            if (k & 1)
                ans = ans * a;
            a = a * a;
            k >>= 1;
        }
        return ans;
    }

    Matrix reverse() const {
        Matrix res(mat[0].size(), mat.size());
        for (int i = 0; i < mat[0].size(); i++) {
            for (int j = 0; j < mat.size(); j++) {
                res.mat[i][j] = mat[j][i];
            }
        }
        return res;
    }
};