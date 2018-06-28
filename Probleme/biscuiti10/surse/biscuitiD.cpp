#include<stdio.h>
#define MAXN 100
#define MAXCIF 100
using namespace std;

void atribuire(int a[MAXCIF], int x) {
    a[0] = 0;
    while(x) {
        a[0]++;
        a[a[0]] = x % 10;
        x /= 10;
    }
}

void copiere(int a[MAXCIF], int b[MAXCIF]) {
    for (int i = 0; i <= a[0]; ++i) {
        b[i] = a[i];
    }
}

void adunare(int a[MAXCIF], int b[MAXCIF]) {
    int i, t = 0;

    if(b[0]>a[0]) {
        for(i = a[0] + 1; i <= b[0]; i++)
            a[i]=0;
        a[0] = b[0];
    } else
        for(i = b[0] + 1; i <= a[0]; i++)
            b[i] = 0;

    for(i = 1; i <= a[0]; i++) {
        a[i] += b[i] + t;
        t = a[i] / 10;
        a[i] %= 10;
    }
    if(t)
        a[++a[0]] = t;
}

void scadere(int a[MAXCIF], int b[MAXCIF]) {
    int i, t = 0;

    for(i = b[0] + 1; i <= a[0]; i++)
        b[i] = 0;

    for(i = 1; i <= a[0]; i++) {
        a[i] = a[i] - (b[i] + t);
        if(a[i] < 0)
            t = 1;
        else
            t = 0;
        if(t)
            a[i] += 10;
    }

    while(!a[a[0]])
        a[0]--;
}

void inmultire(int a[MAXCIF], int x) {
    int i, t = 0;

    for(i = 1; i <= a[0]; i++) {
        a[i] = a[i] * x + t;
        t = a[i] / 10;
        a[i] = a[i] % 10;
    }

    while (t) {
        a[++a[0]] = t % 10;
      t /= 10;
    }
}

int main() {
    int p, n, k;
    FILE *f = fopen("biscuiti.in", "r");
    fscanf(f, "%d%d%d", &p, &n, &k);
    fclose(f);

    f = fopen("biscuiti.out", "w");
    if(p == 1)
        if(k % 2 == 0)
            fprintf(f, "%d\n", 3 * n);
        else
            fprintf(f, "%d\n", 3 * (n - ((2 * n - 1) / k + 1) / 2));
    else {
        int a[MAXCIF], b[MAXCIF], c[MAXCIF];
        if(n == 1)
            fprintf(f, "%3\n");
        else if(n == 2)
            fprintf(f, "%11\n");
        else {
            atribuire(a, 3);
            atribuire(b, 11);
            for(int i = 3; i <= n; i++) {
                copiere(b, c);
                inmultire(b, 4);
                scadere(b, a);
                copiere(c, a);
            }
        }
        for(int i = b[0]; i >= 1; i--)
            fprintf(f, "%d", b[i]);
        fprintf(f, "\n");
    }

    fclose(f);
    return 0;
}
