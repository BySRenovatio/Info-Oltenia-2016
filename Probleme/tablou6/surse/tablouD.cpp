#include<stdio.h>
#include<algorithm>

#define NMAX 1000
#define LMAX 14

using namespace std;

long long x[NMAX + 1];
int p, n, l, lung[NMAX + 1];

void citire() {
    int i, j;
    long long aux;
    FILE *f = fopen("tablou.in", "r");
    fscanf(f, "%d%d", &p, &n);

    l = 1;
    for(i = 1; i <= n; i++) {
        fscanf(f, "%I64d", &x[i]);
        aux = x[i];
        j = 0;
        while(aux) {
            j++;
            aux /= 10;
        }

        lung[i] = j;
        if(j > l)
            l = j;
    }

    fclose(f);
}

void rezolva1() {
    int rez = 0;
    FILE *f = fopen("tablou.out", "w");
    for(int i = 1; i <= n; i++)
        rez += l - lung[i];
    fprintf(f, "%d\n", rez);
    fclose(f);
}

void rezolva2() {
    int t[NMAX + 1][LMAX + 1], i, j, h, c;
    long long aux;

    for(i = 1; i <= n; i++) {
        aux = x[i];
        for(j = l; j >= 1; j--) {
            t[i][j] = aux % 10;
            aux /= 10;

            if(t[i][j] == 1 || t[i][j] == 2 || t[i][j] == 4 || t[i][j] == 8)
                t[i][j] = 1;
            else
                t[i][j] = 0;
        }
    }

    for(i = 0; i <= n; i++)
        t[i][0] = 0;
    for(i = 1; i <= l; i++)
        t[0][i] = 0;

    for(i = 1; i <= n; i++)
        for(j = 1; j <= l; j++)
            t[i][j] = t[i - 1][j] + t[i][j - 1] - t[i - 1][j - 1] + t[i][j];

    c = 0;
    for(h = min(n, l); h >= 1; h--) {
        for(i = 1; i + h - 1 <= n; i++)
            for(j = 1; j + h - 1 <= l; j++)
                if(t[i + h - 1][j + h - 1] - t[i - 1][j + h - 1] - t[i + h - 1][j - 1] + t[i - 1][j - 1] == h * h)
                    c++;
        if(c)
            break;
    }
    FILE * f = fopen("tablou.out", "w");
    fprintf(f, "%d %d\n", c, h);
    fclose(f);
}

int main() {
    citire();
    if(p == 1)
        rezolva1();
    else
        rezolva2();
    return 0;
}
