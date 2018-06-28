#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#define MAX 1010

using namespace std;

void readData(int &p, int &n, int &k, int elevi[], double raport[]);
int mycount(char v[], char x);
void swapme(int &x, int &y);
void swapme(double &x, double &y);
void writeData1(int elevi[], int n);
void writeData2(int elevi[], double raport[], int n, int k);

int main()
{
    int n, p, k;
    int elevi[MAX];
    double raport[MAX];

    readData(p, n, k, elevi, raport);

    if (p == 1)
        writeData1(elevi, n);
    else                        // p == 2
        writeData2(elevi, raport, n, k);

    return 0;
}

void readData(int &p, int &n, int &k, int elevi[], double raport[])
{
    char aux[256];
    int countA, countE, countI, countU, countO;
    int countSpace;

    ifstream fin("urari.in");

    fin >> p;
    fin >> n;
    fin >> k;

    for(int i=1; i<=n; i++)
    {
        fin.getline(aux, 250, '.');
        elevi[i] = atoi(aux);
        fin.getline(aux, 250);

        /// aeiou
        countA = mycount(aux, 'a');
        countE = mycount(aux, 'e');
        countI = mycount(aux, 'i');
        countO = mycount(aux, 'o');
        countU = mycount(aux, 'u');
        countSpace = mycount(aux, ' ');

        raport[i] = (countA + countE + countI + countO + countU) / 1.0 / (countSpace + 1);
    }

    fin.close();
}


void writeData1(int elevi[], int n)
{
    int nrElevi = -1;

    for(int i=1; i<=n; i++)
        if (nrElevi < elevi[i])
            nrElevi = elevi[i];

    ofstream fout("urari.out");
    fout << nrElevi - n;
    fout.close();
}


void writeData2(int elevi[], double raport[], int n, int k)
{
    for(int i=1; i<=n; i++)
        for(int j=i+1; j<=n; j++)
            if (raport[i] > raport[j])
            {
                swapme(raport[i], raport[j]);
                swapme(elevi[i], elevi[j]);
            }

    ofstream fout("urari.out");
    for(int t=n; t>n-k; t--)
        fout << elevi[t] << " ";
    fout.close();
}

void swapme(int &x, int &y)
{
    int aux;

    aux = x;
    x = y;
    y = aux;
}

void swapme(double &x, double &y)
{
    double aux;

    aux = x;
    x = y;
    y = aux;
}

int mycount(char v[], char x)
{
    int lung = strlen(v);
    int counter = 0;

    for(int i=0; i<lung; i++)
        if (v[i] == x)
            counter += 1;

    return counter;
}
