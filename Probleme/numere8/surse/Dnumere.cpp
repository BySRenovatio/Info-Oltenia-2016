#include <fstream>
#include <iostream>
#define NMAX 10001
using namespace std;

int p, n, k, x[NMAX];

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

int main() {

    // citire date
    int i;
    ifstream fin("numere.in");
    fin >> p >> n >> k;

    for(i = 1; i <= n; i++)
        fin >> x[i];
    fin.close();

    // scriere date
    ofstream fout("numere.out");
    if(p == 1)
        fout << quick_select(1, n) << '\n';
    else
        fout << kadane() << '\n';
    fout.close();

    return 0;
}
