#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include <local/dbg.h>
#else
    #define dbg(...) 42
#endif

using LL = long long;

// clang-format off
#define ai(x) using ai##x = array<int, x>;
ai(2); ai(3); ai(4); ai(5); ai(6); ai(7); ai(8); ai(9); ai(10); ai(26);
#undef ai
// clang-format on

#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()
template <class T>
inline bool updmx(T &x, const T &y) { return x < y ? x = y, 1 : 0; }
template <class T>
inline bool updmn(T &x, const T &y) { return y < x ? x = y, 1 : 0; }
template <class T>
inline void clr(T &x) { T().swap(x); }
template <class T>
inline void sortuniq(T &x) {
    sort(all(x));
    x.erase(unique(all(x)), x.end());
}

mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());
LL rand(LL l, LL r) { return rng() % (r - l + 1) + l; }

using LD = long double;
// eps???????????
constexpr LD eps = 1e-12; // ??????????1e-12???(?)
constexpr LD pi = numbers::pi_v<LD>;
constexpr int sign(LD x) { // ????
    if (fabs(x) < eps) return 0;
    if (x < 0) return -1;
    return 1;
}
constexpr int dcmp(LD x, LD y) { // ????
    if (fabs(x - y) < eps) return 0;
    if (x < y) return -1;
    return 1;
}

using PDD = pair<LD, LD>;
#define x first
#define y second

// ???????
constexpr PDD operator+(const PDD &a, const PDD &b) { return PDD{a.x + b.x, a.y + b.y}; }
constexpr PDD operator-(const PDD &a, const PDD &b) { return PDD{a.x - b.x, a.y - b.y}; }
constexpr PDD operator*(LD k, const PDD &a) { return PDD{k * a.x, k * a.y}; }
constexpr PDD operator*(const PDD &a, LD k) { return PDD{k * a.x, k * a.y}; }
constexpr PDD operator/(const PDD &a, LD k) { return PDD{a.x / k, a.y / k}; }
constexpr bool operator==(const PDD &a, const PDD &b) {
    return !dcmp(a.x, b.x) && !dcmp(a.y, b.y);
}

constexpr LD dot(const PDD &a, const PDD &b) { // ??
    return a.x * b.x + a.y * b.y;
}

constexpr LD cross(const PDD &a, const PDD &b) { // ??
    return a.x * b.y - b.x * a.y;
}

// ??????
constexpr LD get_length(const PDD &a) {
    return sqrt(dot(a, a));
}

// ??????
constexpr LD get_angle(const PDD &a, const PDD &b) {
    return atan2(fabs(cross(a, b)), dot(a, b));
}

// ?????????????????
constexpr LD area(const PDD &a, const PDD &b, const PDD &c) {
    return cross(b - a, c - a);
}

// A???**???**??angle?????
constexpr PDD rotate(const PDD &a, LD angle) {
    return PDD{a.x * cos(angle) + a.y * sin(angle),
               -a.x * sin(angle) + a.y * cos(angle)};
}

// ???p+vt, q+wt???
// cross(v,w)==0 ??????????????????????
constexpr PDD get_line_inter(const PDD &p, const PDD &v, const PDD &q, const PDD &w) {
    PDD u = p - q;
    LD t = cross(w, u) / cross(v, w);
    return p + v * t;
}

// ?p; ???a, b????
// ???????
constexpr LD dis2line(const PDD &p, const PDD &a, const PDD &b) {
    PDD v1 = b - a, v2 = p - a;
    return fabs(cross(v1, v2) / get_length(v1));
}

// ???????
constexpr LD dis2seg(const PDD &p, const PDD &a, const PDD &b) {
    if (a == b) return get_length(p - a);
    PDD v1 = b - a, v2 = p - a, v3 = p - b;
    if (sign(dot(v1, v2)) < 0) return get_length(v2);
    if (sign(dot(v1, v3)) > 0) return get_length(v3);
    return dis2line(p, a, b);
}

// ????????
constexpr PDD get_line_proj(const PDD &p, const PDD &a, const PDD &b) {
    PDD v = b - a;
    return a + v * (dot(v, p - a) / dot(v, v));
}

// ???????
constexpr bool on_seg(const PDD &p, const PDD &a, const PDD &b) {
    return sign(cross(p - a, p - b)) == 0 && sign(dot(p - a, p - b)) <= 0;
}

// ?????????
constexpr bool seg_inter(const PDD &a1, const PDD &a2, const PDD &b1, const PDD &b2) {
    LD c1 = cross(a2 - a1, b1 - a1), c2 = cross(a2 - a1, b2 - a1);
    LD c3 = cross(b2 - b1, a1 - b1), c4 = cross(b2 - b1, a2 - b1);
    // ?if?????????????if???????????
    if (!sign(c1) && !sign(c2) && !sign(c3) && !sign(c4)) {
        bool f1 = on_seg(b1, a1, a2);
        bool f2 = on_seg(b2, a1, a2);
        bool f3 = on_seg(a1, b1, b2);
        bool f4 = on_seg(a2, b1, b2);
        bool f = (f1 | f2 | f3 | f4);
        return f;
    }
    return (sign(c1) * sign(c2) < 0 && sign(c3) * sign(c4) < 0);
}


