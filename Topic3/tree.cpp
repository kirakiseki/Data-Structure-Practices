/*
 *
 *  DataStructure-Topic3-TestDataGenerator
 *
 *  Date: 2022/4/30
 *  Charset: UTF-8
 *  Language: cpp
 *  
 *  Tested on gcc (GCC) 11.2.0, GNU ld (GNU Binutils) 2.38 on Linux version 5.15.32-1-MANJARO and gcc version 11.2.0 (Rev10, Built by MSYS2 project) on Windows 10 20H2
 *
 *  Description: 将A-J字符采用Fisher–Yates算法随机打乱（shuffle函数），生成随机二叉树（randomBTreeEdges函数）后匹配输出（按次序输出二叉树的每一条边）。
 * 
 *  Usage:  输入二叉树结点位于左侧的概率，位于右侧的概率（剩余部分随机选择），即可生成随机二叉树。
 * 
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <utility>

using namespace std;

typedef char elem;
typedef bool status;
const int ELEMS_COUNT = 10;
elem elems[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
pair<int, int> edges[ELEMS_COUNT - 1];

typedef struct BNode
{
    elem dat;
    BNode *lchild, *rchild;
} BNode;

status shuffle(char elems[])
{
    for (int i = ELEMS_COUNT - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        elem temp = elems[i];
        elems[i] = elems[j];
        elems[j] = temp;
    }
    return true;
}

status randomBTreeEdges(double ratioLeft, double ratioRight, pair<int, int> edges[])
{
    try //判断概率合法性 不合法抛出异常后catch捕获
    {
        if (ratioLeft < 0 || ratioLeft > 1)
        {
            throw "ratioLeft must be in [0,1]";
        }
        if (ratioRight < 0 || ratioRight > 1)
        {
            throw "ratioRight must be in [0,1]";
        }
        if (ratioLeft + ratioRight > 1)
        {
            throw "ratioLeft + ratioRight must smaller than 1";
        }

        //可供选择的数字id列表
        int canLeft[ELEMS_COUNT] = {1}, countCanLeft = 1;
        int canRight[ELEMS_COUNT] = {1}, countCanRight = 1;
        int edgesCount = 0;
        for (int i = 2; i <= ELEMS_COUNT; ++i)
        {
            double pos = (double)rand() / RAND_MAX; //生成随机数
            BNode node = {0, nullptr, nullptr};
            if (pos < ratioLeft || (ratioLeft + ratioRight < pos && pos <= (1.0 - ratioLeft - ratioRight) / 2)) //生成结点位于左侧
            {
                int posIndex = rand() % countCanLeft;
                node.dat = canLeft[posIndex];
                BNode delLastNode = {0, nullptr, nullptr};
                delLastNode.dat = canLeft[--countCanLeft];  //保存上一个结点副本
                if (posIndex < countCanLeft)    //若选择元素不在最后，则复制到选定位置
                {
                    canLeft[posIndex] = delLastNode.dat;
                }
            }
            else
            {
                int posIndex = rand() % countCanRight;
                node.dat = canRight[posIndex];
                BNode delLastNode = {0, nullptr, nullptr};
                delLastNode.dat = canRight[--countCanRight];
                if (posIndex < countCanRight)
                {
                    canRight[posIndex] = delLastNode.dat;
                }
            }
            canLeft[countCanLeft++] = i;
            canRight[countCanRight++] = i;
            edges[edgesCount++] = make_pair((int)node.dat, i);  //使用makepair建立单项边，从node.dat到i
        }
        sort(edges, edges + edgesCount, [](pair<int, int> a, pair<int, int> b)
             { return a.first < b.first; });    //按照边的起点数字id排序
        for_each(edges, edges + edgesCount, [](pair<int, int> a)
                 { cout << elems[a.first-1] << " " << elems[a.second-1] << endl; });    //输出边，并对应乱序列表
        return true;
    }
    catch (const char *e)
    {
        cout << "Create randomBTree failed because: " << e << endl;
        return false;
    }
}

int main()
{
    srand(time(nullptr));
    double ratioL,ratioR;
    cin>>ratioL>>ratioR;
    shuffle(elems);
    randomBTreeEdges(ratioL, ratioR, edges);
    return 0;
}
