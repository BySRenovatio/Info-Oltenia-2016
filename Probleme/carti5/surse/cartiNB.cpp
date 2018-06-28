#include <fstream>

using namespace std;
long int n;
int p, lipsa[10001];

ifstream fin("carti.in");
ofstream fout("carti.out");

int NrDiv(long int a){
    int nr,i;
if(a==0 || a==1)
return 1;
else{
    nr=0;
    for(i=1;i*2<=a;i++)
        if(a%i==0)
            nr++;
    return nr+1;
}
}

int main()
{
    int i;
long int x,s;
    fin>>p;
    fin>>n;
for(i=1;i<=n;i++)
lipsa[i]=0;
    s=0;
for(i=1;i<=n;i++){
        fin>>x;
        s+=x;
        while(NrDiv(x)>2){
            lipsa[i]++;
            x--;
        }
    }
    if(p==1){
        fout<<NrDiv(s);
    }
    else
    if(p==2){
        for(i=1;i<=n;i++)
            fout<<lipsa[i]<<" ";
    }
    fout<<'\n';
    return 0;
}