// ??**??**???????????
LD polygon_area(vector<PDD> p) {
    LD s = 0;
    for (int i = 1; i + 1 < int(p.size()); ++i)
        s += cross(p[i] - p[0], p[i + 1] - p[i]);
    return s / 2;
}

// ???????flag=1????????????????????R=-1
constexpr pair<PDD, LD> circle_three(const PDD &A, const PDD &B, const PDD &C, const bool flag = 1) {
    LD x = get_length(A - B);
    LD y = get_length(B - C);
    LD z = get_length(C - A);
    if (flag) {
        if (sign(x * x + y * y - z * z) <= 0 || sign(x * x + z * z - y * y) <= 0 || sign(y * y + z * z - x * x) <= 0) {
            return {PDD{}, -1};
        }
    }
    LD p = (x + y + z) / 2;
    LD s = sqrt(p * (p - x) * (p - y) * (p - z));
    LD R = x * y * z / (s * 4);
    auto F = [&](LD a1, LD a2, LD a3, LD b1, LD b2, LD b3, LD c1, LD c2, LD c3) -> LD {
        return a1 * b2 * c3 + b1 * c2 * a3 + c1 * a2 * b3 - a3 * b2 * c1 - b3 * c2 * a1 - c3 * a2 * b1;
    };
    LD X =
        F(
            1, 1, 1,
            dot(A, A), dot(B, B), dot(C, C),
            A.y, B.y, C.y
        ) /
        F(
            1, 1, 1,
            A.x, B.x, C.x,
            A.y, B.y, C.y
        );
    LD Y =
        F(
            1, 1, 1,
            A.x, B.x, C.x,
            dot(A, A), dot(B, B), dot(C, C)
        ) /
        F(
            1, 1, 1,
            A.x, B.x, C.x,
            A.y, B.y, C.y
        );
    return {PDD{X, Y} / 2, R};
}

struct Main {
    static constexpr PDD ZERO = PDD{0., 0.};
    int n, K;
    vector<int> f;
    vector<PDD> a, b, vert; // a[i] + f[K] * b[i]
    vector<LD> base;
    void main() {
        cin >> n >> K;
        f.assign(n, 0);
        for (auto &x : f) cin >> x;
        a.assign(n, ZERO);
        b.assign(n, ZERO);
        for (int t = 0; t < n; ++t) {
            for (int s = 0; s < n; ++s) {
                const LD angle = -pi * 2 * s * t / n;
                const PDD v = {cos(angle), sin(angle)};
                dbg(s, t, v);
                if (s == K)
                    b[t] = std::move(v);
                else
                    a[t] = a[t] + v * f[s];
            }
        }
        base.assign(n, 0.);
        vert.assign(n, ZERO);
        for (int i = 0; i < n; ++i) {
            const PDD tmp = get_line_proj(a[i], ZERO, b[i]);
            dbg(i, tmp);
            vert[i] = a[i] - tmp;
            const int sg = sign(dot(b[i], tmp));
            if (sg == -1) {
                base[i] = get_length(tmp);
            } else
                base[i] = -get_length(tmp);
            dbg(i, a[i]);
            dbg(i, b[i]);
            dbg(i, vert[i]);
            dbg(i, base[i]);
            assert(sign(dot(vert[i], b[i])) == 0);
        }
        LD l = 0., r = 4e6;
        for (int _case = 0; _case < 100; ++_case) {
            const LD mid = (l + r) / 2;
            if (check(mid))
                r = mid;
            else
                l = mid;
        }
        dbg(l, r);
        cout << fixed << setprecision(12) << l << "\n";
    }
    bool check(const LD radius) const {
        dbg(radius);
        LD L = -1e16, R = 1e16;
        for (int i = 0; i < n; ++i) {
            const LD sqr_len = radius * radius - dot(vert[i], vert[i]);
            if (sign(sqr_len) == -1) return 0;
            const LD len = sqrt(sqr_len);
            dbg(i, len);
            const LD l = base[i] - len;
            const LD r = base[i] + len;
#ifdef LOCAL
            const PDD _l = a[i] + l * b[i];
            dbg(_l, dot(_l, _l), radius * radius);
            // assert(dcmp(dot(_l, _l), radius * radius) == 0);
            const PDD _r = a[i] + r * b[i];
            dbg(_r, dot(_r, _r), radius * radius);
            // assert(dcmp(dot(_r, _r), radius * radius) == 0);
#endif
            L = fmax(L, l);
            R = fmin(R, r);
            dbg(i, l, r);
        }
        dbg(L, R);
        if (dcmp(L, R) == 1) return 0;
        if (dcmp(ceil(L), R) != 1)
            return 1;
        else
            return 0;
    }
};
int main() {
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    Main{}.main();
    return 0;
}
