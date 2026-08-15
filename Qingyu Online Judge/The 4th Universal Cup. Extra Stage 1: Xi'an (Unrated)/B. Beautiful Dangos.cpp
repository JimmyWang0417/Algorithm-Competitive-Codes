#include <bits/stdc++.h>
using namespace std;

// #define LOCAL
#ifdef LOCAL
#define debug(...) fprintf(stderr,##__VA_ARGS__)
#else
#define debug(...) 42
#endif

using LL=long long;
using ai2=array<int,2>;
using ai3=array<int,3>;
#define all(x) (x).begin(),(x).end()
#define allr(x) (x).rbegin(),(x).rend()

vector<int>s[3];
inline char d2c(const int& x){
    if(!x) return 'C';
    if(x==1) return 'W';
    return 'P';
}
void solve(){
    int n; cin>>n;
    string t; cin>>t;
    vector<int>a(n+2);
    a[0]=a[n+1]=-1;
    for(int i=0;i<3;++i){
        s[i].assign(n+1,0);
    }
    for(int i=1;i<=n;++i){
        const char& c=t[i-1];
        if(c=='C') a[i]=0;
        else if(c=='W') a[i]=1;
        else a[i]=2;
        for(int j=0;j<3;++j){
            s[j][i]=s[j][i-1];
        }
        ++s[a[i]][i];
    }
    for(int i=0;i<3;++i){
        if(s[i][n]>((n+1)/2)){
            cout<<"Impossible\n";
            return;
        }
    }
    int L=1,R=n;
    while(L<n){
        if(a[L+1]!=a[L]) ++L;
        else break;
    }
    if(L==n){
        cout<<"Beautiful\n";
        return;
    }
    while(R>1){
        if(a[R-1]!=a[R]) --R;
        else break;
    }
    debug("L=%d R=%d\n",L,R);
    int okl,okr;
    auto check=[&](const int& len)->bool{
        for(int r=len;r<=n;++r){
            const int l=r-len+1;
            if(l-1>L || r+1<R) continue;
            bool ok=1;
            for(int j=0;j<3;++j){
                const int cnt=s[j][r]-s[j][l-1];
                int sb=len;
                if(a[l-1]==j) --sb;
                if(a[r+1]==j) --sb;
                if(!sb || cnt>((sb+1)/2)) ok=0;
            }
            if(ok){
                okl=l,okr=r;
                return 1;
            }
        }
        return 0;
    };
    int l=2,r=n,mid,ans=-1;
    while(l<=r){
        mid=l+r>>1;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else l=mid+1;
    }
    assert(ans!=-1);
    check(ans);
    cout<<"Possible\n";
    cout<<okl<<' '<<okr<<'\n';
    vector<int>vis(n+1); int nw=0;
    vector<ai2>opt(3),cnt(3);
    for(int j=0;j<3;++j){
        opt[j]=ai2{s[j][okr]-s[j][okl-1],j};
        debug("%c c=%d\n",d2c(j),opt[j][0]);
    }
    debug("okl=%d okr=%d\n",okl,okr);
    vector<int>p{0,1,2};
    do{
        #ifdef LOCAL
        debug("\tpermutation: ");
        for(int i=0;i<p.size();++i) debug("%d",p[i]);
        debug("\n");
        #endif
        ++nw;
        for(int i=0;i<3;++i) cnt[i]=opt[p[i]];
        bool ok=1,f=0;
        debug("start new fuck\n");
        for(auto& [c,d]:cnt){
            if(!c) continue;
            int st=okl,ed=okr;
            if(a[okl-1]==d) ++st;
            if(a[okr+1]==d) --ed;
            debug("\t%c st=%d ed=%d c=%d\n",d2c(d),st,ed,c);
            int last=-1,cc=0;
            if(!f){
                for(int i=st;i<=ed;++i){
                    if(i-last==1) continue;
                    if(vis[i]==nw) continue;
                    vis[i]=nw;
                    t[i-1]=d2c(d);
                    last=i;
                    if(++cc==c) break;
                }
            }
            else{
                for(int i=ed;i>=st;--i){
                    if(last-i==1) continue;
                    if(vis[i]==nw) continue;
                    vis[i]=nw;
                    t[i-1]=d2c(d);
                    last=i;
                    if(++cc==c) break;
                }
            }
            if(cc!=c) ok=0;
            f^=1;
        }
        if(!ok) continue;
        cout<<t<<'\n';
        return;
    }while(next_permutation(all(p)));
    assert(0);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t; cin>>t;
    while(t--) solve();
    return 0;
}
