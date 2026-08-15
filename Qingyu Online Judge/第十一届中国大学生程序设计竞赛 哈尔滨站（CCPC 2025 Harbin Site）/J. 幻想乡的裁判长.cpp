#include <bits/stdc++.h>
using namespace std;

// #define LOCAL
#ifdef LOCAL
#define dbg(...) fprintf(stderr,##__VA_ARGS__)
#else
#define dbg(...) 42
#endif

// 0-based-index, dx[i]=radius, which is [i to right]
// d0, i is center
// d1, between (i-1) and i is center
#define vi vector<int>
void manacher(auto&& s,vi& d0,vi& d1){
	const int& n=s.size();
#define WORK(X) d##X.assign(n,0); \
	for(int i=0,l=0,r=-1;i<n;++i){ \
	int k=(i>r)?0:min(d##X[l+r-i+X],r-i+1); \
	while(i-k-X>=0 && i+k<n && s[i-k-X]==s[i+k]) ++k; \
	d##X[i]=k--; if(i+k>r) l=i-k-X,r=i+k;}
	WORK(0); WORK(1);
#undef WORK
}
#undef vi

struct Node{
    int x,l,r;
    friend bool operator ==(const Node& x,const Node& y){
        return x.x==y.x;
    }
};

using ai2=array<int,2>;
constexpr int inf=1e9;

void solve(){
    int n; string s;
    cin>>n>>s;
    vector<int>tol(n,-1);
    for(int i=0;i<n;++i){
        if(s[i]=='v') tol[i]=i;
        else if(i) tol[i]=tol[i-1];
    }
    auto getl=[&](int x,int l)->int{
        if(tol[x]!=-1 && tol[x]>=l) return x-tol[x];
        return inf;
    };
    vector<int>tor(n,-1);
    for(int i=n-1;~i;--i){
        if(s[i]=='v') tor[i]=i;
        else if(i!=n-1) tor[i]=tor[i+1];
    }
    auto getr=[&](int x,int r)->int{
        if(tor[x]!=-1 && tor[x]<=r) return tor[x]-x;
        return inf;
    };
    vector<int>nxt(n,-1);
    for(int i=n-1;i>0;--i){
        if(s[i]!='o') nxt[i-1]=i;
        else nxt[i-1]=nxt[i];
    }
    auto fuck_next=[&](int x)->int{
        return nxt[x];
    };
    vector<int>cj(n+1);
    vector<ai2>mp(n*2+5,ai2{-1,-1});
    for(int i=1;i<=n;++i){
        int& x=cj[i];
        x=cj[i-1];
        if(s[i-1]=='v') ++x;
        else if(s[i-1]=='w') x+=2;
        if(s[i-1]=='o') continue;
        if(mp[x][0]==-1) mp[x][0]=i-1;
        mp[x][1]=i-1;
    }
    #define FUCK return {0,0}
    auto matching=[&](const Node& L,const Node& R)->ai2{
        dbg("\tmatch L=%d R=%d\n",L.r,R.l);
        const int& XL=L.x;
        const int& XR=R.x;
        if(XL<XR){
            const int cjr=cj[R.l]; // (R+1)-1
            if(mp[cjr+XL][0]!=-1){
                assert(mp[cjr+XL][1]>=R.l);
                return {L.l,mp[cjr+XL][1]};
            }
            int nwr=mp[cjr+XL-1][1];
            // assert(nwr!=-1 && nwr>R.l);
            if(nwr!=-1 && nwr>=R.l);
            else FUCK;
            int nwl=L.l;
            const int a=getr(nwl,L.r); // a's 'w'
            const int b=getl(nwr,R.l); // b's 'w'
            assert(a!=inf || b!=inf);
            dbg("\tXL=%d < XR=%d\n",XL,XR);
            dbg("\ta=%d b=%d nwl=%d nwr=%d\n",a,b,nwl,nwr);
            if(a<=b){
                return {nwl+a+1,nwr-a};
            }
            else{
                return {nwl+b+1,nwr-b-1};
            }
        }
        else{ // XL>XR
            const int cjl=cj[L.r+1];
            {
                int tmp=mp[cjl-XR][1];
                if(tmp!=-1){
                    tmp=fuck_next(tmp);
                    assert(tmp<=L.r);
                    return {tmp,R.r};
                }
            }
            int nwl=mp[cjl-XR+1][0];
            // assert(nwl!=-1);
            if(nwl==-1) FUCK;
            nwl=fuck_next(nwl);
            // assert(nwl!=-1 && nwl<L.r);
            if(nwl!=-1 && nwl<=L.r);
            else FUCK;
            int nwr=R.r;
            const int a=getr(nwl,L.r); // a's 'w'
            const int b=getl(nwr,R.l); // b's 'w'
            assert(a!=inf || b!=inf);
            dbg("\tXL=%d > XR=%d\n",XL,XR);
            dbg("\ta=%d b=%d nwl=%d nwr=%d\n",a,b,nwl,nwr);
            if(b<=a){
                return {nwl+b,nwr-b-1};
            }
            else{
                return {nwl+a+1,nwr-a-1};
            }
        }
    };
    vector<Node>a;
    {
        int x=0,l=0;
        for(int i=0;i<n;++i){
            if(s[i]=='o'){
                if(x) a.emplace_back(x,l,i-1);
                a.emplace_back(-1,i,i);
                l=i+1,x=0;
            }
            else if(s[i]=='v') ++x;
            else x+=2;
        }
        if(x) a.emplace_back(x,l,n-1);
    }
    const int m=a.size();
    vector<int>sum(m+1);
    for(int i=1;i<=m;++i){
        sum[i]=sum[i-1]+a[i-1].r-a[i-1].l+1;
    }
    auto calc=[&](int l,int r)->int{
        return sum[r+1]-sum[l];
    };
    #ifdef LOCAL
    for(auto& [x,l,r]:a){
        // dbg("[%d,%d] %d\n",l,r,x);
        dbg("%d ",x);
    }
    dbg("\n");
    #endif
    int ans=1,ansl=0,ansr=0;
    auto work=[&](int l,int r)->void{
        const int base=calc(l+1,r-1);
        if(base>ans){
            ans=base;
            ansl=a[l+1].l,ansr=a[r-1].r;
        }
        if(l<0 || r>=m) return;
        if(a[l].x==-1 || a[r].x==-1){
            assert(a[l].x!=-1 || a[r].x!=-1);
            return;
        }
        assert(a[l].x!=a[r].x);
        const auto [tl,tr]=matching(a[l],a[r]);
        dbg("\tmatch L=%d R=%d -> tl=%d tr=%d\n",
            a[l].r,a[r].l,tl,tr);
        const int x=tr-tl+1;
        if(x>ans){
            ans=x;
            ansl=tl,ansr=tr;
        }
    };
    vector<int>d0,d1;
    manacher(a,d0,d1);
    // i, i+d[i]-1
    for(int i=0;i<m;++i){
        work(i-d0[i],i+d0[i]);
        if(i){
            work(i-d1[i]-1,i+d1[i]);
        }
    }
    for(int i=ansl;i<=ansr;++i){
        cout<<s[i];
    }
    cout<<'\n';
}

signed main()
{
    #ifndef LOCAL
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    #endif
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
