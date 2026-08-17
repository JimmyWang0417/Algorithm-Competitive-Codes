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
template <typename T>
auto &operator<<(ostream &in, const vector<T> &rhs)
{
    for (auto i : rhs)
        in << i << ' ';
    return in;
}
struct Main
{
    int n;
    vector<int> a;
    Main()
    {
        cin >> n;
        a.resize(n + 1);
        for (int &i : a)
            cin >> i;
        string s;
        for (int i = 1; i <= n; ++i)
        {
            s.push_back('R');
            --a[i];
            while (a[i - 1] > 1)
            {
                s.append("LR");
                --a[i - 1], --a[i];
            }
            if (i < n && a[i] < 1)
            {
                cout << "Impossible\n";
                return;
            }
        }
        if (a[n])
        {
            cout << "Impossible\n";
            return;
        }
        cout << s + string(n, 'L') << '\n';
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
