#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

void writeTest(int i, int n, int p);
void writeOkFile(int i);

int main()
{
    int n, p;

    srand(time(NULL));

    for(int i=0; i<20; i++)
    {
        if(i % 2 == 0)
            p = 1;
        else
            p = 2;

        n = (i + 1) * 50;

        writeTest(i, n, p);
        writeOkFile(i);
    }

    return 0;
}

void writeTest(int i, int n, int p)
{
    char numeFisier[20];
    itoa(i, numeFisier, 10);
    strcat(numeFisier, "-tablou.in");

    ofstream fout(numeFisier);
    fout << p << endl;
    fout << n << endl;

    for(int j=1; j<=n; j++)
        fout << ((rand() + 1) * (rand() + 1)) << " ";

    fout.close();
}

void writeOkFile(int i)
{
    char numeFisier[20];
    itoa(i, numeFisier, 10);
    strcat(numeFisier, "-tablou.ok");

    ofstream fout(numeFisier);
    fout << " ";
    fout.close();
}
