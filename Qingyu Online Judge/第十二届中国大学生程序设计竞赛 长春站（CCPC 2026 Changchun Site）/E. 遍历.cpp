#include <bits/stdc++.h>
#define VI vector<int>
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar())f^=ch=='-';
    for(;isdigit(ch);ch=getchar())x=x*10+(ch^48);
    return f?x:-x;
}

int n,a,b,c;

void func1(){
    puts("7 4");
    puts("4 1");
    puts("1 6");
    puts("1 8");
    puts("8 3");
    puts("8 5");
    puts("5 2");
    for(int i=9;i<=n;++i){
        if(i&1)printf("4 %d\n",i);
        else printf("1 %d\n",i);
    }
}

void func2(){
    puts("5 1");
    puts("3 1");
    puts("7 1");
    puts("3 6");
    puts("7 4");
    puts("7 2");
    for(int i=8;i<=n;++i){
        if(i&1)printf("1 %d\n",i);
        else printf("5 %d\n",i);
    }
}

void func3(){
    puts("1 3");
    puts("1 4");
    puts("4 2");
    for(int i=5;i<=n;++i){
        if(i&1)printf("3 %d\n",i);
        else printf("1 %d\n",i);
    }
}

void func4(){
    puts("1 3");
    puts("1 4");
    puts("4 2");
    for(int i=3;i<=b;++i){
        printf("2 %d\n",i+2);
    }
    for(int i=1;i+b+2<=n;++i){
        if(i&1){
            printf("4 %d\n",i+b+2);
        }else{
            printf("2 %d\n",i+b+2);
        }
    }
}

void func5(){
    puts("1 4");
    puts("1 6");
    puts("3 6");
    puts("5 6");
    puts("2 5");
    for(int i=7;i<=n;++i){
        if(i&1)printf("2 %d\n",i);
        else printf("5 %d\n",i);
    }
}

void solve(){
    n=read(),a=read(),b=read(),c=read();
    if(a==0&&c==0){
        puts("-1");
        return;
    }
    if(a==0){
        if(b==0)func1();
        else if(b==1)func2();
        else if(b==2)func3();
        else func4();
    }else{
        if(!b){
            if(a==1){
                func5();
            }else{
                for(int i=1;i<=a;++i){
                    printf("%d %d\n",i,i+1);
                }
                int x=a-1,y=a;
                for(int i=1;i+1+a<=n;++i){
                    if(i&1)printf("%d %d\n",x,i+1+a);
                    else printf("%d %d\n",y,i+1+a);
                }
            }
        }else{
            for(int i=1;i<=a;++i){
                printf("%d %d\n",i,i+1);
            }
            int x=a,y=a+1;
            for(int i=1+a+1;i<=1+a+b;++i){
                printf("%d %d\n",x,i);
            }
            for(int i=1;i+a+b+1<=n;++i){
                if(i&1)printf("%d %d\n",i+a+b+1,y);
                else printf("%d %d\n",i+a+b+1,x);
            }
        }
    }
    for(int i=1;i<=n;++i)printf("%d ",i);
    puts("");
}

signed main(){
    for(int cas=read();cas--;)solve();
}

/*
3
8 0 7 0
8 7 0 0
8 2 2 3
*/
