#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
const int MAX_BITS = 18;
const int N = 1 << MAX_BITS;

int phi[N + 5], prime[N + 5], tot;
bool is_prime[N + 5];

// 1. 线性筛求欧拉函数
void init_phi(int n) {
    fill(is_prime, is_prime + n + 1, true);
    is_prime[0] = is_prime[1] = false;
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            prime[++tot] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= tot && i * prime[j] <= n; j++) {
            is_prime[i * prime[j]] = false;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
}

// 快速幂（求逆元和 2 的 cnt0 次方）
long long qpow(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

// 2. 快速沃尔什变换 (FWT - 或卷积)
// flag = 1 为正变换，flag = -1 为逆变换
void fwt_or(long long *a, int flag) {
    for (int len = 1; len < N; len <<= 1) {
        for (int i = 0; i < N; i += (len << 1)) {
            for (int j = 0; j < len; j++) {
                if (flag == 1) {
                    a[i + j + len] = (a[i + j + len] + a[i + j]) % MOD;
                } else {
                    a[i + j + len] = (a[i + j + len] - a[i + j] + MOD) % MOD;
                }
            }
        }
    }
}

long long f[MAX_BITS + 1][N], g[MAX_BITS + 1][N];
int popcnt[N];
long long inv[MAX_BITS + 1];

int main() {
    // 开启 Fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init_phi(N + 1);

    // 预处理 1 到 18 的逆元，用于多项式 exp 计算
    for (int i = 1; i <= MAX_BITS; i++) {
        inv[i] = qpow(i, MOD - 2);
    }
    // 预处理 popcount
    for (int i = 0; i < N; i++) {
        popcnt[i] = __builtin_popcount(i);
    }

    int n;
    if (!(cin >> n)) return 0;

    int cnt0 = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        // 特判 0，不参与 FWT，最后直接乘 2^cnt0
        if (x == 0) {
            cnt0++;
        } else {
            f[popcnt[x]][x]++;
        }
    }

    // 3. 占位多项式：对每一层分别做 FWT(OR) 正变换
    for (int i = 1; i <= MAX_BITS; i++) {
        fwt_or(f[i], 1);
    }

    // 4. 在 FWT 的点值表示下，逐位进行多项式 exp
    for (int S = 0; S < N; S++) {
        g[0][S] = 1; // exp 的常数项为 1
        for (int i = 1; i <= MAX_BITS; i++) {
            long long sum = 0;
            // 利用递推式：g_i = (1/i) * sum_{j=1}^{i} (j * f_j * g_{i-j})
            for (int j = 1; j <= i; j++) {
                sum = (sum + j * f[j][S] % MOD * g[i - j][S]) % MOD;
            }
            g[i][S] = sum * inv[i] % MOD;
        }
    }

    // 5. 对每一层做 FWT(OR) 逆变换还原
    for (int i = 1; i <= MAX_BITS; i++) {
        fwt_or(g[i], -1);
    }

    // 6. 统计答案
    long long ans = 0;
    for (int S = 0; S < N; S++) {
        // 合法子集的项必定在 popcnt 对应的层上
        if (g[popcnt[S]][S] > 0) {
            ans = (ans + g[popcnt[S]][S] * phi[S + 1]) % MOD;
        }
    }

    // 乘上 0 的贡献
    long long pow2 = qpow(2, cnt0);
    ans = ans * pow2 % MOD;

    cout << ans << "\n";

    return 0;
}