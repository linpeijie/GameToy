#include <iostream>
#include <cstdio>

using namespace std;

int main(){
    int T;
    cin >> T;

    while (T--)
    {
        int distance = 0;

        int n;
        cin >> n;

        int A[n];
        int V[n];
        for (int i = 0; i < n; ++i)
            cin >> A[i];
        for (int i = 0; i < n; ++i)
            cin >> V[i];

        int count = n;

        while (count>1)
        {
            int min_d = INT_MAX;
            int min_i = 0;
            int max_i = 0;
            int max = 0;

            for (int i = 0; i < n; ++i)
                if (A[i] > max)
                {
                    max = A[i];
                    max_i = i;
                }

            for (int i = 0; i < n; ++i)
            {
                if (A[i] != 0 && i != max_i)
                {
                    int d = abs(max_i - i)*V[max];
                    if (d < min_d)
                    {
                        min_d = d;
                        min_i = i;
                    }
                }
            }

            swap(A[max_i], A[min_i]);
            A[min_i] = 0;

            count--;
            distance += min_d;
        }

        cout << distance << endl;
    }
    return 0;
}