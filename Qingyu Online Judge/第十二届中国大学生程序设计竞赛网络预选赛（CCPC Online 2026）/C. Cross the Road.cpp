#include <bits/stdc++.h>
#include <cassert>
using namespace std;

#ifdef LOCAL
    #define dbg(...) fprintf(stderr, ##__VA_ARGS__)
#else
    #define dbg(...) 42
#endif

#define all(x) (x).begin(), (x).end()
using LL = long long;

using LD = long double;
constexpr LD eps = 1e-12;
constexpr LD pi = numbers::pi_v<LD>;
constexpr int sign(const LD x) {
    if (fabs(x) < eps) return 0;
    return x > LD(0.) ? 1 : -1;
}
constexpr int dcmp(const LD x, const LD y) {
    return sign(x - y);
}

using PDD = pair<LD, LD>;
#define x first
#define y second

constexpr PDD operator+(const PDD &a, const PDD &b) {
    return PDD{a.x + b.x, a.y + b.y};
}
constexpr PDD operator-(const PDD &a, const PDD &b) {
    return PDD{a.x - b.x, a.y - b.y};
}
constexpr PDD operator*(const LD k, const PDD &a) {
    return PDD{k * a.x, k * a.y};
}
constexpr PDD operator*(const PDD &a, const LD k) {
    return PDD{k * a.x, k * a.y};
}
constexpr PDD operator/(const PDD &a, const LD k) {
    return PDD{a.x / k, a.y / k};
}
constexpr bool operator==(const PDD &a, const PDD &b) {
    return !dcmp(a.x, b.x) && !dcmp(a.y, b.y);
}

constexpr LD dot(const PDD &a, const PDD &b) {
    return a.x * b.x + a.y * b.y;
}
constexpr LD cross(const PDD &a, const PDD &b) {
    return a.x * b.y - b.x * a.y;
}

constexpr LD get_length(const PDD &a) {
    return sqrt(dot(a, a));
}
constexpr LD get_angle(const PDD &a, const PDD &b) {
    return atan2(fabs(cross(a, b)), dot(a, b));
}
constexpr bool on_seg(const PDD &p, const PDD &a, const PDD &b) {
    return sign(cross(p - a, p - b)) == 0 && sign(dot(p - a, p - b)) == 0;
}
constexpr bool seg_inter(const PDD &a1, const PDD &a2, const PDD &b1, const PDD &b2) {
    LD c1 = cross(a2 - a1, b1 - a1), c2 = cross(a2 - a1, b2 - a1);
    LD c3 = cross(b2 - b1, a1 - b1), c4 = cross(b2 - b1, a2 - b1);
    return (sign(c1) * sign(c2) < 0 && sign(c3) * sign(c4) < 0);
}

inline void read(LD &x) {
    int _x;
    cin >> _x;
    x = _x;
}
inline LD solve_eq(LD a, LD b, LD c) {
    if (sign(a) == 0) {
        if (sign(b))
            return -c / b;
        else {
            return LD(-1.);
        }
    }
    c /= a;
    b /= a;
    a = LD(1.);
    LD delta = b * b - a * c * 4;
    dbg("a = %.3Lf b = %.3Lf c = %.3Lf delta = %.3Lf\n",
        a, b, c, delta);
    if (sign(delta) == -1) return LD(-1.);
    delta = fmax(delta, LD(0.));
    const LD sqrt_delta = sqrt(delta);
    dbg("sqrt_delta = %.3Lf\n", sqrt_delta);
    const LD res1 = (-sqrt_delta - b) / a / LD(2.);
    const LD res2 = (sqrt_delta - b) / a / LD(2.);
    dbg("res1 = %.3Lf\n", res1);
    dbg("res2 = %.3Lf\n", res2);
    const int s1 = sign(res1), s2 = sign(res2);
    if (s1 == -1 && s2 == -1)
        return LD(-1.);
    else if (s1 == -1)
        return res2;
    else if (s2 == -1)
        return res1;
    else
        return fmin(res1, res2);
}
struct Main {
    static constexpr LD inf = LD(1e9);
    LD w, x1, x2, yc, u, v;
    PDD st, ed;
    void main() {
        read(w);
        read(x1);
        read(x2);
        read(yc);
        read(u);
        read(v);
        st = PDD{x1, yc};
        ed = PDD{x2, yc};
        if (can_direct()) {
            const LD ans = w / v;
            cout << fixed << setprecision(12) << ans << "\n";
            return;
        }
        LD ans = inf;
        const LD base = (w - yc) / v;
        for (const auto p : {st, ed}) {
            const LD a = u * u - v * v;
            const LD b = u * p.x * LD(2.);
            const LD c = dot(p, p);
            const LD t = solve_eq(a, b, c);
            dbg("* t= %.3Lf\n", t);
            if (sign(t) == -1) continue;
            ans = fmin(ans, t);
        }
        assert(dcmp(ans, inf) == -1);
        ans += base;
        cout << fixed << setprecision(12) << ans << "\n";
    }
    bool can_direct() {
        PDD d = PDD{-u, v};
        const LD mul = w / v;
        const PDD p = d * mul;
#ifdef LOCAL
        dbg("d = {%.3Lf, %.3Lf} ", d.x, d.y);
        dbg("p = {%.3Lf, %.3Lf} ", p.x, p.y);
        dbg("st = {%.3Lf, %.3Lf} ", st.x, st.y);
        dbg("ed = {%.3Lf, %.3Lf} ", ed.x, ed.y);
        dbg("\n");
#endif
        if (seg_inter(PDD{LD(0.), LD(0.)}, p, st, ed))
            return 0;
        else
            return 1;
    }
};

int main() {
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int t;
    cin >> t;
    while (t--)
        Main{}.main();
    return 0;
}
