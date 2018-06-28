#include <iostream>
#include <fstream>

#define MAXN 1010
#define MAXLUNG 16

using namespace std;

int readData(int &n, int &p, long numbers[]);
void writeData(int p, int nrTab, int dimTab, int nrZero);
void buildTab(int n, int m, long numbers[], int tablou[][MAXLUNG]);
int solve1(int n, int m, long numbers[]);
void solve2(int n, int m, int tablou[][MAXLUNG], int &nrTab, int &dimTab);
int checkTab(int x, int n, int y, int m, int lung, int tab[][MAXLUNG]);

int main()
{
    int n, m, p;
    long numbers[MAXN];
    int tablou[MAXN][MAXLUNG];
    int nrTab, dimTab, nrZero;

    m = readData(n, p, numbers);

    if (p == 1)
    {
        nrZero = solve1(n, m, numbers);
        writeData(1, nrTab, dimTab, nrZero);
    }
    else            // p = 2
    {
        buildTab(n, m, numbers, tablou);
        solve2(n, m, tablou, nrTab, dimTab);
        writeData(2, nrTab, dimTab, nrZero);
    }

    return 0;
}

int readData(int &n, int &p, long numbers[])
{
        char buffer[32];
        int maxL = -1;
        int len;

        ifstream fin("tablou.in");

        fin >> p;
        fin >> n;

        for(int i=1; i<=n; i++)
        {
            fin >> numbers[i];
            len = sprintf(buffer, "%ld", numbers[i]);        /// nerdy way to find length

            if (maxL < len)
                maxL = len;
        }

        fin.close();
        return maxL;
}

void writeData(int p, int nrTab, int dimTab, int nrZero)
{
    ofstream fout("tablou.out");

    if (p == 1)
    {
        fout << nrZero;
    }
    else    // p = 2
    {
        fout << nrTab << " " << dimTab;
    }

    fout.close();
}

void buildTab(int n, int m, long numbers[], int tablou[][MAXLUNG])
{
    long nr;

    for(int i=1; i<=n; i++)
    {
        nr = numbers[i];
        for(int j=m; j>=1; j--)
        {
            tablou[i][j] = nr % 10;
            nr = nr / 10;
        }
    }

    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            if((tablou[i][j] == 2) || (tablou[i][j] == 4) || (tablou[i][j] == 8) || (tablou[i][j] == 1))
                tablou[i][j] = 1;
            else
                tablou[i][j] = 0;
}

int solve1(int n, int m, long numbers[])
{
    char buffer[32];
    int nrZero = n * m;
    int len;

    for(int i=1; i<=n; i++)
    {
       len = sprintf(buffer, "%ld", numbers[i]);
       nrZero -= len;
    }

    return nrZero;
}

void solve2(int n, int m, int tablou[][MAXLUNG], int &nrTab, int &dimTab)
{
    int auxDimTab;

    nrTab = 0;
    dimTab = 0;

    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            for(int lung=1; lung<=m; lung++)
            {
                auxDimTab = checkTab(i, n, j, m, lung, tablou);

                if (auxDimTab > dimTab)
                {
                    dimTab = auxDimTab;
                    nrTab = 1;
                }
                else
                    if (auxDimTab == dimTab)
                    {
                        nrTab += 1;
                    }
            }
}

int checkTab(int x, int n, int y, int m, int lung, int tab[][MAXLUNG])
{
    int prod = 1;

    if(x + lung > n)
        return 0;

    if(y + lung > m)
        return 0;

    for(int i=x; i<=x+lung; i++)
        for(int j=y; j<=y+lung; j++)
        {
            prod *= tab[i][j];

            if (prod == 0)
                return 0;
        }
    return (lung + 1);
}
