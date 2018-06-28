#include<stdio.h>
#define MAXCIF 205
#define NMAX 100
#define NSTART 20
#define NTESTE 20
using namespace std;
int p, n;

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

void inmultire(int a[MAXCIF], int b[MAXCIF], int c[MAXCIF]) {
    int i, j, t=0;

    c[0]= a[0] + b[0] - 1;
    for(i = 1; i <= a[0] + b[0]; i++)
        c[i] = 0;

    for(i = 1; i <= a[0]; i++)
        for(j = 1; j <= b[0]; j++)
            c[i + j - 1] += a[i] * b[j];

    for(i = 1; i <= c[0]; i++) {
        c[i] += t;
        t = c[i] / 10;
        c[i] %= 10;
    }
    if(t)
        c[++c[0]] = t;
}

void putere(int n, int p, int rez[MAXCIF]) {
    int a[MAXCIF], b[MAXCIF], i;

    atribuire(a, n);
    atribuire(rez, 1);

    for(i = 1; i <= p; i++) {
        copiere(rez, b);
        inmultire(a, b, rez);
    }
}

void catalan(int n, int rez[MAXCIF]) {
    int p[2 * NMAX + 10], a[MAXCIF], b[MAXCIF], i, x, d;

    for(i = 1; i <= 2 * n; i++)
        p[i] = 0;

    for(i = n + 2; i <= 2 * n; i++) {
        x = i;
        d = 2;
        while(x > 1) {
            while(x % d == 0) {
                p[d]++;
                x /= d;
            }
            d++;
        }
    }

    for(i = 2; i <= n; i++) {
        x = i;
        d = 2;
        while(x > 1) {
            while(x % d == 0) {
                p[d]--;
                x /= d;
            }
            d++;
        }
    }

    atribuire(rez, 1);
    for(i = 2; i <= 2 * n; i++)
        if(p[i]) {
            atribuire(a, i);
            while(p[i]) {
                copiere(rez, b);
                inmultire(a, b, rez);
                p[i]--;
            }
        }
}

void scrie_test(int p, int test) {
    char fisier[20];
    int i, rez[MAXCIF];

    printf("p=%d test=%d n=%d\n", p, test, n);

    sprintf(fisier, "teste\\%d-concurs.in", test);
    FILE *in = fopen(fisier, "w");

    sprintf(fisier, "teste\\%d-concurs.ok", test);
    FILE *ok = fopen(fisier, "w");

    if(p == 1)
        putere(n, n, rez);
    else
        catalan(n, rez);

    fprintf(in, "%d\n%d\n", p, n);

    for(int i = rez[0]; i >= 1; i--)
        fprintf(ok, "%d", rez[i]);
    fprintf(ok, "\n");

    fclose(in);
    fclose(ok);
}

int main(){
    int test, nr_teste1, nr_teste2, neg, i;

    nr_teste1 = NTESTE / 2;
    nr_teste2 = NTESTE / 2;

    //cerinta 1
    for(test = 0; test < nr_teste1; test++) {
        n =  NSTART + (float)test / (nr_teste1 - 1) * (NMAX - NSTART);
        scrie_test(1, test);
    }


    //cerinta 2
    n = 7;
    scrie_test(2, 10);
    n = 10;
    scrie_test(2, 11);
    for(test = 2; test < nr_teste2; test++) {
        n =  NSTART + (float)test / (nr_teste2 - 1) * (NMAX - NSTART);
        scrie_test(2, nr_teste1 + test);
    }
    return 0;
}
