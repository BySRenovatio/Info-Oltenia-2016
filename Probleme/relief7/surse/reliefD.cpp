#include<stdio.h>
#define NMAX 100005
using namespace std;

int n, p;
long long x[NMAX];

void citire() {
    FILE *f = fopen("relief.in", "r");
    fscanf(f, "%d%d", &p, &n);
    for(int i = 1; i <= n; i++)
        fscanf(f, "%I64d", &x[i]);
    fclose(f);
}

void rezolva1() {
    int m, c;
    m = x[1]; c = 1;
    for(int i = 2; i <= n; i++)
        if(x[i] < m) {
            m = x[i];
            c = 1;
        }else if(x[i] == m)
            c++;

    FILE *f = fopen("relief.out", "w");
    fprintf(f, "%d\n", c);
    fclose(f);
}

void rezolva2() {
    int s1, s2, m = 0, d = 0, v = 0;
    FILE *f = fopen("relief.out", "w");
    if(n == 1)
        fprintf(f, "0 0 0\n");
    else {
        s1 = -1;

        if(x[2] > x[1])
            s2 = 1;
        else if(x[2] == x[1]) {
            s2 = 0;
            v++;
        } else
            s2 = -1;

        for(int i = 3; i <= n; i++)
            if(x[i] > x[i - 1]){
                if(s2 != 1){
                    s1 = s2;
                    s2 = 1;
                }
            } else if(x[i] == x[i - 1]) {
                if(s2 != 0) {
                    s1 = s2;
                    s2 = 0;
                    v++;
                }
            }else {
                if(s2 != -1) {
                    if(s2 == 1)
                        m++;
                    else
                        if(s2 == 0 && s1 == 1)
                            d++;
                    s1 = s2;
                    s2 = -1;
                }
            }
            v -= d;
            fprintf(f, "%d %d %d\n", m, d, v);
    }
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
