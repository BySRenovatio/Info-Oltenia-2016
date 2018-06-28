#include<stdio.h>
#define NMAX 105
using namespace std;

int p, n, m, k;
char t[NMAX][NMAX];

void citire() {
    FILE *f = fopen("litere.in", "r");
    fscanf(f, "%d%d%d%d", &p, &m, &n, &k);
    for(int i = 0; i < m; i++)
        fscanf(f, "%s", t[i]);
    fclose(f);
}

int rezolva1() {
    int c[27][27], l[26], q = 0;

    for(int i = 0; i < 26; i++)
        l[i] = 0;

    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            l[t[i][j] - 'a'] = 1;

    for(int i = 0; i < 26; i++)
        q += l[i];

    c[1][0] = c[1][1] = 1;
    for(int i = 2; i <= q; i++) {
        c[i][0] = c[i][i] = 1;
        for(int j = 1; j < i; j++)
            c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
    }

    return c[q][k];
}

int vocala(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int rezolva2() {
    int qx[NMAX * NMAX], qy[NMAX * NMAX], x[NMAX][NMAX], l, r, i, j;
    int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0}, s;
    for(i = 0; i < m ; i++)
        for(j = 0; j < n; j++)
            x[i][j] = 0;

    l = r = 0;
    for(i = 0; i < n; i++)
        if(vocala(t[0][i])) {
            qx[r] = 0;
            qy[r] = i;
            r++;
            x[0][i] = 1;
        }

    while(l < r) {
        if(qx[l] == m - 1)
            return x[qx[l]][qy[l]];
        for(s = 0; s < 4; s++) {
            i = qx[l] + dx[s];
            j = qy[l] + dy[s];

            if(i >= 0 && j >= 0 && i < m && j < n && vocala(t[i][j]) && x[i][j] == 0) {
                qx[r] = i;
                qy[r] = j;
                r++;
                x[i][j] = x[qx[l]][qy[l]] + 1;
            }
        }
        l++;
    }
    return -1;
}

int main() {
    citire();

    FILE *f = fopen("litere.out", "w");
    if(p == 1)
        fprintf(f, "%d\n", rezolva1());
    else
        fprintf(f, "%d\n", rezolva2());
    fclose(f);
    return 0;

}
