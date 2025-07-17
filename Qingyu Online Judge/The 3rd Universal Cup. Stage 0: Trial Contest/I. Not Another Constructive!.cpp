#include <bits/stdc++.h>
using namespace std;
constexpr int N = 45, M = 2503;
typedef long long ll;
int n, m;
string s;
bitset<M> dp[N][M][N];
vector<tuple<int, int, int>> pre[N][M][N];
inline void _main()
{
	cin >> n >> m >> s;
	dp[n + 1][0][0][0] = 1;
	for (int i = n; i >= 1; --i)
	{
		for (int j = 0; j <= m + 1; ++j)
			for (int k = 0; k <= n - i; ++k)
			{
				if (s[i - 1] != 'N' && s[i - 1] != 'A' && s[i - 1] != 'C')
				{
					dp[i][j][k] |= dp[i + 1][j][k];
					pre[i][j][k].emplace_back(j, k, 0);
				}
				if (s[i - 1] == 'C' || s[i - 1] == '?')
				{
					dp[i][j][k + 1] |= dp[i + 1][j][k];
					pre[i][j][k + 1].emplace_back(j, k, 1);
				}
				if (s[i - 1] == 'A' || s[i - 1] == '?')
				{
					dp[i][min(j + k, m + 1)][k] |= dp[i + 1][j][k];
					pre[i][min(j + k, m + 1)][k].emplace_back(j, k, 2);
				}
				if (s[i - 1] == 'N' || s[i - 1] == '?')
				{
					dp[i][j][k] |= dp[i + 1][j][k] << j;
					pre[i][j][k].emplace_back(j, k, 3);
				}
			}
//		for (int j = 0; j <= m; ++j)
//			for (int k = 0; k <= n; ++k)
//				for (int l = 0; l <= m; ++l)
//					if (dp[i][j][k][l])
//						printf("%d %d %d %d\n", i, j, k, l);
	}
	int posj = -1, posk = -1;
	for (int i = 0; i <= m + 1; ++i)
	{
		for (int j = 0; j <= n; ++j)
		{
			if (dp[1][i][j][m])
			{
				posj = i;
				posk = j;
				break;
			}
		}
		if (posj != -1)
			break;
	}
	if (posj == -1)
	{
		cout << "-1\n";
		return;
	}
	for (int i = 1, j = posj, k = posk, l = m; i <= n; ++i)
	{
//		printf("%d %d %d %d\n", i, j, k, l);
		for (auto [a, b, c] : pre[i][j][k])
		{
			if (c <= 2 && dp[i + 1][a][b][l])
			{
				j = a;
				k = b;
				cout << (c == 0 ? (s[i - 1] == '?' ? 'B' : s[i - 1]) : (c == 1 ? 'C' : 'A'));
				break;
			}
			if (c == 3 && dp[i + 1][a][b][l - a])
			{
				j = a;
				k = b;
				l = l - a;
				cout << 'N';
				break;
			}
		}
	}
	cout << '\n';
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int test = 1;
//	cin >> test; 
	while (test--)
		_main();
	return 0;
}