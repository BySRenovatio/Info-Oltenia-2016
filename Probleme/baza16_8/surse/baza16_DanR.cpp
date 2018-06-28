#include <fstream>

using namespace std;
int n,x[11],p;
int digits[16];
ifstream f("baza16.in");
ofstream g("baza16.out");

void solve_1(){
    int i,j;
    int aux;
    int Nr1 = 0;
    for (i = 1; i <= n; i++)
    {
        aux = x[i];
        while (aux != 0)
        {
            j = aux % 16;
            if (j > 9) break;
            aux /= 16;
        }
        if (aux == 0) Nr1++;
    }
    g<<Nr1<<'\n';
}

int factorial (int n){
    if (n==1) return 1;
    return n*factorial(n-1);
}

void solve_2(){
    int i,j,aux;
    for (i = 1; i <= n; i++){
       aux = x[i];
       while (aux != 0){
        digits[aux%16]++;
        aux /= 16;
       }
    }
    j = 0;
    for (i=0; i < 16; i++)
        if (digits[i])
            j++;

    if (digits[0] == 0)
        g<<factorial(j);
    else
        g<<(j-1)*factorial(j-1);
}

int main()
{
    f>>p;
    f>>n;
    for (int i = 1; i <=n; i++)
        f>>x[i];
    f.close();
    if (p==1)
        solve_1();
    else
        solve_2();
    g.close();
    return 0;
}
