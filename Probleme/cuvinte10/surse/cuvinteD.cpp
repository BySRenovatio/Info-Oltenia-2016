#include<stdio.h>
#include<string.h>
#define NMAX 255
#define MOD 9901
using namespace std;

int p, m, n, aux;
char c1[NMAX], c2[NMAX];

void citire() {
    FILE *f;
    f = fopen("cuvinte.in", "r");
    fscanf(f, "%d", &p);
    fscanf(f, "%s", c1);
    fscanf(f, "%s", c2);
    m = strlen(c1);
    n = strlen(c2);
    fclose(f);
}

void rezolva1() {
    int poz[NMAX], i, j;
    for(i = 0, j = 0; i < m && j < n; i++)
        if(c1[i] == c2[j]) {
            poz[j] = i + 1;
            j++;
        }

    FILE *f = fopen("cuvinte.out", "w");
    if(j < n)
        fprintf(f, "0\n");
    else
        for(i = 0; i < n; i++)
            fprintf(f, "%d", poz[i]);
    fprintf(f, "\n");
    fclose(f);
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

void rezolva2() {
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


    FILE *f = fopen("cuvinte.out", "w");
    fprintf(f, "%d\n", rez);
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
