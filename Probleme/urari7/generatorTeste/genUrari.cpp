#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 1010
#define LUNGSTR 256

using namespace std;

void writeTest(int i, int n, int p, int k, char urare[MAX][LUNGSTR]);
void generateString(int j, char urare[MAX][LUNGSTR], int lung);

int main()
{
    int n = 1;
    int p, k;
    char urari[MAX][LUNGSTR];

    srand(time(NULL));

    for(int i=0; i<=19; i++)
    {
          n = 50 * (i+1);

          if (i < 10)
                p = 1;
          else
                p = 2;

          k = rand() % n + 1;

          char *begin = urari[0];
          char *end = begin + sizeof(urari);
          fill(begin, end, 0);

          for(int j=1; j<=n; j++)
            generateString(j, urari, (rand() % 200 + 1));

          writeTest(i, n, p, k, urari);
    }

    return 0;
}

void writeTest(int i, int n, int p, int k, char urare[MAX][LUNGSTR])
{
    char numeFisier[20];
    itoa(i, numeFisier, 10);
    strcat(numeFisier, "-urari.in");

    ofstream fout(numeFisier);
    fout << p << endl;
    fout << n << " " << k << endl;

    int used[MAX];
    int newNr;

    fill(used, used+MAX, 0);

    for(int i=1; i<=n; i++)
    {
        again:
        newNr = rand() % 1000 + 1;

        if (used[newNr] == 0)
        {
            used[newNr] = 1;
            fout << newNr << "." << urare[i];
        }
        else
            goto again;
    }

    fout.close();
}

void generateString(int j, char urare[MAX][LUNGSTR], int lung)
{
    for(int i=0; i<lung; i++)
    {
        urare[j][i] = 'a' + (rand() % 26);

        if ((i % 7 == 0) && (rand() % 2 == 0) && (i !=0 ))
            urare[j][i] = ' ';
    }
    urare[j][lung] = '\n';
}
