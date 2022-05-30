#ifndef LEVELMAP_H
#define LEVELMAP_H
#include"grid.h"
#include<QStack>
#include<QVector>
class levelMap {
public:
    levelMap(int row, int col, int stateMap[20][20]);

    QStack<grid *> search(grid *start, grid *end);

    QVector<grid *> findNeighbors(grid *node, QVector<grid *> openlist, QVector<grid *> closelist);

    bool check(int x, int y, QVector<grid *> openlist, QVector<grid *> closelist);

    bool iscontain(QVector<grid *> list, int x, int y);

    int findMinGrid(QVector<grid *> openlist);

private:
    int row;
    int col;
    grid *Map[20][20];
};

#endif // LEVELMAP_H
