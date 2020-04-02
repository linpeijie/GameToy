// 网易雷火笔试1
//
#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main(){
    //freopen("1.in","r",stdin);
    int n;
    vector<map<char, long>> F;
    map<char, long> f1;
    map<char, long> f2;
    string f[40];
    int count[26];

    cin >> n;
    cin >> f[0] >> f[1];

    for (auto e: f[0])
    {
        if (f1.find(e) != f1.end()) f1[e]++;
        else
        {
            f1.insert(pair<char, long>(e, 1));
            if (count[e - 'a'] == 0) count[e - 'a'] = 1;
        }

    }

    for (auto e: f[1])
    {
        if (f2.find(e) != f2.end()) f2[e]++;
        else
        {
            f2.insert(pair<char, long>(e, 1));
            if (count[e - 'a'] == 0) count[e - 'a'] = 1;
        }

    }

    F.push_back(f1);
    F.push_back(f2);

    for(int i = 2; i < n; i++)
    {
        map<char, long> m;
        for(int j = 0; j < 26; ++j)
        {
            if (count[j] > 0)
            {
                long number = F[i-1][j + 'a'] + F[i-2][j + 'a'];
                m.insert(pair<char, long>((j + 'a'), number));
            }

        }

        F.push_back(m);
    }

    for(int i = 0; i < 26; ++i)
    {
        if (count[i] > 0)
        {
            cout << char(i + 'a') << ":" << F[n-1][i + 'a'] << endl;
        }
    }

    return 0;
}