#include <fstream>
#include <cmath>
#define MAX_SIZE 10001
using namespace std;
int p,n,X[MAX_SIZE],i,sum;
ifstream f("carti.in");
ofstream g("carti.out");

void solve_1(){
    int nr = 1; //suma insusi
    int i;
    for (i=1; i <= sum/2; i++)
        if (sum % i == 0)
            nr++;
    g<<nr<<'\n';
}

bool is_prime(int k){
    int i;
    for (i=2; i<= sqrt(k); i++)
        if (k%i==0)
            return false;
    return true;
}

void solve_2(){
    int i,j;
    for (i = 1; i <=n; i++)
    {
        j = X[i];
        while (!is_prime(j))
            j--;
        g<<X[i]-j<<" ";
    }
    g<<'\n';
}

int main()
{
    f>>p;
    f>>n;
    sum = 0;
    for (i = 1; i <= n; i++)
        {f>>X[i]; sum += X[i]; }
    f.close();
    if (p == 1)
        solve_1();
    else
        solve_2();
    g.close();
    return 0;
}
