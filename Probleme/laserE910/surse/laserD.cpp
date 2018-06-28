#include<stdio.h>
#include<math.h>
#include<algorithm>
#define NMAX 1000005

using namespace std;

struct punct {
    int x, y;
} pct[NMAX];

int n, d, p;

void citire() {
    FILE *f = fopen("laser.in", "r");
    fscanf(f, "%d%d%d", &p, &n, &d);
    for(int i = 0; i < n; i++)
        fscanf(f, "%d%d", &pct[i].x, &pct[i].y);
    fclose(f);
}

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
    return pmin + 1;
}

int cmp(punct p, punct q) {
    return  1LL * p.y * q.x < 1LL * q.y * p.x;
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
    return rez;
}

int main()
{
    citire();

    FILE *f = fopen("laser.out", "w");
    if(p == 1)
        fprintf(f, "%d\n", rezolva1());
    else
        fprintf(f, "%d\n", rezolva2());
    fclose(f);
    return 0;
}
