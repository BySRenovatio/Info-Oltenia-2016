#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

#define MAX 11

using namespace std;

void readData(int &n, int &p, long numere[]);
void writeData(long nr);
void transformNumbers(int n, long numere[], char baza16[][MAX]);
int countBaza16(int n, char baza16[][MAX]);
long countDistinct(int n, char baza16[][MAX]);
long factorial(int n);

int main()
{
    int n, p;
    long nrFaraCifre;
    long combinatii;
    long numere[MAX];
    char baza16[MAX][MAX];

    readData(n, p, numere);
    transformNumbers(n, numere, baza16);

    if (p == 1)
    {
        nrFaraCifre = countBaza16(n, baza16);
        writeData(nrFaraCifre);
    }
    else
    {
        combinatii = countDistinct(n, baza16);
        writeData(combinatii);
    }

    return 0;
}

void readData(int &n, int &p, long numere[])
{
    ifstream fin("baza16.in");
    fin >> p;
    fin >> n;

    for(int i=1; i<=n; i++)
        fin >> numere[i];

    fin.close();
}

void writeData(long nr)
{
    ofstream fout("baza16.out");
    fout << nr;
    fout.close();
}

void transformNumbers(int n, long numere[], char baza16[][MAX])
{
    for(int i=1; i<=n; i++)
        itoa(numere[i], baza16[i], 16);
}

int countBaza16(int n, char baza16[][MAX])
{
    int totalNr = n;

    for(int i=1; i<=n; i++)
        for(int j=0; j<strlen(baza16[i]); j++)
            if ((baza16[i][j] == 'a') || (baza16[i][j] == 'b') || (baza16[i][j] == 'c') || (baza16[i][j] == 'd') || (baza16[i][j] == 'e') || (baza16[i][j] == 'f'))
            {
                totalNr -= 1;
                break;
            }
    return totalNr;
}

long countDistinct(int n, char baza16[][MAX])
{
    int cifreDistincte[20] = {0};
    int dist = 0;

    for(int i=1; i<=n; i++)
        for(int j=0; j<strlen(baza16[i]); j++)
            switch (baza16[i][j])
            {
                case '0': {cifreDistincte[0]++; break;}
                case '1': {cifreDistincte[1]++; break;}
                case '2': {cifreDistincte[2]++; break;}
                case '3': {cifreDistincte[3]++; break;}
                case '4': {cifreDistincte[4]++; break;}
                case '5': {cifreDistincte[5]++; break;}
                case '6': {cifreDistincte[6]++; break;}
                case '7': {cifreDistincte[7]++; break;}
                case '8': {cifreDistincte[8]++; break;}
                case '9': {cifreDistincte[9]++; break;}
                case 'a': {cifreDistincte[11]++; break;}
                case 'b': {cifreDistincte[12]++; break;}
                case 'c': {cifreDistincte[13]++; break;}
                case 'd': {cifreDistincte[14]++; break;}
                case 'e': {cifreDistincte[15]++; break;}
                case 'f': {cifreDistincte[16]++; break;}
            }

    for(int i=0; i<=16; i++)
        if (cifreDistincte[i] != 0)
            dist++;

    if (cifreDistincte[0] == 0)
        return factorial(dist);
    else
        return (dist-1) * factorial(dist-1);
}

long factorial(int n)
{
    if(n!=1)
        return n*factorial(n-1);

    return 1;
}
