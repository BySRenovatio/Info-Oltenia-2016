#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

void writeTest(int i, int n, int p);
void writeOkFile(int i);
void make(int tip, int vect[], int nr);

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

        n = i * 5000 + 2500;

        writeTest(i, n, p);
        writeOkFile(i);
    }

    return 0;
}

void writeTest(int i, int n, int p)
{
    char numeFisier[20];
    itoa(i, numeFisier, 10);
    strcat(numeFisier, "-relief.in");

    ofstream fout(numeFisier);
    fout << p << endl;
    fout << n << endl;

    int puse = 0;
    int tip;
    int nr;
    int vect[111];

    while(puse < n)
    {
        nr = rand() % 91 + 10;

        if (puse + nr <= n)
        {
            tip = rand() % 3 + 1;
            make(tip, vect, nr);

            for(int j=1; j<=nr; j++)
                fout << vect[j] << " ";

            puse += nr;
        }

        if (n - puse <= 30)
        {
            nr = n - puse;

            tip = rand() % 3 + 1;
            make(tip, vect, nr);

            for(int j=1; j<=nr; j++)
                fout << vect[j] << " ";

            puse += nr;
        }
    }

    fout.close();
}

void writeOkFile(int i)
{
    char numeFisier[20];
    itoa(i, numeFisier, 10);
    strcat(numeFisier, "-relief.ok");

    ofstream fout(numeFisier);
    fout.close();
}

void make(int tip, int vect[], int nr)
{
    int top = rand() + 1;

    if (tip == 1)               /// munte
    {
        for(int i=nr/2, j=0; i>=1; i--, j++)
            vect[i] = top - j;

        for(int i=nr/2+1, j=1; i<=nr; i++, j++)
            vect[i] = top - j;
    }
    else
        if (tip == 2)           /// deal
        {
            for(int i=1; i<=5; i++)
                vect[i] = top - 5 + i;

            for(int i=nr; i>=nr-5; i--)
                vect[i] = top - 5 + (nr - i);

            for(int i=6; i<=nr-5; i++)
                vect[i] = top;
        }
        else
            if (tip == 3)       /// vale
            {
                for(int i=1; i<=nr; i++)
                    vect[i] = top;
            }
}
