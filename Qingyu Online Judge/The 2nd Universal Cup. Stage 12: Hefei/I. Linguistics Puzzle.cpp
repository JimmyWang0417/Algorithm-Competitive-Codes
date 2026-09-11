#include <bits/stdc++.h>
#include <cassert>
using namespace std;

// #define LOCAL
#ifdef LOCAL
#define dbg(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define dbg(...) 42
#endif

#define all(x) (x).begin(), (x).end()
using LL = long long;
using ai3 = array<int, 3>;

mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());

using u64 = unsigned long long;
const u64 mg = 0x9e3779b97f4a7c15;
void __calc_next_hash(u64 &x, const u64 y)
{
    x ^= std::hash<u64>{}(y) + mg + (x << 6) + (x >> 2);
}

template <class S>
struct Node
{
    int x;
    map<S, int> y, z;
    Node() : x(0), y({}), z({}) {}
    u64 hash() const
    {
        u64 seed = mg;
        __calc_next_hash(seed, this->x);
        vector<int> vec;
        for (auto [_, u] : this->y)
            vec.push_back(u);
        sort(all(vec));
        for (auto u : vec)
            __calc_next_hash(seed, u);
        vec.clear();
        for (auto [_, u] : this->z)
            vec.push_back(u);
        sort(all(vec));
        for (auto u : vec)
            __calc_next_hash(seed, u);
        return seed;
    }
};

struct Init
{
    array<unordered_map<u64, int>, 55> mps;
    void init()
    {
        for (int n = 2; n <= 52; ++n)
            calc(n);
        dbg("All OK !");
    }
    void calc(const int n)
    {
        auto &&mp = mps[n];
        vector<Node<int>> a(n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
            {
                const int x = i * j;
                const int p = x / n;
                const int q = x % n;
                if (!p)
                    ++a[q].x;
                else
                {
                    ++a[p].z[q];
                    ++a[q].y[p];
                }
            }

        for (int i = 0; i < n; ++i)
        {
            const u64 h = a[i].hash();
            auto it = mp.find(h);
            assert(it == mp.end());
            mp[h] = i;
        }
    }
} pre;

struct Main
{
    int n;
    string buf;
    void main()
    {
        cin >> n;
        vector<Node<char>> a(n);
        for (int i = 0; i < n * n; ++i)
        {
            cin >> buf;
            const int p = c2d(buf[0]);
            dbg("buf=%s p=%d\n", buf.c_str(), p);
            if (buf.size() == 1)
            {
                ++a[p].x;
                continue;
            }
            const int q = c2d(buf[1]);
            dbg("buf=%s p=%d\n", buf.c_str(), q);
            ++a[p].z[q];
            ++a[q].y[p];
        }
        vector<char> o;
        o.reserve(n);
        if (n <= 26)
        {
            for (int i = 0; i < n; ++i)
                o.push_back('a' + i);
        }
        else
        {
            for (int i = 0; i < 26; ++i)
                o.push_back('a' + i);
            for (int i = 0; i < n - 26; ++i)
                o.push_back('A' + i);
        }
        string ans(n, '*');
        for (const char c : o)
        {
            const int d = c2d(c);
            const u64 h = a[d].hash();
            ans[pre.mps[n][h]] = c;
        }
        cout << ans << "\n";
    }
    static int c2d(const char c)
    {
        if ('a' <= c && c <= 'z')
            return c - 'a';
        return c - 'A' + 26;
    }
};

signed main()
{
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    pre.init();
    int t;
    cin >> t;
    while (t--)
        Main{}.main();
    return 0;
}