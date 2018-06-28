#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<ctime>
#include<stdlib.h>
#define NMAX 1000000
#define COORDMAX 9999999
#define NTESTE 20
#define NSTART 100

using namespace std;

struct punct {
    int x, y;
} pct[NMAX + 5];

int n, d, p;

double dist(int i) {
    return sqrt(1.0 * pct[i].x * pct[i].x + 1.0 * pct[i].y * pct[i].y);
}

int in_raza(int i) {
    return dist(i) <= 1.0 * d;
}

int rezolva1() {
    double dmin, d;
    int pmin;
    dmin = dist(0); pmin = 0;
    for(int i = 1; i < n; i++) {
        d = dist(i);
        if(d < dmin){
            dmin = d;
            pmin = i;
        }
    }
    printf("c1 = %d ", pmin + 1);
    return pmin + 1;
}

int cmp(punct p, punct q) {
    return  1LL * p.y * q.x < 1LL * q.y * p.x;
}

int cmp2(punct p, punct q) {
    return p.x < q.x || (p.x == q.x && p.y < q.y);
}

int rezolva2() {
    int sw, rez = 0;
    sort(pct, pct + n, cmp);

    if(in_raza(0))
        sw = 1;
    else
        sw = 0;

    for(int i = 1; i < n; i++)
        if(1LL * pct[i - 1].y * pct[i].x == 1LL * pct[i].y * pct[i - 1].x) {
            if(sw == 0 && in_raza(i))
                sw = 1;
        } else {
            rez += sw;
            if(in_raza(i))
                sw = 1;
            else
                sw = 0;
        }
    rez += sw;
    printf("c2=%d\n", rez);
    return rez;
}

int lrand() {
    return rand() * rand();
}

void scrie_test(int p, int test) {
    char fisier[20];
    int i;

    sprintf(fisier, "teste\\%d-laser.in", test);
    FILE *in = fopen(fisier, "w");

    sprintf(fisier, "teste\\%d-laser.ok", test);
    FILE *ok = fopen(fisier, "w");

    fprintf(in, "%d\n%d %d\n", p, n, d);
    for(i = 0; i < n; i++)
        fprintf(in, "%d %d\n", pct[i].x, pct[i].y);

    if(p == 1)
        fprintf(ok, "%d\n", rezolva1());
    else
        fprintf(ok, "%d\n", rezolva2());

    fclose(in);
    fclose(ok);
}

int main() {
    srand(time(NULL));

    int test, i, j, nr_teste, k, sw;

    nr_teste = NTESTE / 2;

    for(test = 0; test < nr_teste; test++) {
        n =  NSTART + (float)test / (nr_teste - 1) * (NMAX - NSTART);
        d = COORDMAX / 4 + lrand() % (COORDMAX / 2);

        for(i = 0; i < n / 4; i++) {
            pct[i].x = lrand() % COORDMAX + 1;
            pct[i].y = lrand() % COORDMAX + 1;
        }

        for(i = n / 4; i < n; i++)
            if(rand() % 2 == 1) {
                pct[i].x = lrand() % COORDMAX + 1;
                pct[i].y = lrand() % COORDMAX + 1;
            }else {
                j = lrand() % i;
                k = rand() % 10;
                pct[i].x = (k * pct[j].x) % COORDMAX + 1;
                pct[i].y = (k * pct[j].y) % COORDMAX + 1;
            }

        sort(pct, pct + n, cmp2);
        sw = 1;
        for(i = 1; i < n; i++)
            if(pct[i].x == pct[i - 1].x && pct[i].y == pct[i - 1].y){
                pct[i].x = lrand() % COORDMAX + 1;
                pct[i].y = lrand() % COORDMAX + 1;
                sw = 0;
            }
        while(!sw) {
            sort(pct, pct + n, cmp2);
            sw = 1;
            for(i = 1; i < n; i++)
                if(pct[i].x == pct[i - 1].x && pct[i].y == pct[i - 1].y){
                    pct[i].x = lrand() % COORDMAX + 1;
                    pct[i].y = lrand() % COORDMAX + 1;
                    sw = 0;
                }
        }

        random_shuffle(pct, pct + n);

        scrie_test(1, test);
        scrie_test(2, test + nr_teste);
    }
    return 0;
}
