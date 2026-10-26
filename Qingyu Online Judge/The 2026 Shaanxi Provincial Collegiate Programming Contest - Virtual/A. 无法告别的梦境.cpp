#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar())f^=ch=='-';
    for(;isdigit(ch);ch=getchar())x=x*10+(ch^48);
    return f?x:-x;
}

const int N=2e5+5;

int a[N],d1[N],d2[N],n,q,k,sumd1[N],sumd2[N];

int sgn(int a,int h){
    if(h<=a)return 1;
    h-=a;
    return (h-1)/k+2;
}

signed main(){
    n=read(),k=read(),q=read();
    for(int i=1;i<=n;++i){
        a[i]=read();
        if(i>1){
            if(a[i-1]<a[i])d1[i]=1;
            if(a[i-1]>a[i])d2[i]=1;
        }
        sumd1[i]=sumd1[i-1]+d1[i];
        sumd2[i]=sumd2[i-1]+d2[i];
        //d1 -> -1, d2 -> +1
    }
    for(int i=1;i<=q;++i){
        int A=read(),C=read(),B=read(),D=read();
        C=sgn(a[A],C),D=sgn(a[B],D);
        //(A,C),(B,D)
        if(A>B){
            swap(A,B);
            swap(C,D);
        }
        int bas1=B-A,bas2,bas3=labs(C-D);
        if(C<=D)bas2=sumd2[B]-sumd2[A];
        else bas2=sumd1[B]-sumd1[A];
        bas3=max(0ll,bas3-bas2);
        printf("%lld\n",bas1+bas3);
    }
}
