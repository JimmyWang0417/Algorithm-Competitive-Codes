#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 3005;
constexpr int mod = 998244353;
struct Matrix
{
	ll g[49][49];
	Matrix(){ memset(g, 0, sizeof(g)); }
	inline Matrix operator*(const Matrix &rhs) const
	{
		Matrix res;
		for (int i = 0; i < 49; ++i)
			for (int k = 0; k < 49; ++k)
				for (int j = 0; j < 49; ++j)
					(res.g[i][j] += g[i][k] * rhs.g[k][j]) %= mod;
		return res;
	}
	inline Matrix operator^(int power)
	{
		Matrix res, a = (*this);
		for (int i = 0; i < 49; ++i)
			res.g[i][i] = 1;
		while (power)
		{
			if (power & 1)
				res = res * a;
			a = a * a;
			power >>= 1;
		}
		return res;
	}
	inline void print()
	{
		for (int i = 0; i < 49; ++i)
		{
			for (int j = 0; j < 49; ++j)
				cout << g[i][j] << ' ';
			cout << '\n';
		}
	}
};
Matrix power[37];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	Matrix base;
	for (int i = 0; i <= 6; ++i)
		for (int j = 0; j <= 6; ++j)
		{
			base.g[i * 7 + j][i * 7 + j] = 52 - (i < 6) - (j < 6);
			if (i < 6)
				base.g[i * 7 + j][(i + 1) * 7 + j] = 1;
			if (j < 6)
				base.g[i * 7 + j][i * 7 + (j + 1)] = 1;
		}
	power[0] = base;
	for (int i = 1; i <= 30; ++i)
		power[i] = power[i - 1] * power[i - 1];
	int T = 1;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		ll a[49], b[49];
		memset(a, 0, sizeof(a));
		a[0] = 1;
		for (int i = 0; i <= 30; ++i)
			if ((n >> i) & 1)
			{
				memset(b, 0, sizeof(b));
				for (int k = 0; k < 49; ++k)
					for (int j = 0; j < 49; ++j)
						(b[j] += a[k] * power[i].g[k][j]) %= mod;
				memcpy(a, b, sizeof(b));
			}
		cout << a[48] << '\n';
	}
	return 0;
} 