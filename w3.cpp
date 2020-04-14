#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>

using namespace std;

#define MAX 11000
int arr[MAX];
int number[MAX];

int find(int x)
{
    if (x == arr[x])
        return x;
    else
    {
        int y = find(arr[x]);
        arr[x] = y;
        return y;
    }
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int N, M;
        cin >> N >> M;

        for (int i = 1; i <= N; ++i)
        {
            arr[i] = i;
            number[i] = 1;
        }

        while (N--)
        {
            int op;
            cin >> op;

            if (op == 1)
            {
                int X, Y;
                cin >> X >> Y;

                int find_x, find_y;

                find_x = find(X);
                find_y = find(Y);

                if (find_x != find_y)
                {
                    arr[find_x] = find_y;
                    number[find_y] += number[find_x];
                }

            }else if (op == 2)
            {
                int X;
                cin >> X;

                if (arr[X] == X && number[X] > 1)
                {
                    int z = number[X];
                    number[X] = 1;
                    for (int i = 1; i <= N; ++i)
                    {
                        if ( i == X)
                            continue;

                        int x_i = find(i);
                        if (x_i == X)
                        {
                            for (int j = i + 1; j <= N; j++)
                            {
                                int x_j = find(j);
                                if (x_j == X)
                                    arr[j] = i;
                            }

                            number[i] = z - 1;
                            arr[i] = i;
                        }
                    }
                }
            }else
            {
                int X;
                cin >> X;

                int find_x = find(X);
                cout << number[find_x];
            }

            for (int i = 1; i <= N; ++i)
            {
                int find_x;
                find_x = find(i);
            }
        }
    }


    return 0;
}