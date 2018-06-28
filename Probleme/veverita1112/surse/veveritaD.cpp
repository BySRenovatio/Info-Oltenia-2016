#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<vector>
#define inf 2000000000
#define NMAX 501
using namespace std;

int d[NMAX], x[NMAX], px[NMAX], py[NMAX], poz[NMAX], c[NMAX], cost[NMAX][NMAX];
int n, nn, k, p, nc, distanta;
vector < int > l[NMAX];

void citire() {
    FILE *f = fopen("veverita.in", "r");

    fscanf(f, "%d", &p);
    fscanf(f, "%d%d", &n, &k);

    for(int i = 1; i <= n; i++)
        fscanf(f, "%d%d", &px[i], &py[i]);
    fclose(f);
}

int dist(int i, int j) {
    return abs(px[i] - px[j]) + abs(py[i] - py[j]);
}

void construieste_graf() {
    for(int i = 1; i < n; i++)
        for(int j = i + 1; j <=n; j++)
            if(dist(i, j) <= k) {
                l[i].push_back(j);
                l[j].push_back(i);
            }
}

void dfs(int nod) {
    c[nod] = nc;
    for(int i = 0; i < l[nod].size(); i++)
        if(c[l[nod][i]] == 0)
            dfs(l[nod][i]);
}

void componente_conexe() {
    for(int i = 1; i <= n; i++)
        if(c[i] == 0) {
            nc++;
            dfs(i);
        }
}

void construieste_graf_condensat() {
    int d;

    for(int i = 1; i <= nc; i++) {
        for(int j = 1; j <= nc; j++)
            cost[i][j] = inf;
        cost[i][i] = 0;
    }

    for(int i = 1; i < n; i++)
        for(int j = i + 1; j <= n; j++)
            if(c[i] != c[j]){
                d = dist(i, j);
                if(d < cost[c[i]][c[j]])
                    cost[c[i]][c[j]] = cost[c[j]][c[i]] = d;
            }
}

void swap(int i, int j){
    int aux;
    aux = x[i];
    x[i] = x[j];
    x[j] = aux;
    poz[x[i]] = i;
    poz[x[j]] = j;
}

void heapUp(int k){
    if(k > 1)
        if(d[x[k / 2]] > d[x[k]]){
            swap(k, k / 2);
            heapUp(k / 2);
        }
}
void heapDown(int k){
    int st, dr, i;

    if(2 * k <= nn){
        st = d[x[2 * k]];
        if(2 * k + 1 <= nn)
            dr = d[x[2 * k + 1]];
        else
            dr = st + 1;
        if(st < dr)
            i = 2 * k;
        else
            i = 2 * k + 1;
        if(d[x[k]] > d[x[i]]){
            swap(k, i);
            heapDown(i);
        }
    }
}
void buildHeap(){
    for(int i = 1; i <= nn; i++)
        heapUp(i);
}
int scoateHeap(){
    swap(1, nn);
    nn--;
    heapDown(1);
    poz[x[nn + 1]] = 0;
    return x[nn + 1];
}
void prim(){
    int k;
    nn = nc;

    for(int i = 1; i <= nn; i++){
        x[i] = i;
        d[i] = inf;
        poz[i] = i;
    }
    d[1] = 0;
    buildHeap();

    while(nn > 0){
        k = scoateHeap();

        distanta += d[k];

        for(int i = 1; i <= nc; i++)
            if(poz[i] !=0 && cost[k][i] < d[i]){
                d[i] = cost[k][i];
                heapUp(poz[i]);
            }
    }
}

int main(){
    citire();
    construieste_graf();
    componente_conexe();

    FILE *f = fopen("veverita.out", "w");
    if(p == 1)
        fprintf(f,"%d\n", nc - 1);
    else {
        construieste_graf_condensat();
        prim();
        fprintf(f,"%d\n", distanta);
    }

    fclose(f);
    return 0;
}
