#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int mod = 998244353;
inline ll quickpow(ll a, int b)
{
	ll res = 1;
	while (b)
	{
		if (b & 1)
			(res *= a) %= mod;
		(a *= a) %= mod;
		b >>= 1;
	}
	return res;
}
constexpr int N = (1 << 18) + 5;
int n, m, q;
ll dp[N][23];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m >> q;
	for (int j = 0; j < (1 << n); ++j)
		for (int i = 0; i <= n; ++i)
			dp[j][i] = 1;
	for (int i = 0; i < q; ++i)
	{
		int c, d, x;
		cin >> c >> d >> x;
		(dp[c][d] *= x) %= m;  
	}
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < (1 << n); ++j)
		{	
			if ((j >> i) & 1)
				continue;
			for (int k = 1; k <= n; ++k)
			{
				(dp[j | (1 << i)][k - 1] *= dp[j][k]) %= m;
				(dp[j][k - 1] *= dp[j | (1 << i)][k]) %= m;
			} 
		}
	for (int i = 0; i < (1 << n); ++i)
		cout << dp[i][0] << ' ';
	cout << '\n';
	return 0;
}