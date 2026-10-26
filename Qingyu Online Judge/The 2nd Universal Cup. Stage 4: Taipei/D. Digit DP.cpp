#include <bits/stdc++.h>
#define int __int128
#define VI vector<int>
#define VII vector<array<int,2>>

using namespace std;

template<class T>
inline void chmin(T &x,T y){x>y?x=y:0;}

template<class T>
inline void chmax(T &x,T y){x<y?x=y:0;}

constexpr int mo=998244353;

inline void red(int &x){x>=mo?x-=mo:0;}
inline int qpow(int x,int t=mo-2){
    int ret=1;
    for(;t;t>>=1,x=x*x%mo)if(t&1)ret=ret*x%mo;
    return ret;
}

const int inv6=qpow(6);

inline int read(){
    int x=0,f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar())f^=ch=='-';
    for(;isdigit(ch);ch=getchar())x=x*10+(ch^48);
    return f?x:-x;
}
inline void write(int x,char ch=0){
    if(x<0)putchar('-'),x=-x;
    if(!x)putchar('0');
    else{
        string o;
        do{
            o+=x%10^'0';
            x/=10;
        }while(x);
        reverse(o.begin(),o.end());
        printf("%s",o.c_str());
    }
    if(ch)putchar(ch);
}

struct matrix{
    static constexpr int mo=::mo;
    array<array<int,4>,4> a;
    int n=0,m=0;
    static inline void red(int &x){::red(x);}
    static inline int qpow(int x,int t=mo-2){
        return ::qpow(x,t);
    }
    matrix()=default;
    matrix(int _n,int _m,int v=0):n(_n),m(_m){
        for(int i=0;i<n;++i)for(int j=0;j<m;++j)a[i][j]=v;
    }
    matrix(int _n):matrix(_n,_n){
        for(int i=0;i<n;++i)a[i][i]=1;
    }
    // using array<array<int,4>,4>::array;
    array<int,4> &operator[](size_t i){return a[i];}
    const array<int,4> &operator[](size_t i)const{return a[i];}
    matrix operator*(const matrix &t)const{
        if(m!=t.n)return matrix();
        matrix ret(n,t.m);
        for(int i=0;i<n;++i)for(int k=0;k<m;++k){
            if(!a[i][k])continue;
            for(int j=0;j<t.m;++j){
                red(ret[i][j]+=a[i][k]*t[k][j]%mo);
            }
        }
        return ret;
    }
    matrix operator+(const matrix &t)const{
        if(n!=t.n||m!=t.m)return matrix();
        matrix ret=*this;
        for(int i=0;i<n;++i)for(int j=0;j<m;++j){
            red(ret[i][j]+=t[i][j]);
        }
        return ret;
    }
    matrix operator-(const matrix &t)const{
        if(n!=t.n||m!=t.m)return matrix();
        matrix ret=*this;
        for(int i=0;i<n;++i)for(int j=0;j<m;++j){
            red(ret[i][j]+=mo-t[i][j]);
        }
        return ret;
    }
};

const matrix I(4);

matrix getv(int x){
    matrix ret(4);
    ret[1][0]=x;
    ret[2][0]=x*x%mo;   ret[2][1]=2*x%mo;
    ret[3][0]=x*x*x%mo; ret[3][1]=3*x*x%mo; ret[3][2]=3*x%mo;
    return ret;
}

struct SegmentTree{
    struct node{
        array<signed,2> ch{};
        matrix s=matrix(4,1),lazy=I;
        int l,r;
        node(int x=0,int y=0,signed u=0,signed v=0){
            l=x,r=y,ch[0]=u,ch[1]=v;
        }
        signed &operator[](size_t i){return ch[i];}
    };
    vector<node> tr;
    vector<signed> rootlist;
    signed pool,root;
    SegmentTree(int l=0,int r=0){
        rootlist={root=pool=1};
        tr={node(),node(l,r)};
    }
    signed newnode(int l,int r,signed u=0,signed v=0){
        tr.push_back(node(l,r,u,v));
        return ++pool;
    }
    signed &lc(signed p){return tr[p][0];}
    signed &rc(signed p){return tr[p][1];}
    void pushup(signed p){
        auto &LL=tr[lc(p)],&RR=tr[rc(p)];
        tr[p].s=LL.s+RR.s;
    }
    void pushdown(signed p){
        matrix &tmp=tr[p].lazy;
        for(int i=0;i<2;++i){
            auto &ch=tr[tr[p][i]];
            ch.s=tmp*ch.s;
            ch.lazy=tmp*ch.lazy;
        }
        tmp=I;
    }
    void build(signed p,int l,int r,vector<matrix> &info){
        tr[p]=node(l,r);
        if(l==r){
            tr[p].s=info[l];
            return;
        }
        int mid=(l+r)>>1;
        lc(p)=newnode(l,mid);
        rc(p)=newnode(mid+1,r);
        build(lc(p),l,mid,info);
        build(rc(p),mid+1,r,info);
        pushup(p);
    }
    void modify(signed p,int L,int R,int d){
        int l=tr[p].l,r=tr[p].r;
        if(L<=l&&r<=R){
            tr[p].s=getv(d)*tr[p].s;
            tr[p].lazy=getv(d)*tr[p].lazy;
            return;
        }
        pushdown(p);
        int mid=(l+r)>>1;
        if(L<=mid)modify(lc(p),L,R,d);
        if(mid<R)modify(rc(p),L,R,d);
        pushup(p);
    }
    matrix query(signed p,int L,int R){
        int l=tr[p].l,r=tr[p].r;
        if(L<=l&&r<=R)return tr[p].s;
        if(R<l||r<L)return matrix(4,1);
        pushdown(p);
        int mid=(l+r)>>1;
        matrix ret=matrix(4,1);
        if(L<=mid)ret=ret+query(lc(p),L,R);
        if(mid<R)ret=ret+query(rc(p),L,R);
        return ret;
    }
}sgt;

