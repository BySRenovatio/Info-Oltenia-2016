#include <fstream>

using namespace std;
long long int n;
int f[11],p;
ifstream fin("note.in");
ofstream fout("note.out");

void nr(long long int &a){
    while(a>0){
        if(a%10==0){
            f[10]++;
            a/=100;
        }
        else
        {
            f[a%10]++;
            a/=10;
        }
    }
}


int main()
{
    int s,i;
    fin>>p;
    fin>>n;
    fin.close();
    s=0;
    if(p==1)
    {
        nr(n);
        for(i=1;i<=10;i++)
            s+=f[i];
        fout<<s;
    }
    else
        if(p==2)
    {
	i=0;
        while(f[i]==0)
            i++;
        fout<<f[i];
    }
    fout.close();
    return 0;
}
