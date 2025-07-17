#include <bits/stdc++.h>
using namespace std;
constexpr int N = 3005;
int n, m;
char str[N];
bool g[N][N];
namespace subtask1
{
	inline void main()
	{
		for (int i = 0; i < n; ++i)
		{
			cin >> str;
			for (int j = 0; j < n; ++j)
				g[i][j] = (str[j] == '1');
		}
		int q = m - n - 3;
		for (int j = 0; j < n; ++j)
			for (int i = 0; i < q; ++i)
				g[n + i][j] = g[j][n + i] = (j >> i) & 1;
		int A = n + q, B = A + 1, C = B + 1;
		for (int i = 0; i < m; ++i)
			if (i != A && i != B)
				g[A][i] = g[i][A] = 1;
		for (int i = 0; i < n; ++i)
			g[C][i] = g[i][C] = 1;
		g[B][C] = g[C][B] = 1;
		g[B][n] = g[n][B] = 1;
		for (int i = 1; i < q; ++i)
			g[n + i - 1][n + i] = g[n + i][n + i - 1] = 1;
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < m; ++j)
				cout << g[i][j];
			cout << '\n';
		}
	}
}
namespace subtask2
{
	int deg[N];
	bool vis[N];
	int a[N], b[14];
	inline void main()
	{
		for (int i = 0; i < n; ++i)
		{
			cin >> str;
			for (int j = 0; j < n; ++j)
			{
				g[i][j] = (str[j] == '1');
				deg[i] += g[i][j];
			}
		}
		int A = 0, B = 0, C = 0;
		for (int i = 0; i < n; ++i)
			if (deg[i] == n - 2)
			{
				A = i;
				break;
			}
		for (int i = 0; i < n; ++i)
			if (!g[A][i] && i != A)
			{
				B = i;
				break;
			}
		for (int i = 0; i < n; ++i)
			if (g[B][i] && deg[i] == m + 2)
			{
				C = i;
				break;
			}
		int q = n - m - 3;
		vis[A] = vis[B] = vis[C] = true;
		for (int i = 0; i < n; ++i)
			if (g[C][i])
				vis[i] = true;
//		cout << endl;
		for (int i = 0, u = B; i < q; ++i)
		{
//			for (int j = 0; j < n; ++j)
//				cout << g[u][j];
//			cout << endl;
			for (int j = 0; j < n; ++j)
				if (g[u][j] && !vis[j])
				{
					vis[b[i] = u = j] = true;
					break;
				}
		}
		for (int i = 0; i < n; ++i)
			if (g[C][i] && i != A && i != B)
			{
				int u = 0;
				for (int j = 0; j < q; ++j)
					u |= g[i][b[j]] << j;
				a[u] = i;
			}
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < m; ++j)
				cout << g[a[i]][a[j]];
			cout << '\n';
		}
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m;
	if (n < m)
		subtask1::main();
	else
		subtask2::main();
	return 0;
}