int n,q;

matrix init=matrix(4,1);

VI a,typ,l,r,x;

vector<matrix> info;

matrix getdp(VI &digit){//记得reverse digit
    vector<matrix> dp[2];
    VI vis[2];
    vis[0]=vis[1]=VI(n+5,0);
    dp[0]=dp[1]=vector<matrix>(n+5,matrix(4,1));
    auto dfs=[&](int dep,int lim,auto &&self)->matrix{
        if(dep==-1)return init;
        if(vis[lim][dep])return dp[lim][dep];
        vis[lim][dep]=1;
        int up=lim?digit[dep]:1;
        for(int i=0;i<=up;++i){
            matrix tmp;
            if(i)tmp=getv(a[dep])*self(dep-1,lim&&(i==up),self);
            else tmp=self(dep-1,lim&&(i==up),self);
            dp[lim][dep]=dp[lim][dep]+tmp;
        }
        return dp[lim][dep];
    };
    return dfs(n-1,1,dfs);
}

int to_int(string x){
    reverse(x.begin(),x.end());
    int ret=0;
    for(int i=0,j=1;i<x.size();++i,j<<=1){
        ret=ret+j*(x[i]-'0');
    }
    return ret;
}

void solve(){
    n=read(),q=read();
    a.assign(n,0);
    for(int &x:a)x=read();
    typ=l=r=x=VI(q,0);
    for(int i=0;i<q;++i){
        typ[i]=read();
        string u,v;
        cin>>u>>v;
        if(typ[i]==1)x[i]=read();
        l[i]=to_int(u)-1;
        r[i]=to_int(v);
    }
    VI tmp={-1},ord;
    for(int i=0;i<q;++i){
        tmp.push_back(l[i]);
        tmp.push_back(r[i]);
    }
    sort(tmp.begin(),tmp.end());
    map<int,int> mp;
    int m=0;
    for(int i=0,j;i<tmp.size();i=j){
        j=i+1;
        while(j<tmp.size()&&tmp[i]==tmp[j])++j;
        ord.push_back(tmp[i]);
        mp[tmp[i]]=m++;
    }
    --m;
    info.assign(m+3,matrix(4,1));
    matrix prev(4,1);
    for(int i=1;i<=m;++i){
        VI digit(n+5,0);
        int x=ord[i];
        for(int j=0;j<n;++j){
            digit[j]=x&1;
            x>>=1;
        }
        auto tmp=getdp(digit);
        info[i]=tmp-prev;
        prev=tmp;
    }
    sgt=SegmentTree(1,m);
    sgt.build(1,1,m,info);
    auto trans=[&](matrix x)->int{
        int s1=x[1][0],s2=x[2][0],s3=x[3][0];
        int A=s1*s1%mo*s1%mo;
        int B=(mo-3)*s2%mo*s1%mo;
        int C=2*s3%mo;
        return (A+B+C)%mo*inv6%mo;
    };
    for(int i=0;i<q;++i){
        if(typ[i]==1){
            int u=mp[l[i]],v=mp[r[i]];
            sgt.modify(1,u+1,v,x[i]);
        }else{
            int u=mp[l[i]],v=mp[r[i]];
            auto mat=sgt.query(1,u+1,v);
            // printf("%lld",trans(mat));
            write(trans(mat),'\n');
        }
    }
}

signed main(){
    init[0][0]=1;
    // for(int cas=read();cas--;){
        solve();
    // }
}