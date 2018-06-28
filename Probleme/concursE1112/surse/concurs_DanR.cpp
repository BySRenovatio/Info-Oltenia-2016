#include <fstream>
#define MAX_SIZE 100001
using namespace std;

ifstream f("concurs.in");
ofstream g("concurs.out");

int n,p,X[MAX_SIZE];

void assign_bigN(int k){
    X[0] = 0;
    while (k){
        X[0]++;
        X[X[0]] = k % 10;
        k /= 10;
    }
}

void Mult(int H[], unsigned long X)
/* H <- H*X */
{ int i;
  unsigned long T=0;

  for (i=1;i<=H[0];i++)
    { H[i]=H[i]*X+T;
      T=H[i]/10;
      H[i]=H[i]%10;
    }
  while (T) /* Cat timp exista transport */
    { H[++H[0]]=T%10;
      T/=10;
    }
}

void solve_1(){
    assign_bigN(n);
    for (int i = 2; i<=n; i++)
        Mult(X, n);
    for (int i=X[0]; i > 0; i--)
        g<<X[i];
    g<<'\n';
}

// A recursive function to find nth catalan number
unsigned long int catalan(unsigned int n)
{
    // Base case
    if (n <= 1) return 1;

    // catalan(n) is sum of catalan(i)*catalan(n-i-1)
    unsigned long int res = 0;
    for (int i=0; i<n; i++)
        res += catalan(i)*catalan(n-i-1);

    return res;
}


void solve_2(){
    g<<catalan(n)<<'\n';
}

int main()
{
    f>>p;
    f>>n;
    f.close();
    if (p == 1)
        solve_1();
    else
        solve_2();
    g.close();
    return 0;
}
