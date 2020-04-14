#include <iostream>
#include <cstdio>
#include <cmath>
#include <map>

using namespace std;
#define MAX 510
int arr[MAX][MAX];

double distance(int x1, int y1, int x2, int y2)
{
    return sqrt((x1-x2)*(x1-x2) +(y1-y2)*(y1-y2));
}

int main(){
    int T;
    cin >> T;

    while(T--)
    {
        int M, L;
        cin >> M >> L;

        int i,j;

        for (i = 0; i < M; ++i)
            for (j = 0; j < M; ++j)
            cin >> arr[i][j];

        int X, Y;
        cin >> X >> Y;

        int front_l = 0;

        while (front_l < L)
        {
            front_l = L;
            for (i = 0; i < M;++i)
                for (j = 0; j < M; ++j)
                    if (arr[i][j] > 0 && distance(i,j,X,Y) <= L)
                    {
                        L += arr[i][j];
                        arr[i][j] = 0;
                    }
        }

        cout << L;
    }

    return 0;
}