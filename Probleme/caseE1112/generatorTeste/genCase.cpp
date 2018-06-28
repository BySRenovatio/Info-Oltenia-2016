#include<stdio.h>
#include<algorithm>
#include<math.h>
#include<stdlib.h>
#include<ctime>
#define NSTART 20
#define KSTART 1
#define NTESTE 20
#define NMAX 1000
#define KMAX 10
#define COORDMAX 1000000000

using namespace std;
int x[NMAX + 5], y[NMAX + 5], xs[KMAX + 1], ys[KMAX + 1], ls[KMAX + 1];
int p, n, k, poz[KMAX + 1][NMAX + 5], nr[KMAX + 1], case_izolate, s[NMAX + 5], vf;
int sat_curent;

long long det(int i, int j, int k){
    return 1LL * x[i] * y[j] + 1LL * x[j] * y[k] + 1LL * x[k] * y[i] - 1LL * y[j] * x[k] - 1LL * y[k] * x[i] - 1LL * y[i] * x[j];
}
int cmp(int i,int j){
    return (y[i]-y[poz[sat_curent][0]])*(x[j]-x[poz[sat_curent][0]])<(x[i]-x[poz[sat_curent][0]])*(y[j]-y[poz[sat_curent][0]]);
}

int apartine_sat(int sat, int casa) {
    return x[casa] >= xs[sat] && y[casa] >= ys[sat] &&
        x[casa] <= xs[sat] + ls[sat] && y[casa] <= ys[sat] + ls[sat];
}

void gaseste_case() {
    int aux;

    case_izolate = n;
    for(int i = 1; i <= k; i++)
        nr[i] = 0;

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= k; j++)
            if(apartine_sat(j, i)) {
                case_izolate--;
                poz[j][nr[j]] = i;
                nr[j]++;

                if(x[i] < x[poz[j][0]] || (x[i] == x[poz[j][0]] && y[i] < y[poz[j][0]])) {
                    aux = poz[j][0];
                    poz[j][0] = i;
                    poz[j][nr[j] - 1] = aux;
                }
            }
}

void infasuratoare() {
    if(nr[sat_curent] < 3) {
        vf = 0;
        return;
    }
    sort(poz[sat_curent] + 1, poz[sat_curent] + nr[sat_curent], cmp);

    vf = 2;
    s[1] = poz[sat_curent][0];
    s[2] = poz[sat_curent][1];
    for(int i = 2; i < nr[sat_curent]; i++){
        while(vf >= 2 && det(s[vf - 1], s[vf], poz[sat_curent][i]) < 0)
            vf--;
        vf++;
        s[vf] = poz[sat_curent][i];
    }
}

void scrie_test(int p, int test) {
    char fisier[20];
    int i;

    sprintf(fisier, "teste\\%d-case.in", test);
    FILE *in = fopen(fisier, "w");

    sprintf(fisier, "teste\\%d-case.ok", test);
    FILE *ok = fopen(fisier, "w");


    fprintf(in, "%d\n%d %d\n", p, n, k);
    for(i = 1; i <= n; i++)
        fprintf(in, "%d %d ", x[i], y[i]);
    fprintf(in, "\n");
    for(i = 1; i <= k; i++)
        fprintf(in, "%d %d %d ", xs[i], ys[i], ls[i]);
    fprintf(in, "\n");

    gaseste_case();

    if(p == 1) {
        fprintf(ok, "%d\n", case_izolate);
        printf("izolate_calculat = %d\n", case_izolate);
    } else {
        printf("pe infasuratoare: ");

        int rez = 0;
        for(i = 1; i <= k; i++) {
            sat_curent = i;
            infasuratoare();
            rez += vf;
            printf("%d ", vf);
        }
        printf("\n");
        fprintf(ok, "%d\n", rez);
    }

    fclose(in);
    fclose(ok);
}

int lrand() {
    return rand() * rand();
}

int interior(int i, int x, int y) {
    if(x >= xs[i] && x <= xs[i] + ls[i] && y >= ys[i] && y <= ys[i] + ls[i])
        return 1;
    return 0;
}

int e_izolat(int x, int y) {
    for(int i = 1; i <= k; i++)
        if(interior(i, x, y))
            return 0;
    return 1;
}

int main() {
    srand(time(NULL));

    int test, i, j, nr_teste, izolate, nr, q, sw;

    nr_teste = NTESTE / 2;

    for(test = 0; test < nr_teste; test++) {
        n =  NSTART + (float)test / (nr_teste - 1) * (NMAX - NSTART);
        k =  KSTART + (float)test / (nr_teste - 1) * (KMAX - KSTART);

        izolate = rand() % (n / 10) + 1;
        nr = (n - izolate) / k;

        printf("n = %d k = %d izolate = %d\n", n,k,izolate);

        for(i = 1; i <= k; i++) {
            xs[i] = (i - 1) * (COORDMAX / KMAX) + lrand() % (COORDMAX / KMAX / 10) + 1;
            ys[i] = lrand() % (COORDMAX - COORDMAX / KMAX);
            ls[i] = (COORDMAX / KMAX / 4) + lrand() % (COORDMAX / KMAX / 2);
        }

        q = 0;
        for(i = 1; i <= izolate; i++) {
            q++;
            x[q] = lrand() % COORDMAX;
            y[q] = lrand() % COORDMAX;

            while(!e_izolat(x[q], y[q])) {
                x[q] = lrand() % COORDMAX;
                y[q] = lrand() % COORDMAX;
            }
        }

        for(i = 1; i <= k; i++)
            for(j = 1; j <= nr; j++) {
                q++;
                x[q] = xs[i] + lrand() % ls[i];
                y[q] = ys[i] + lrand() % ls[i];
            }

        while(q < n) {
            q++;
            x[q] = xs[k] + lrand() % ls[k];
            y[q] = ys[k] + lrand() % ls[k];
        }
        scrie_test(1, test);
        scrie_test(2, 10 + test);
        printf("\n");
    }
    return 0;
}
