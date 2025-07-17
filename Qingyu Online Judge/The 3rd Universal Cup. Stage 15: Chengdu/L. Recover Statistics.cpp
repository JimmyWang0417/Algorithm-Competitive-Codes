#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef long long ll;
constexpr int N = 1e5 + 5;
constexpr int B = 500;
int a, b, c;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> a >> b >> c;
    cout << 100 << '\n';
    for (int i = 1; i <= 50; ++i)
        cout << a << ' ';
    for (int i = 51; i <= 95; ++i)
        cout << b << ' ';
    for (int i = 96; i <= 99; ++i)
        cout << c << ' ';
    cout << c + 1 << '\n';
    return 0;
}