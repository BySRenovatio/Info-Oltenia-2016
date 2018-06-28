#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <limits.h>
 
#define MAX 10010
 
using namespace std;
 
void writeData(int nr);
void readData(int &n, int &p, int &k, int numere[]);
int compare(const void *a, const void *b) { return ( *(int*)a - *(int*)b ); }
int calcSuma(int n, int numere[]);
 
int main()
{
    int n, p, k;
    int numere[MAX];
    int suma;
 
    readData(n, p, k, numere);
 
    if (p == 1)
    {
        qsort(numere, n, sizeof(int), compare);
        writeData(numere[k-1]);
    }
    else
    {
        suma = calcSuma(n, numere);
        writeData(suma);
    }
 
    return 0;
}
 
void readData(int &n, int &p, int &k, int numere[])
{
    ifstream fin("numere.in");
 
    fin >> p;
 
    if (p == 1)
    {
        fin >> n >> k;
        for(int i=0; i<n; i++)
            fin >> numere[i];
    }
    else        // p = 2
    {
       fin >> n >> k;
       for(int i=0; i<n; i++)
            fin >> numere[i];
    }
 
    fin.close();
}
 
void writeData(int nr)
{
    ofstream fout("numere.out");
 
    fout << nr;
 
    fout.close();
}
 
int calcSuma(int n, int numere[])
{
    int max_so_far;
    int max_ending_here;
    int sw = 0;
 
    for(int i=0; i<n; i++)
        if(numere[i] >= 0)
        {
            sw = 1;
            break;
        }
 
    if (sw == 0)
        goto part2;
 
    max_so_far = INT_MIN;
    max_ending_here = 0;
 
    for(int i = 0; i < n; i++)
    {
        max_ending_here = max(max_ending_here + numere[i], 0);
        max_so_far = max(max_ending_here, max_so_far);
    }
 
    return max_so_far;
 
    part2:
    max_so_far = numere[0];
    max_ending_here = numere[0];
 
    for(int i = 1; i < n; i++)
    {
        max_ending_here = max(max_ending_here + numere[i], numere[i]);
        max_so_far = max(max_ending_here, max_so_far);
    }
 
    return max_so_far;
}