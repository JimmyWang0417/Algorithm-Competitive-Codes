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
struct Main1
{
    int n, k;
    Main1()
    {
        cin >> n >> k;
        vector<bool> a(n + 1);
        for (int i = 0; i < k; ++i)
        {
            int x;
            cin >> x;
            a[x] = true;
        }
        stack<int> st;
        int pos = -1;
        for (int i = 1; i <= n; ++i)
        {
            if (a[i])
                st.push(i);
            else if (!st.empty())
                st.pop();
            else
                pos = i;
        }
        a[pos] = true;
        for (int i = 1; i <= n; ++i)
            if (a[i])
                cout << i << ' ';
        cout << '\n';
    }
};
struct Main2
{
    int n, k;
    Main2()
    {
        cin >> n >> k;
        vector<bool> a(n + 1);
        for (int i = 0; i <= k; ++i)
        {
            int x;
            cin >> x;
            a[x] = true;
        }
        stack<int> st;
        for (int i = 1; i <= n; ++i)
        {
            if (a[i])
                st.push(i);
            else if (!st.empty())
                st.pop();
        }
        while (st.size() > 1)
            st.pop();
        cout << st.top() << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    string _;
    cin >> _;
    int T = 1;
    cin >> T;
    while (T--)
        if (_ == "Alice")
            Main1();
        else
            Main2();
    return 0;
}

