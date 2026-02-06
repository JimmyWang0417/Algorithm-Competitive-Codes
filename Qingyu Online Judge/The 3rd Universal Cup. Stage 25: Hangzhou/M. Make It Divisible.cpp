#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 998244353;
mt19937 rnd((random_device())());
struct Main
{
    Main()
    {
        int n, k;
        cin >> n >> k;
        int g = 0;
        vector<int> a(n + 5), b(n + 5);
        int minn = INT_MAX;
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i];
            minn = min(minn, a[i]);
            if (i > 1)
                g = __gcd(g, abs(a[i] - a[i - 1]));
        }
        if (g == 0)
        {
            cout << k << " " << (i64)k * (k + 1) / 2 << endl;
            return;
        }
        vector<int> p;
        auto check = [&](int x)
        {
            if (!(x - minn >= 1 && x - minn <= k))
                return;
            stack<int> st;
            for (int i = 1; i <= n; ++i)
                b[i] = a[i] + (x - minn);
            for (int i = 1; i <= n; ++i)
            {
                while (!st.empty() && b[i] <= b[st.top()])
                {
                    if (b[st.top()] % b[i])
                        return;
                    st.pop();
                }
                if (!st.empty() && b[i] % b[st.top()])
                    return;
                st.push(i);
            }
            p.push_back(x - minn);
        };
        for (int i = 1; i * i <= g; ++i)
        {
            if (g % i == 0)
            {
                check(i);
                if (i * i != g)
                    check(g / i);
            }
        }
        i64 res = 0;
        for (int i : p)
            res += i;
        cout << p.size() << ' ' << res << '\n'; 
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}