#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include <local/dbg.h>
#else
    #define dbg(...) 42
#endif

using LL = long long;

// clang-format off
#define ai(x) using ai##x = array<int, x>;
ai(2); ai(3); ai(4); ai(5); ai(6); ai(7); ai(8); ai(9); ai(10); ai(26);
#undef ai
// clang-format on

#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()
template <class T>
inline bool updmx(T &x, const T &y) { return x < y ? x = y, 1 : 0; }
template <class T>
inline bool updmn(T &x, const T &y) { return y < x ? x = y, 1 : 0; }
template <class T>
inline void clr(T &x) { T().swap(x); }
template <class T>
inline void sortuniq(T &x) {
    sort(all(x));
    x.erase(unique(all(x)), x.end());
}

mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());
LL rand(LL l, LL r) { return rng() % (r - l + 1) + l; }

template <typename T>
class fhqTreap {
private:
    struct Node {
        int l, r, siz;
        LL rnd;
        T val;
        LL sum;
        Node() {
            l = r = siz = 0;
            rnd = 0ll;
            val = T(0);
            sum = 0ll;
        }
        Node(int l_, int r_, int siz_, LL rnd_, T val_, LL sum_) {
            l = l_, r = r_, siz = siz_;
            rnd = rnd_;
            val = val_;
            sum = sum_;
        }
    };
    vector<Node> q;
    int root, rootX, rootY, rootZ;
    int New(T val) {
        Node new_node = Node(0, 0, 1, rng(), val, val);
        q.push_back(new_node);
        return q.size() - 1;
    }
    void Update(int id) {
        q[id].siz = q[q[id].l].siz + q[q[id].r].siz + 1;
        q[id].sum = q[q[id].l].sum + q[q[id].r].sum + q[id].val;
    }
    void Split(int id, T key, int &idX, int &idY) {
        if (id == 0) {
            idX = idY = 0;
            return;
        }
        if (q[id].val <= key) {
            idX = id;
            Split(q[id].r, key, q[id].r, idY);
        } else {
            idY = id;
            Split(q[id].l, key, idX, q[id].l);
        }
        Update(id);
    }
    int Merge(int l, int r) {
        if (l == 0 || r == 0) return l + r;
        if (q[l].rnd <= q[r].rnd) {
            q[r].l = Merge(l, q[r].l);
            Update(r);
            return r;
        } else {
            q[l].r = Merge(q[l].r, r);
            Update(l);
            return l;
        }
    }

public:
    fhqTreap() {
        init();
    }
    void init() {
        root = 0;
        q.clear();
        Node empty_node = Node();
        q.push_back(empty_node);
    }
    void insert(T val) {
        Split(root, val, rootX, rootY);
        root = Merge(Merge(rootX, New(val)), rootY);
    }
    void erase(T val) { // actually, 'extract' may be more precise
        Split(root, val, rootX, rootZ);
        Split(rootX, val - 1, rootX, rootY);
        rootY = Merge(q[rootY].l, q[rootY].r);
        root = Merge(Merge(rootX, rootY), rootZ);
    }
    T prev(T val) {
        Split(root, val - 1, rootX, rootY);
        int tmp = rootX;
        while (q[tmp].r) tmp = q[tmp].r;
        root = Merge(rootX, rootY);
        return q[tmp].val;
    }
    T next(T val) {
        Split(root, val, rootX, rootY);
        int tmp = rootY;
        while (q[tmp].l) tmp = q[tmp].l;
        root = Merge(rootX, rootY);
        return q[tmp].val;
    }
    int rank(T val) { // val's rank
        Split(root, val - 1, rootX, rootY);
        int ans = q[rootX].siz + 1;
        root = Merge(rootX, rootY);
        return ans;
    }
    T get(int rank) {
        int id = root;
        while (1) {
            //			printf("id:%d val:%d l:%d lsiz:%d r:%d rsiz:%d|rank:%d\n",id,q[id].val,q[id].l,q[q[id].l].siz,q[id].r,q[q[id].r].siz,rank);
            if (q[q[id].l].siz >= rank)
                id = q[id].l;
            else if (q[q[id].l].siz + 1 == rank)
                return q[id].val;
            else {
                rank -= (q[q[id].l].siz + 1);
                id = q[id].r;
            }
        }
    }
    int count(LL s) const {
        int id = root, cnt = 0;
        while (1) {
            if (q[id].sum <= s) {
                s -= q[id].sum;
                cnt += q[id].siz;
                break;
            } else if (q[q[id].l].sum + q[id].val > s) {
                id = q[id].l;
            } else {
                s -= q[q[id].l].sum + q[id].val;
                cnt += q[q[id].l].siz + 1;
                id = q[id].r;
            }
        }
        return cnt;
    }
    //	void output(){
    //		auto dfs=[&](auto self,int u)->void{
    //			if(!u) return;
    //			self(self,q[u].l);
    //			debug("%d|val=%d ls=%d rs=%d\n",u,q[u].val,q[u].l,q[u].r);
    //			self(self,q[u].r);
    //		};
    //		debug("output fhqTreap\n");
    //		dfs(dfs,root);
    //		debug("\n");
    //	}
};

struct Main {
    int n, Q;
    vector<int> a;
    fhqTreap<int> treap;
    LL sum_neg = 0;
    void main() {
        treap.init();
        cin >> n >> Q;
        a.assign(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            if (a[i] > 0) {
                treap.insert(a[i]);
            } else {
                sum_neg += a[i];
            }
        }
        for (int i, x; Q--;) {
            cin >> i >> x;
            if (a[i] > 0) {
                treap.erase(a[i]);
            } else {
                sum_neg -= a[i];
            }
            if ((a[i] = x) > 0) {
                treap.insert(a[i]);
            } else {
                sum_neg += a[i];
            }
            const int ans = treap.count(-sum_neg);
            cout << (ans + 1) << "\n";
        }
    }
};
int main() {
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    Main{}.main();
    return 0;
}