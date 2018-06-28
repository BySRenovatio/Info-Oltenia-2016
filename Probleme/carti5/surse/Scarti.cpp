#include <iostream>
#include <fstream>

#define MAX 10011
#define MAXC 10000011

using namespace std;

int CIUR[MAXC];

void ciur();
int readData(int &p, int &n, int carti[]);
int getDivs(int nr);
int firstPrime(int nr);
void writeData(int p, int n, int nrDivizori, int pagCarti[]);

int main()
{
    int p;
    int n;
    int sum;
    int carti[MAX];
    int pagCarti[MAX];
    int nrDivizori;

    ciur();

    sum = readData(p, n, carti);

    if (p == 1)
        nrDivizori = getDivs(sum);
    else                            // p == 2
    {
        for(int i=1; i<=n; i++)
            pagCarti[i] = firstPrime(carti[i]);
    }

    writeData(p, n, nrDivizori, pagCarti);

    return 0;
}

void ciur()
{
    int i, j;

    for(int i=1; i<= MAX-1; i++)
        CIUR[i] = 1;

    for(i=2; i<= MAX/2; i++)
        for(j=i; j<= MAX-1; j+=i)
            if ((CIUR[j] == 1) && (j!=i))
                CIUR[j] = 0;
}

int readData(int &p, int &n, int carti[])
{
    int i;
    int s = 0;

    ifstream fin("carti.in");

    fin >> p;
    fin >> n;

    for(i=1; i<=n; i++)
        fin >> carti[i], s += carti[i];

    fin.close();

    return s;
}

void writeData(int p, int n, int nrDivizori, int pagCarti[])
{
    ofstream fout("carti.out");

    if (p == 1)
    {
        fout << nrDivizori;
    }
    else            // p == 2
    {
        for(int i=1; i<=n; i++)
            fout << pagCarti[i] << " ";
    }

    fout.close();
}

int getDivs(int nr)
{
    int i;
    int nrDiv = 0;

    for(i=2; i<nr; i++)
        if ((nr % i == 0) && (CIUR[i] == 1))
            nrDiv += 1;

    return (nrDiv + 2);     // (1 si el insusi)
}

int firstPrime(int nr)
{
    int i;

    for(i=nr; i>=1; i--)
        if (CIUR[i] == 1)
            return (nr-i);

    return -1;
}
