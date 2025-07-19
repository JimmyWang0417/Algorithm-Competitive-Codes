#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 105;
constexpr int mod = 998244353;
int n, L, R, a[N];
int f[N][N][N], g[N][N];
int sum[N];
template <typename T>
inline void ckmin(T &x, T y)
{
	if (x > y)
		x = y;
}
signed main() 
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> L >> R;
    for (int i = 1; i <= n; ++i)
    {
    	cin >> a[i];
    	sum[i] = sum[i - 1] + a[i];
	}
    memset(f, 0x3f, sizeof(f));
    memset(g, 0x3f, sizeof(g));
    for (int i = 1; i <= n; ++i)
    	f[i][i][1] = g[i][i] = 0;
    for (int len = 2; len <= n; ++len)
    	for (int l = 1, r; r = l + len - 1, r <= n; ++l)
    	{
    		for (int i = 1; i < R; ++i)
    			for (int j = l; j < r; ++j)
    				ckmin(f[l][r][i + 1], f[l][j][i] + g[j + 1][r]);
    		for (int i = L; i <= R; ++i)
    			ckmin(g[l][r], f[l][r][i] + sum[r] - sum[l - 1]);
    		ckmin(f[l][r][1], g[l][r]);
		}
	cout << (f[1][n][1] > INT_MAX / 4 ? 0 : f[1][n][1]) << '\n';
    return 0;
}