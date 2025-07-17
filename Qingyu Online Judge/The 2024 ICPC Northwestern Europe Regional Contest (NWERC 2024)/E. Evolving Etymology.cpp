#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 1e5 + 5;
inline ll quickpow(ll a, ll b, int p) 
{
	ll res = 1;
	while (b) 
	{
		if (b & 1) 
			res = res * a % p;
		a = a * a % p; b >>= 1;
	}
	return res;
}
inline void _main()
{
	int n;
	ll k;
	cin >> n >> k;
	string s;
	cin >> s;
	ll jump = quickpow(2, k, n);
	for (int i = 0; i < n; i++)
		cout << s[jump * i % n];
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