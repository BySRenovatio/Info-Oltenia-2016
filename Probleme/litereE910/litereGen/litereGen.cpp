#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

void writeTest(int i, int m, int n, int p, int k);
void writeOkFile(int i);

int main()
{
    int m, n, p, k;

    srand(time(NULL));

    for(int i=0; i<20; i++)
    {
        if(i % 2 == 0)
            p = 1;
        else
            p = 2;

        m = (i * 5) + 3;
        n = m + (rand() % 5 - 2);
        k = rand() % 10 + 3;

        writeTest(i, m, n, p, k);
        writeOkFile(i);
    }

    return 0;
}

void writeTest(int i, int m, int n, int p, int k)
{
    int valMin = 0;
    int cate = 0;

    char numeFisier[20];
    itoa(i, numeFisier, 10);
    strcat(numeFisier, "-litere.in");

    ofstream fout(numeFisier);
    fout << p << endl;
    fout << m << " " << n << " " << k << endl;

    for(int j=1; j<=m; j++)
    {
        valMin = 0;
        for(int l=1; l<=n; )
        {
            cate = rand() % 5 + 1;
            for(int s=1; (s<=cate && l<=n) ; s++, l++)
                fout << char(97 + valMin);
            valMin ++;

            if (valMin >= 26)
                valMin = 0;
        }
        fout << endl;
    }

    fout.close();
}

void writeOkFile(int i)
{
    char numeFisier[20];
    itoa(i, numeFisier, 10);
    strcat(numeFisier, "-litere.ok");

    ofstream fout(numeFisier);
    fout.close();
}
