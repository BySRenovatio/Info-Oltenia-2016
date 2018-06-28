#include <fstream>

using namespace std;

long int n,x[10001],p,k;
int f1[10],f2,a;

void citeste()
{
    int i;
    ifstream fin("elevi.in");
    fin>>p>>n;
    for(i=1;i<=n;i++)
    fin>>x[i];
    fin.close();
}

int impartire(long int &a)
{
    f2=0;
    while(a>0)
    {
        f2++;
        f1[f2]=a%10;
        a/=10;
    }
	return f2;
}

void ordonare(int y[10])
{
    int i,j,aux;
    for(i=1;i<n;i++)
        for(j=1;j<=n;j++)
            if(y[i]>y[j])
            {
                aux=x[i];
                x[i]=x[j];
                x[j]=aux;
            }
}

void refacere(int y[10],long int a)
{
    int i;
	a=0;
    for(i=f2;i>=1;i--){
		a*=10+y[i];
	}
}

bool gasire(long int y,int i){
	bool gasit; int j;
		for(j=1;j<=n;j++)
			if(y==x[j]&&i!=j){
				gasit=true;
				break;
			}
			return gasit;
			
}
int main()
{
    ofstream fout("elevi.out");
    int i; int s=0;
    citeste();
    if(p==1){
		int i; int s=0;
		for(i=1;i<=n;i++)
			s+=impartire(x[i]);
		fout<<s;
    }
    if(p==2)
    {
		s=0;
        for(i=1;i<=n;i++)
        {
            impartire(x[i]);
            ordonare(f1);
            refacere(f1,x[i]);
			if(!(gasire(x[i],i)))
				s++;
        }
        fout<<s;
    }
    fout.close();
    return 0;
}