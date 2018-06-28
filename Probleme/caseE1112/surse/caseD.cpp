#include<stdio.h>
#include<algorithm>
#include<math.h>
#define NMAX 1005
#define KMAX 11

using namespace std;
int x[NMAX], y[NMAX], xs[KMAX], ys[KMAX], ls[KMAX];
int p, n, k, poz[KMAX][NMAX], nr[KMAX], case_izolate, s[NMAX], vf;
int sat_curent;

long long det(int i, int j, int k){
    return 1LL * x[i] * y[j] + 1LL * x[j] * y[k] + 1LL * x[k] * y[i] - 1LL * y[j] * x[k] - 1LL * y[k] * x[i] - 1LL * y[i] * x[j];
}
int cmp(int i,int j){
    return (y[i]-y[poz[sat_curent][0]])*(x[j]-x[poz[sat_curent][0]])<(x[i]-x[poz[sat_curent][0]])*(y[j]-y[poz[sat_curent][0]]);
}

void citire(){
    FILE *f;

    f=fopen("case.in","r");
    fscanf(f,"%d%d%d", &p, &n, &k);

    for(int i = 1; i <= n; i++)
        fscanf(f, "%d%d", &x[i], &y[i]);
    for(int i = 1; i <= k; i++)
        fscanf(f, "%d%d%d", &xs[i], &ys[i], &ls[i]);
    fclose(f);
}

int apartine_sat(int sat, int casa) {
    return x[casa] >= xs[sat] && y[casa] >= ys[sat] &&
        x[casa] <= xs[sat] + ls[sat] && y[casa] <= ys[sat] + ls[sat];
}

void gaseste_case() {
    int aux;

    case_izolate = n;

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

int main() {
    citire();
    gaseste_case();

    FILE *f;
    f=fopen("case.out","w");

    if(p == 1)
        fprintf(f, "%d\n", case_izolate);
    else {
        int rez = 0;
        for(int i = 1; i <= k; i++) {
            sat_curent = i;
            infasuratoare();
            rez += vf;
        }
        fprintf(f, "%d\n", rez);
    }

    fclose(f);
    return 0;
}
