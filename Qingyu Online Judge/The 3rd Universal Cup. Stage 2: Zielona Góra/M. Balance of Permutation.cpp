#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 35;
int n, b;
int p[N];
bool mark[N];
__int128 dp[N][N][N * N];
inline __int128 solve(int beg)
{
	int res = 0;
	int pi = 0;
	for (int i = 1; i <= beg; ++i)
	{
		pi += (p[i] >= beg);
		res += max(0, min(p[i], beg) - i);
	}
	memset(dp, 0, sizeof(dp));
	dp[beg - 1][pi][res] = 1;
	for (int i = beg; i <= n; ++i)
	{
		for (int j = pi; j < i; ++j)
			for (int k = 0; k <= b; ++k)
			{
				if (!dp[i - 1][j][k])
					continue;
				if (mark[i])
				{
					dp[i][j - 1][k + j - 1] += dp[i - 1][j][k] * j;
					dp[i][j][k + j] += dp[i - 1][j][k];
				}
				else
				{
					if (j > 0)
						dp[i][j - 1][k + j - 1] += dp[i - 1][j][k] * j * (j - pi);
					dp[i][j][k + j] += dp[i - 1][j][k] * (j - pi);
					
					dp[i][j][k + j] += dp[i - 1][j][k];
					
					dp[i][j][k + j] += dp[i - 1][j][k] * j;
					dp[i][j + 1][k + j + 1] += dp[i - 1][j][k];
				}
			}
		pi -= mark[i];
	}
	return dp[n][0][b];
}
template<typename T> void read(T& x) {
	x = 0;
	char ch;
	while (ch = getchar(), isdigit(ch))
		x = x * 10 + ch - '0';	
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	__int128 k_th;
	read(n), read(b), read(k_th);
	b >>= 1;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			if (mark[j])
				continue;
			mark[p[i] = j] = true;
			auto res = solve(i + 1);
			if (res >= k_th)
				break;
			mark[j] = false;
			k_th -= res;
		}
	}
	for (int i = 1; i <= n; ++i)
		cout << p[i] << ' ';
	cout << '\n';
	return 0;
}