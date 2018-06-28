#include<stdio.h>
#include<ctime>
#include<stdlib.h>
#define NMAX 1000
#define NSTART 50
#define NTESTE 20
using namespace std;
int p, n, m, compus[NMAX * NMAX + 10], a, b, c;
long long s;

void prime() {
    int i, j;
    compus[0] = compus[1] = 1;
    for(i = 2; i * i <= NMAX * NMAX; i++)
        if(!compus[i])
            for(j = 0; i * i + j * i <= NMAX * NMAX; j++)
                compus[i * i + j * i] = 1;
}

void scrie_test(int p, int test) {
    char fisier[20];

    printf("p=%d test=%d m=%d n=%ds=%I64d\n", p, test, m, n, s);

    sprintf(fisier, "teste\\%d-prime.in", test);
    FILE *in = fopen(fisier, "w");

    sprintf(fisier, "teste\\%d-prime.ok", test);
    FILE *ok = fopen(fisier, "w");

    fprintf(in, "%d\n%d %d %I64d\n", p, m, n, s);
    if(p == 1)
        fprintf(ok, "%d %d %d\n", a, b, c);
    else
        fprintf(ok, "%d %d\n", (c - 1) / n + 1, (c - 1) % n + 1);

    fclose(in);
    fclose(ok);
}

int main(){
    int test, nr_teste, i;
    srand(time(NULL));
    prime();

    nr_teste = NTESTE / 2;

    for(test = 0; test < nr_teste; test++) {
        n =  NSTART + (float)test / (nr_teste - 1) * (NMAX - NSTART);
        m = n - 1;

        a = (rand() * rand()) % (n * m) + 1;
        while(a > 1 && compus[a])
            a--;
        while(a == 1) {
            a = (rand() * rand()) % (n * m) + 1;
        while(a > 1 && compus[a])
            a--;
        }


        b = (rand() * rand()) % (n * m) + 1;
        while(b > 1 && compus[b])
            b--;
        while(b == 1 || b == a) {
            b = (rand() * rand()) % (n * m) + 1;
            while(b > 1 && compus[b])
                b--;
        }

        c = (rand() * rand()) % (n * m) + 1;
        while(c > 1 && compus[c])
            c--;
        while(c == 1 || c == a || c == b) {
            c = (rand() * rand()) % (n * m) + 1;
            while(c > 1 && compus[c])
                c--;
        }



printf("%d %d %d\n",a,b,c);
        s = 1LL * n * m * (n * m + 1) / 2 - a - b - c;

        scrie_test(1, test);
        scrie_test(2, test + nr_teste);
    }

    return 0;
}
