template <class T>
struct Frac {
    T zi;
    T mu;
    Frac(T num_, T den_) : zi(num_), mu(den_) {
        if (mu < 0) {
            mu = -mu;
            zi = -zi;
        }
    }
    Frac() : Frac(0, 1) {}  // (1/0)
    Frac(T num_) : Frac(num_, 1) {}
    void reduce() {
        T g = std::gcd(zi, mu);  // 调用 std::gcd 计算最大公约数
        zi /= g;                 // 将分子除以最大公约数
        mu /= g;                 // 将分母除以最大公约数
    }
    explicit operator double() const {
        return 1. * zi / mu;
    }
    Frac &operator+=(const Frac &rhs) {
        zi = zi * rhs.mu + rhs.zi * mu;
        mu *= rhs.mu;
        return *this;
    }
    Frac &operator-=(const Frac &rhs) {
        zi = zi * rhs.mu - rhs.zi * mu;
        mu *= rhs.mu;
        return *this;
    }
    Frac &operator*=(const Frac &rhs) {
        zi *= rhs.zi;
        mu *= rhs.mu;
        return *this;
    }
    Frac &operator/=(const Frac &rhs) {
        zi *= rhs.mu;
        mu *= rhs.zi;
        if (mu < 0) {
            zi = -zi;
            mu = -mu;
        }
        return *this;
    }
    friend Frac operator+(Frac lhs, const Frac &rhs) {
        return lhs += rhs;
    }
    friend Frac operator-(Frac lhs, const Frac &rhs) {
        return lhs -= rhs;
    }
    friend Frac operator*(Frac lhs, const Frac &rhs) {
        return lhs *= rhs;
    }
    friend Frac operator/(Frac lhs, const Frac &rhs) {
        return lhs /= rhs;
    }
    friend Frac operator-(const Frac &a) {
        return Frac(-a.zi, a.mu);
    }
    friend bool operator==(const Frac &lhs, const Frac &rhs) {
        return lhs.zi * rhs.mu == rhs.zi * lhs.mu;
    }
    friend bool operator!=(const Frac &lhs, const Frac &rhs) {
        return lhs.zi * rhs.mu != rhs.zi * lhs.mu;
    }
    friend bool operator<(const Frac &lhs, const Frac &rhs) {
        return lhs.zi * rhs.mu < rhs.zi * lhs.mu;
    }
    friend bool operator>(const Frac &lhs, const Frac &rhs) {
        return lhs.zi * rhs.mu > rhs.zi * lhs.mu;
    }
    friend bool operator<=(const Frac &lhs, const Frac &rhs) {
        return lhs.zi * rhs.mu <= rhs.zi * lhs.mu;
    }
    friend bool operator>=(const Frac &lhs, const Frac &rhs) {
        return lhs.zi * rhs.mu >= rhs.zi * lhs.mu;
    }
    friend std::ostream &operator<<(std::ostream &os, Frac x) {
        T g = std::gcd(x.zi, x.mu);
        if (x.mu == g) {
            return os << x.zi / g;
        } else {
            return os << x.zi / g << "/" << x.mu / g;
        }
    }
};