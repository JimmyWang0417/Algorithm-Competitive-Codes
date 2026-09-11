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

template <class S>
inline bool updmx(S &x, const S y)
{
    if (x < y)
    {
        x = y;
        return 1;
    }
    return 0;
}

struct Main
{
    using AAA = array<array<array<array<int, 6>, 6>, 6>, 6>;
    int n;
    AAA dp, nw;
    void main()
    {
        cin >> n;
        clr(dp), clr(nw);
        dp[0][0][0][0] = 0;
        for (int _t = 0; _t < n; ++_t)
        {
            const int x = []() -> int
            {
                int x;
                cin >> x;
                return x;
            }();
            for (int f1 = 0; f1 <= 5; ++f1)
                for (int l1 = 0; l1 <= 5; ++l1)
                {
                    if (f1 == 0 && l1 != 0)
                        continue;
                    for (int f2 = 0; f2 <= 5; ++f2)
                        for (int l2 = 0; l2 <= 5; ++l2)
                        {
                            if (f2 == 0 && l2 != 0)
                                continue;
                            const int d = dp[f1][l1][f2][l2];
                            if (d == -1)
                                continue;
                            { // get to 1
                                int nf1 = f1, nf2 = f2, nl2 = l2, nl1 = l1;
                                nl1 = x;
                                int add = 0;
                                if (f1 == 0)
                                    nf1 = x, add = 0;
                                else
                                    add = calc(l1, x);
                                updmx(nw[nf1][nl1][nf2][nl2], d + add);
                            }
                            { // get to 2
                                int nf1 = f1, nf2 = f2, nl2 = l2, nl1 = l1;
                                nl2 = x;
                                int add = 0;
                                if (f2 == 0)
                                    nf2 = x, add = 0;
                                else
                                    add = calc(l2, x);
                                updmx(nw[nf1][nl1][nf2][nl2], d + add);
                            }
                        }
                }
            swap(dp, nw);
            clr(nw);
        }
        int ans = 0;
        for (int f1 = 0; f1 <= 5; ++f1)
            for (int l1 = 0; l1 <= 5; ++l1)
            {
                if (f1 == 0 && l1 != 0)
                    continue;
                for (int f2 = 0; f2 <= 5; ++f2)
                    for (int l2 = 0; l2 <= 5; ++l2)
                    {
                        if (f2 == 0 && l2 != 0)
                            continue;
                        const int d = dp[f1][l1][f2][l2];
                        if (d == -1)
                            continue;
                        int add = calc(l1, f2);
                        if (f1 == 0 || f2 == 0)
                            add = 0;
                        updmx(ans, dp[f1][l1][f2][l2] + add);
                    }
            }
        cout << (ans + n) << "\n";
    }
    int calc(const int x, const int y) const
    {
        int res = y - x;
        if (res < 0)
            res += 5;
        return res;
    }
    void clr(AAA &x)
    {
        for (int i = 0; i <= 5; ++i)
            for (int j = 0; j <= 5; ++j)
                for (int k = 0; k <= 5; ++k)
                    for (int l = 0; l <= 5; ++l)
                        x[i][j][k][l] = -1;
    }
};

signed main()
{
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int T = 1;
    while (T--)
        Main{}.main();
    return 0;
}