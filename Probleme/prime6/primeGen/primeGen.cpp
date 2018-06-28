#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

void writeTest(int i, int m, int n, int p, unsigned long int S);
void writeOkFile(int i);
int trei(int val);

int main()
{
    unsigned long int S;
    int m, n;
    int p;

    srand(time(NULL));

    for(int i=0; i<20; i++)
    {
        if(i % 2 == 0)
            p = 1;
        else
            p = 2;

        m = i * 10 + 25;
        n = m + (rand() % 21 - 10);
        S = (unsigned long int) ((1 + (n * m)) * (n * m) / 2) - trei(m*n);

        writeTest(i, m, n, p, S);
        writeOkFile(i);
    }

    return 0;
}

void writeTest(int i, int m, int n, int p, unsigned long int S)
{
    char numeFisier[20];
    itoa(i, numeFisier, 10);
    strcat(numeFisier, "-prime.in");

    ofstream fout(numeFisier);
    fout << p << endl;
    fout << m << " " << n << " " << S << endl;

    fout.close();
}

void writeOkFile(int i)
{
    char numeFisier[20];
    itoa(i, numeFisier, 10);
    strcat(numeFisier, "-prime.ok");

    ofstream fout(numeFisier);
    fout.close();
}

int trei(int val)
{
    int vect[100010] = {0};

    ifstream fin("pri.txt");
    for(int i=1; i<=100000; i++)
        fin >> vect[i];

    int Suma = 0;
    int sw = 0;
    int nr;

    while (sw < 3)
    {
        nr = rand() % 99999 + 1;

        if (vect[nr] <= val)
            Suma += vect[nr], sw++;

    }

    return Suma;
}
