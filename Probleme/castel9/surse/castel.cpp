#include <fstream>
using namespace std;
ifstream f("castel.in");
ofstream g("castel.out");
int x[10005], n, v[10005], p;

void cit(){
int i;
f>>p;
f>>n;
for(i=1;i<=n;i++)
    f>>x[i];
f.close();
}

void ordonare(){
int i,j,aux;
for(i=1;i<n;i++)
    for(j=i+1;j<=n;j++)
        if(x[i]>x[j]){
            aux=x[i];
            x[i]=x[j];
            x[j]=aux;
        }
}

int nr(int k, int d){
int nr=0;
while(k%d==0){
    nr++;
    k/=d;
}
return nr;
}

int det_codP(int a){
int i,nr5=0;
for(i=1;i<=a;i++)
nr5+=nr(i,5);
return nr5;
}

void divizori(int k, int expo){
int d,e;
d=2;
while(k>1){
    e=0;
    while(k%d==0){
        e++;
        k/=d;
    }
    if(e>0)
        v[d]=(v[d]+e*expo) % 9973;
    d++;
}
}

int det_codC(){
int i,j,k=n, p=1;
x[0]=0;
for(i=1;i<=n;i++){
    for(j=x[i-1]+1;j<=x[i];j++)
        divizori(j,k);
    k--;
}
for(i=2;i<=x[n];i++)
    if(v[i]>0)
        p=(p*(v[i]+1)) % 9973;
return p;
}
int main()
{
    int codP, codC;
    cit();
    ordonare();
    if(p==1){
    codP=det_codP(x[n]);
    g<<codP<<'\n';
    }
        else{
    codC=det_codC();
    g<<codC<<'\n';
        }
    g.close();
    return 0;
}
