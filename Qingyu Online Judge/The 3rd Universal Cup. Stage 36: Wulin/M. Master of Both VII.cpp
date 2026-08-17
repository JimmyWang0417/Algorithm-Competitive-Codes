#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 998244353;
constexpr double eps = 1e-7;
struct Main
{
    int n;
    vector<int> a;
    auto query(int l, int r)
    {
        cout << "? " << l << ' ' << r << endl;
        int x;
        cin >> x;
        return x;
    }
    auto answer(const vector<pair<int, int>> &p)
    {
        cout << '!';
        for (auto [x, y] : p)
            cout << ' ' << x << ' ' << y;
        cout << endl;
        bool x;
        cin >> x;
        return x;
    }
    Main()
    {
        cin >> n;
        a.resize(n + 5);
        for (int i = 3; i < n; ++i)
            a[i] = query(1, i);
        vector<pair<int, int>> p;
        stack<int> st;
        for (int i = 3; i <= n; ++i)
        {
            for (int j = 0; j < a[i] - a[i - 1]; ++j)
                st.push(i - 1);
            for (int j = 0; j < a[i - 1] - a[i]; ++j)
            {
                p.emplace_back(st.top(), i);
                st.pop();
            }
        }
        for (int i = 3; i < n; ++i)
            if (a[i] == 0)
                p.emplace_back(1, i);
        assert(answer(p));
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

