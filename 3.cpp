// 网易雷火笔试3
// 图层渲染题
#include <iostream>
#include <cstdio>
#include <string>

// 7 3
// Image 293 0 200 200 green
// Image -234 0 200 200 red
// Image -132 86 200 200 yellow
// Image -132 -224 200 200 yellow
// Image 23 0 200 200 red
// Text -134 -205 180 33
// Text 293 -46 180 33
// green 233018
// red 233210
// yellow 242132
// 17128

using namespace std;

struct obj
{
    int x, y, w, h;
    int depth = 1;
    string textureName, name;
    int instaceID;
    int index;
};

struct color
{
    string name;
    long instanceID;
};

bool isXJ(obj currentUI, obj lowerUI)
{
    int W = abs(currentUI.x - lowerUI.x);
    int H = abs(currentUI.y - lowerUI.y);

    if ((W < (currentUI.w + lowerUI.w)/2) && (H < (currentUI.h + lowerUI.h)/2))
        return true;

    return false;
}

bool isBatch(obj currentUI, obj lowerUI)
{
    if (lowerUI.name == "Text" && currentUI.name == "Text")
        return true;

    if ((lowerUI.textureName == currentUI.textureName))
        return true;

    return false;
}

int main(){
    int tInstanceID;
    int N, M;
    int drawCall = 1;
    obj gridObj[1000];
    color gridColor[10];

    int x, y, w, h;
    int depth = 1;
    string textureName, name;

    cin >> N >> M;

    for (int i = 0; i < N; ++i)
    {
        cin >> name;
        if (name == "Image")
        {
            cin >> x >> y >> w >> h >> textureName;
            gridObj[i].name = name;
            gridObj[i].x = x;
            gridObj[i].y = y;
            gridObj[i].w = w;
            gridObj[i].h = h;
            gridObj[i].textureName = textureName;
        }else
        {
            cin >> x >> y >> w >> h;
            gridObj[i].name = name;
            gridObj[i].x = x;
            gridObj[i].y = y;
            gridObj[i].w = w;
            gridObj[i].h = h;
        }
    }

    for (int i = 0; i < M; ++i)
        cin >> gridColor[i].name >> gridColor[i].instanceID;

    cin >> tInstanceID;

    // 计算instanceID
    for (int i = 0; i < N; ++i)
    {
        if (gridObj[i].name == "Text")
            gridObj[i].instaceID = tInstanceID;
        else
        {
            for (int j = 0; j < M; ++j)
            {
                if (gridObj[i].textureName == gridColor[j].name)
                {
                    gridObj[i].instaceID = gridColor[j].instanceID;
                }
            }
        }
    }

    // 计算depth
    for (int i = 1; i < N; ++i)
    {
        int maxDepth = 1;

        for (int j = i - 1; j >= 0; --j)
        {
            // 2.相交正确
            if (isXJ(gridObj[i], gridObj[j]))
            {
                //cout << gridObj[i].textureName << "  " << gridObj[j].textureName << endl;
                // 3.
                if (gridObj[j].depth > maxDepth) maxDepth = gridObj[j].depth;
                // 2.1  2.2
                if (isBatch(gridObj[i], gridObj[j]))
                {
                    //cout << gridObj[i].textureName << "  " << gridObj[j].textureName << endl;
                    gridObj[i].depth = maxDepth;
                }
                else
                {
                    gridObj[i].depth = maxDepth + 1;
                }

            }
        }

    }

    // 排序
    for (int i = 0; i < N; ++i)
    {
        for (int j = i + 1; j < N; ++j)
        {
            if (gridObj[j].depth > gridObj[j-1].depth)
                swap(gridObj[j], gridObj[j-1]);
            else if (gridObj[j].depth == gridObj[j-1].depth)
            {
                if (gridObj[j].instaceID > gridObj[j-1].instaceID)
                    swap(gridObj[j], gridObj[j-1]);
                else if (gridObj[j].instaceID == gridObj[j-1].instaceID)
                {
                    if (gridObj[j].index > gridObj[j-1].index)
                        swap(gridObj[j], gridObj[j-1]);
                }
            }
        }
    }

    // 计算drawCall
    for (int i = 1; i < N; ++i)
    {
        if (!isBatch(gridObj[i], gridObj[i-1]))
            drawCall++;
    }

    cout << drawCall << endl;

    return 0;
}