#include <fstream>
#define MAX_SIZE 110

using namespace std;
int A[MAX_SIZE],B[MAX_SIZE],C[MAX_SIZE];
int n,k,i,p;
ifstream f("biscuiti.in");
ofstream g("biscuiti.out");

void solve_1(){
    /* My approach --- NU MERGE
    int i,j;
    for (i = 2*n; i >= 0; i--)
        if (i%k==0){
            j = i/k;
            break;
        }
    int nr = 0;
    for (i = 1; i <= j; i++)
        if ((k*i)%2==1)
        nr++;

    g<<nr;*/
    //FOLOSIND FORMULA DE LA DRAGOS DIN SURSA
    if (k%2==0)
        g<<3*n<<'\n';
    else
        g<<3*(n-((2*n-1)/k+1)/2);
}

void Subtract(int A[], int B[])
/* A <- A-B */
{ int i, T=0;

  for (i=B[0]+1;i<=A[0];) B[i++]=0;
  for (i=1;i<=A[0];i++)
    A[i]+= (T=(A[i]-=B[i]+T)<0) ? 10 : 0;
    /* Adica A[i]=A[i]-(B[i]+T);
       if (A[i]<0) T=1; else T=0;
       if (T) A[i]+=10; */
  while (!A[A[0]]) A[0]--;
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

void copy_array(int A[], int B[]){
    B[0] = A[0];
    for (int i = 1; i <= A[0]; i++)
        B[i] = A[i];
}

void solve_2(){
    int i;
    if (n==1)
        g<<3<<'\n';
    else
    if (n==2)
        g<<11<<'\n';
    else{
        B[0] = 2;
        B[1] = 1;
        B[2] = 1;
        A[0] = 1;
        A[1] = 3;
        for (i = 3; i <= n; i++){
            copy_array(B,C);
            Mult(B,4);
            Subtract(B,A);
            copy_array(C,A);
        }
        for (i = B[0]; i >= 1; i--)
            g<<B[i];
        g<<'\n';
    }
}

int main()
{
    f>>p;
    f>>n>>k;
    f.close();
    if (p == 1)
        solve_1();
    else
        solve_2();
    g.close();
    return 0;
}
