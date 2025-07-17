#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1024 + 5;
constexpr int mod = 998244353;
int tot;
char str[69][49];
inline void times2add1()
{
	sprintf(str[tot], "POP %d GOTO %d; PUSH %d GOTO %d\n", tot, tot + 1, tot, 1);
	sprintf(str[++tot], "HALT; PUSH 100 GOTO 1\n");
}
inline void add2()
{
	sprintf(str[tot], "POP %d GOTO %d; PUSH %d GOTO %d\n", tot, tot + 1, tot, tot);
	sprintf(str[++tot], "HALT; PUSH 100 GOTO 1\n");
}
inline void dfs(int k)
{
	if (k == 1)
	{
		sprintf(str[tot = 1], "HALT; PUSH 100 GOTO 1\n");
		return;
	}
	if ((k - 1) / 2 % 2)
	{
		dfs((k - 1) / 2);
		times2add1();
	}
	else
	{
		dfs((k - 3) / 2);
		times2add1();
		add2();
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int k;
	cin >> k;
	dfs(k);
	cout << tot << '\n';
	for (int i = 1; i <= tot; ++i)
		cout << str[i];
	return 0;
}