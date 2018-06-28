#include<stdio.h>
#define NMAX 1001
using namespace std;

int p, m, n, compus[NMAX * NMAX], i, j, t, a, b, c;
long long s, sum;

void gaseste_numere() {
    sum = 1LL * m * n * (m * n + 1) / 2;
    t = sum - s;

    compus[0] = compus[1] = 1;
    for(i = 2; i * i <= t; i++)
        if(!compus[i])
            for(j = 0; i * i + j * i <= t; j++)
                compus[i * i + j * i] = 1;

    for(i = 2; i < t; i++)
        if(!compus[i])
            for(j = i + 1; t - i - j > j; j++)
                if(!compus[j] && t - i - j <= m * n && !compus[t - i - j]) {
                    a = i;
                    b = j;
                    c = t - i - j;
                    return;
                }
}

int main() {
    FILE *f = fopen("prime.in", "r");
    fscanf(f, "%d%d%d%I64d", &p, &m, &n, &s);
    fclose(f);

    gaseste_numere();

    f = fopen("prime.out", "w");
    if(p == 1)
        fprintf(f, "%d %d %d\n", a, b, c);
    else
        fprintf(f, "%d %d\n", (c - 1) / n + 1, (c - 1) % n + 1);
    return 0;
}
