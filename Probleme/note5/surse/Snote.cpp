#include <iostream>
#include <fstream>

using namespace std;

int solve();

int main()
{
    ofstream fout("note.out");

    fout << solve();

    fout.close();

    return 0;
}

int solve()
{
    int p;                         // 1 sau 2
    long long int n;               // 1 <= n <= 10^14

    int nrNote = 0;
    int minNota = 10;

    ifstream fin("note.in");

    fin >> p;
    fin >> n;

    fin.close();

    if (p == 1)                     // nr. note
    {
        while (n > 0)
        {
            if (n % 10 == 0)
            {
                nrNote ++;
                n /= 100;
            }
            else
            {
                nrNote ++;
                n /= 10;
            }
        }

        return nrNote;
    }
    else                                // cea mai mica nota
    {
        while (n > 0)
        {
            if (n % 10 != 0)
            {
                if (minNota > (n % 10))
                    minNota = n % 10;

                n /= 10;
            }
            else                        // = 10
            {
                n /= 100;
            }
        }

        return minNota;
    }

    return -1;
}
