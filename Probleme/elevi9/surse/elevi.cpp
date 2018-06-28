#include <fstream>
using namespace std;
ifstream f("elevi.in");
ofstream g("elevi.out");
int x[10005],n,p;

void citire(){
int i;
f>>p;
f>>n;
for(i=1;i<=n;i++)
    f>>x[i];
f.close();
}

int nrcif(int k){
int nr=0;
while(k){
    nr++;
    k/=10;
}
return nr;
}

int rez1(){
int s=0,i;
for(i=1;i<=n;i++)
    s+=nrcif(x[i]);
return s;
}

int inlocuire(int k){
int i,j,m=0,a[12],aux,p;
while(k){
    m++;
    a[m]=k%10;
    k/=10;
}
for(i=1;i<m;i++)
    for(j=i+1;j<=m;j++)
        if(a[i]<a[j]){
            aux=a[i];
            a[i]=a[j];
            a[j]=aux;
        }
p=1;k=0;
for(i=m;i>=1;i--){
    k=k+p*a[i];
    p*=10;
}
return k;
}

int rez2(){
int i,j,nr=0,aux;
for(i=1;i<=n;i++)
    x[i]=inlocuire(x[i]);
for(i=1;i<n;i++)
    for(j=i+1;j<=n;j++)
        if(x[i]>x[j]){
            aux=x[i];
            x[i]=x[j];
            x[j]=aux;
        }
nr=1;
for(i=2;i<=n;i++)
    if(x[i]!=x[i-1])
        nr++;
return nr;
}

int main()
{
    int r1,r2;
    citire();
    if(p==1){
        r1=rez1();
        g<<r1;
    }
    else{
        r2=rez2();
        g<<r2;
    }
    g.close();
    return 0;
}
