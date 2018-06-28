#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<algorithm>
#include<ctime>
#define NMAX 250
#define NSTART 20
#define NTESTE 20
#define MOD 9901
using namespace std;

int p, m, n, aux;
char c1[NMAX + 5], c2[NMAX + 5];

void rezolva1(int test) {
    int poz[NMAX + 5], i, j;
    for(i = 0, j = 0; i < m && j < n; i++)
        if(c1[i] == c2[j]) {
            poz[j] = i + 1;
            j++;
        }

    char fisier[20];
    sprintf(fisier, "teste\\%d-cuvinte.in", test);
    FILE *in = fopen(fisier, "w");
    fprintf(in, "1\n%s\n%s\n", c1, c2);
    fclose(in);

    sprintf(fisier, "teste\\%d-cuvinte.ok", test);
    FILE *ok = fopen(fisier, "w");

    if(j < n) {
        fprintf(ok, "0\n");
        printf("%d ", test);
    }else
        for(i = 0; i < n; i++)
            fprintf(ok, "%d", poz[i]);
    fprintf(ok, "\n");
    fclose(ok);
}

void gcd(int &x, int &y, int a, int b){
    if(b == 0) {
        x = 1;
        y = 0;
    }else{
        gcd(x, y, b, a%b);
        aux = x;
        x = y;
        y = aux - y * (a / b);
    }
}

int invers_modular(int x) {
    int inv, ins;
    gcd(inv, ins, x, MOD);
    if(inv < 0)
        inv = (inv + MOD) % MOD;
    return inv;
}

int aranjamente(int n, int m) {
    int a = 1;
    for(int i = n - m + 1; i <= n; i++)
        a = (a * i) % MOD;
    return a;
}

void rezolva2(int test) {
    int rez = 0, p, i, k, h, l1[26], l2[26];

    for(i = 0; i < 26; i++)
        l1[i] = l2[i] = 0;

    for(i = 0; i < m; i++)
        l1[c1[i] - 'a']++;
    for(i = 0; i < n; i++)
        l2[c2[i] - 'a']++;

    k = h = 0;
    for(i = 0; i < 26; i++)
        if(l1[i] > 1 || l2[i] > 1)
            h++;
        else if(l1[i] > 0 || l2[i] > 0)
            k++;

    // Nr(1)
    rez = (rez + aranjamente(k + h, 1));

    // Nr(2) + ... + Nr(k + h)
    for(i = 2; i <= k + h; i++) {
        rez = (rez + aranjamente(k + h, i));

        p = (aranjamente(k + h - 1, i - 2) * h) % MOD;
        p = (p * i) % MOD;
        p = (p * (i - 1)) % MOD;
        p = (p * invers_modular(2)) % MOD;
        rez = (rez + p) % MOD;
    }

    // Nr(k + h + 1)
    i = k + h + 1;
    p = (aranjamente(k + h - 1, i - 2) * h) % MOD;
    p = (p * i) % MOD;
    p = (p * (i - 1)) % MOD;
    p = (p * invers_modular(2)) % MOD;
    rez = (rez + p) % MOD;

    char fisier[20];
    sprintf(fisier, "teste\\%d-cuvinte.in", test);
    FILE *in = fopen(fisier, "w");
    fprintf(in, "2\n%s\n%s\n", c1, c2);
    fclose(in);

    sprintf(fisier, "teste\\%d-cuvinte.ok", test);
    FILE *ok = fopen(fisier, "w");
    fprintf(ok, "%d\n", rez);
    fclose(ok);
}

int main() {
    srand(time(NULL));

    int test, i, j, nr_teste, ok1, h, l[26], c, poz[NMAX + 5];

    nr_teste = NTESTE / 2;
    ok1 = rand() % nr_teste;
    for(test = 0; test < nr_teste; test++) {
        m = NSTART + (float)test / (nr_teste - 1) * (NMAX - NSTART);
        n = rand() % m + 1;

        h = rand() % 26;

        //c2
        for(i = 0; i < 26; i++)
            l[i] = 0;
        for(i = 0; i < n; i++){
            c = rand() % 26;
            while(c > h && l[c] != 0)
                c = rand() % 26;
            l[c]++;
            c2[i] = 'a' + c;
        }
        c2[n] = '\0';

        //c1
        for(i = 0; i <= m; i++)
            c1[i] = 0;
        for(i = 0; i < 26; i++)
            l[i] = 0;

        if(ok1 != test) {
            i = 0;
            j = 0;
            while(j < n) {
                i += rand() % max((m - i - (n - j - 1)) / 2, 1);
                c1[i] = c2[j];
                l[c1[i] - 'a']++;
                i++;
                j++;
            }
            for(i = 0; i < m; i++)
                if(c1[i] == 0) {
                    c = rand() % 26;
                    while(c > h && l[c] != 0)
                        c = rand() % 26;
                    l[c]++;
                    c1[i] = 'a' + c;
                }
            c1[m] = '\0';
        } else {
            for(i = 0; i < m; i++){
                c = rand() % 26;
                while(c > h && l[c] != 0)
                    c = rand() % 26;
                l[c]++;
                c1[i] = 'a' + c;
            }
            c1[m] = '\0';
        }
        rezolva1(test);
        rezolva2(test + nr_teste);
    }
    printf("%d\n", ok1);
    return 0;
}
