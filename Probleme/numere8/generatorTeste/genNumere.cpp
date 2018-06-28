#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#define NMAX 10000
#define NSTART 100
#define NTESTE 20

using namespace std;

int p, n, k, x[NMAX + 1];

int pivot(int st, int dr) {
    int i, j, i0 = 0, j0 = -1, aux;
    i = st; j = dr;

    while(i < j) {
        if(x[i] > x[j]) {
            aux = x[i];
            x[i] = x[j];
            x[j] = aux;

            aux = i0;
            i0 = -j0;
            j0 = -aux;
        }
        i += i0;
        j += j0;
    }

    return i;
}

int quick_select(int st, int dr) {
    int m = pivot(st, dr);

    if(k <= m - st)
        return quick_select(st, m - 1);
    else if(k > m - st + 1) {
        k -= m - st + 1;
        return quick_select(m + 1, dr);
    } else
        return x[m];
}

int kadane() {
    int max_local, max_global;

    max_local = max_global = x[1];
    for(int i = 2; i <= n; i++) {
        if(max_local > 0)
            max_local += x[i];
        else
            max_local = x[i];

        if(max_local > max_global)
            max_global = max_local;
    }

    return max_global;
}

void scrie_test(int p, int test) {
    char fisier[20];
    int i;

    sprintf(fisier, "teste\\%d-numere.in", test);
    FILE *in = fopen(fisier, "w");

    sprintf(fisier, "teste\\%d-numere.ok", test);
    FILE *ok = fopen(fisier, "w");


    fprintf(in, "%d\n%d %d\n", p, n, k);
    if(p == 1)
        fprintf(ok, "%d\n", quick_select(1, n ));
    else
        fprintf(ok, "%d\n", kadane());

    for(i = 1; i <= n; i++)
        fprintf(in, "%d ", x[i]);
    fprintf(in, "\n");

    fclose(in);
    fclose(ok);
}

int main() {

    srand(time(NULL));

    int test, nr_teste, neg, i;

    nr_teste = NTESTE / 2;

    for(test = 0; test < nr_teste; test++) {
        n =  NSTART + (float)test / (nr_teste - 1) * (NMAX - NSTART);
        k = rand() % n + 1;

        for(i = 1; i <= n; i++){
            x[i] = rand() % NMAX;

            //primul test de la cerinta 2 are doar numere negative
            if(test == 0)
                x[i] = -x[i];
            else {
                neg = rand() % 2;
                if(neg)
                    x[i] = -x[i];
            }
        }

        scrie_test(2, test + nr_teste);
        scrie_test(1, test);
    }

    return 0;
}
