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
typedef complex<double> p2;
constexpr auto pi = M_PI;
auto cross(p2 x, p2 y)
{
    return (conj(x) * y).imag();
}
auto rotate(p2 x, double angle)
{
    return x * polar(1.0, angle);
}
struct Main
{
    Main()
    {
        int n = 188;
        cout << n << '\n';
        for (int i = 1; i < 32; ++i)
        {
            cout << "add 32\n";
            for (int j = 0; j < 1024; j += 32)
                cout << j + i - 1 << ' ';
            cout << '\n';
            for (int j = 0; j < 1024; j += 32)
                cout << j + i << ' ';
            cout << '\n';
            for (int j = 0; j < 1024; j += 32)
                cout << j + i << ' ';
            cout << '\n';
        }
        for (int i = 32; i < 1024; i += 32)
        {
            cout << "add 32\n";
            for (int j = 0; j < 32; ++j)
                cout << i - 1 << ' ';
            cout << '\n';
            for (int j = 0; j < 32; ++j)
                cout << i + j << ' ';
            cout << '\n';
            for (int j = 0; j < 32; ++j)
                cout << i + j << ' ';
            cout << '\n';
        }

        for (int i = 0; i < 1024; i += 32)
        {
            cout << "mul 32\n";
            for (int j = 0; j < 32; ++j)
                cout << i + j << ' ';
            cout << '\n';
            for (int j = 0; j < 32; ++j)
                cout << 1024 + i + j << ' ';
            cout << '\n';
            for (int j = 0; j < 32; ++j)
                cout << 1024 + i + j << ' ';
            cout << '\n';
        }

        for (int i = 1; i < 32; ++i)
        {
            cout << "max 32\n";
            for (int j = 0; j < 1024; j += 32)
                cout << 1024 + j + i - 1 << ' ';
            cout << '\n';
            for (int j = 0; j < 1024; j += 32)
                cout << 1024 + j + i << ' ';
            cout << '\n';
            for (int j = 0; j < 1024; j += 32)
                cout << 1024 + j + i << ' ';
            cout << '\n';
        }
        for (int i = 32; i < 1024; i += 32)
        {
            cout << "max 32\n";
            for (int j = 0; j < 32; ++j)
                cout << 1024 + i - 1 << ' ';
            cout << '\n';
            for (int j = 0; j < 32; ++j)
                cout << 1024 + i + j << ' ';
            cout << '\n';
            for (int j = 0; j < 32; ++j)
                cout << 1024 + i + j << ' ';
            cout << '\n';
        }

        for (int i = 0; i < 1024; i += 32)
        {
            cout << "sub 32\n";
            for (int j = 0; j < 32; ++j)
                cout << i + j << ' ';
            cout << '\n';
            for (int j = 0; j < 32; ++j)
                cout << 1024 + i + j << ' ';
            cout << '\n';
            for (int j = 0; j < 32; ++j)
                cout << i + j << ' ';
            cout << '\n';
        }
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}
