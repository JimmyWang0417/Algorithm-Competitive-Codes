#include <bits/stdc++.h>
using namespace std;

// #define LOCAL
#ifdef LOCAL
#define dbg(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define dbg(...) 42
#endif

using LL = long long;
#define all(x) (x).begin(), (x).end()

using ai2 = array<int, 2>;
using ai4 = array<int, 4>;

vector<ai2> ok;
vector<ai4> bit[16];
void init()
{
    for (int xi = 0; xi < 4; ++xi)
        for (int xj = 0; xj < 4; ++xj)
        {
            for (int yi = 0; yi < 4; ++yi)
                for (int yj = 0; yj < 4; ++yj)
                {
                    ai4 o = {xi ^ yi, xi ^ yj, xj ^ yi, xj ^ yj};
                    if (o[0] + 1 == o[1] && o[0] + 2 == o[2] && o[0] + 3 == o[3])
                    {
                        ok.push_back({xi * 4 + xj, yi * 4 + yj});
                        dbg("%d %d\n%d %d\n\n", xi, xj, yi, yj);
                    }
                }
        }
    for (int xi = 0; xi < 2; ++xi)
        for (int xj = 0; xj < 2; ++xj)
        {
            for (int yi = 0; yi < 2; ++yi)
                for (int yj = 0; yj < 2; ++yj)
                {
                    ai4 o = {xi ^ yi, xi ^ yj, xj ^ yi, xj ^ yj};
                    int x = 0;
                    for (auto &oo : o)
                        x = x * 2 + oo;
                    bit[x].push_back({xi, xj, yi, yj});
                }
        }
}

void fuck(auto &&a, auto &&b)
{
    const int n = (int)(a.size());
    for (int i = 0; i + 1 < n; ++i)
    {
        int ai = a[i] & (~3);
        int aj = a[i + 1] & (~3);
        if (ai != aj)
            continue;
        int x = (a[i] & 3) << 2;
        x |= (a[i + 1] & 3);
        ++b[x];
    }
}

vector<int> test(const ai4 &o, const int p)
{
    vector<int> r;
    for (int i = 0; i < p; ++i)
    {
        int x = 0;
        for (auto oo : o)
        {
            x = x * 2 + (oo >> i & 1);
        }
        if (bit[x].empty())
            return {};
        r.push_back(x);
    }
    return r;
}

LL NONE(auto &&a, auto &&b)
{
    array<int, 16> apack{}, bpack{};
    fuck(a, apack);
    fuck(b, bpack);
    LL ans = 0;
    for (auto &[x, y] : ok)
    {
        ans += 1ll * apack[x] * bpack[y];
    }
    return ans;
}

LL FUCK(auto &&a, auto &&b)
{
    // 01.11110
    map<ai2, int> mp;
    LL ans = 0;
    for (int p = 3; p <= 30; ++p)
    {
        const int mask = (1 << p) - 1;
        const int base = (1 << (p - 1)) - 2;
        ai4 o = {base, base + 1, base + 2, base + 3};
        mp.clear();
        for (int i = 1; i < b.size(); ++i)
        {
            if ((b[i - 1] & (~mask)) != (b[i] & (~mask)))
                continue;
            ++mp[{b[i - 1] & mask, b[i] & mask}];
        }
        for (int i = 0; i + 1 < a.size(); ++i)
        {
            const int ai = a[i] & mask;
            const int aj = a[i + 1] & mask;
            if ((a[i] & (~mask)) != (a[i + 1] & (~mask)))
                continue;
            const int bi = ai ^ o[0];
            const int bj = ai ^ o[1];
            if ((bi ^ aj) != o[2])
                continue;
            if ((bj ^ aj) != o[3])
                continue;
            ans += mp[{bi, bj}];
        }
    }
    return ans;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (auto &x : a)
        cin >> x;
    for (auto &x : b)
        cin >> x;
    LL ans = NONE(a, b);
    ans += FUCK(a, b);
    cout << ans << '\n';
}

void BF_TEST(const ai4 &a, int p = 5)
{
    auto r = test(a, p);
    dbg("ok=%d\n", r.size() != 0);
    if (p > 1)
    {
        for (int i = 0; i < p; ++i)
        {
            dbg("\tr[%d]=%d size=%llu\n", i, r[i], bit[r[i]].size());
        }
    }
    else
    {
        dbg("%d %d\n%d %d\n", a[0], a[1], a[2], a[3]);
        for (auto &[i, j, k, l] : bit[r[0]])
        {
            dbg("\ta|%d %d\n\tb|%d %d\n\n", i, j, k, l);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    /*
    BF_TEST(ai4{0b01101,0b01110,0b01111,0b10000}); // ok=0
    BF_TEST(ai4{0b01110,0b01111,0b10000,0b10001}); // ok=1
    BF_TEST(ai4{0b01111,0b10000,0b10001,0b10010}); // ok=0
    01110 01111
    10000 10001
    */
    BF_TEST(ai4{0b01110, 0b01111, 0b10000, 0b10001}); // ok=1
                                                      //	0011, 1010, 0101
                                                      //	BF_TEST(ai4{0,0,1,1},1);
                                                      //	BF_TEST(ai4{1,0,1,0},1);
                                                      //	BF_TEST(ai4{0,1,0,1},1);
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}

