/* * * * * * * * * ** * * * * * * * * *
 * 关卡地图类
 * 用于实现自动寻路，链接寻路系统和关卡界面
 * 使用A*算法进行寻路
 * * * * * * * * * * * * * * * * * * * */
#ifndef LEVELMAP_H
#define LEVELMAP_H
#include"grid.h"
#include<QStack>
#include<QVector>
class levelMap {
public:
    levelMap(int row, int col, int stateMap[20][20]);
    //A*寻路算法
    QStack<grid *> search(grid *start, grid *end);
    //寻路算法中把相邻节点加入队列
    QVector<grid *> findNeighbors(grid *node, QVector<grid *> openlist, QVector<grid *> closelist);
    //判断节点是否合法
    bool check(int x, int y, QVector<grid *> openlist, QVector<grid *> closelist);
    //判断节点是否被某个列表包含
    bool iscontain(QVector<grid *> list, int x, int y);
    //寻找列表中F值最小的节点
    int findMinGrid(QVector<grid *> openlist);
    //重设节点状态
    void setState(int x,int y,int state);
    //返回节点状态
    int getState(int x,int y);

private:
    int row;
    int col;
    grid *goal;//寻路目标节点
    grid *Map[20][20];//储存节点状态
};

#endif // LEVELMAP_H
